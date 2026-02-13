#include "myheader.h"
#include <lpc214x.h>
#include "delay.h"
#include "lcd.h"
#include "dht11.h"
#include <string.h>
#define UPDATE_TIME 1
#define BUZZERPIN 21
u8 setPoint=31;
u8 menu_flag;
u32 interruptFlag=0;
u8 eeprom_index=1;
u8* convertToString(u8 num);
void mystrrev(u8* ptr);
u32 gcount=0;
int main (void)
{
	unsigned char humidity_integer, humidity_decimal, temp_integer, temp_decimal, checksum,humidity,temperature;  
	Init_LCD();
	init_i2c();
	//RTC_nmin_Alarm();
	InitUART0();
	Init_RTC();
	Init_eint2();
	Init_KPM();
	strLCD("Connecting...");
   	esp01_connectAP();

	while(1)
	{
		if(menu_flag==1)
		{
			menu_flag=0;
			menuHandler();
		}
		dht11_request();
		dht11_response();
		humidity_integer = dht11_data();
		humidity_decimal = dht11_data();
		temp_integer = dht11_data();
		temp_decimal = dht11_data();
		checksum = dht11_data();
		humidity = humidity_integer;
		temperature = temp_integer;
		if( (humidity_integer + humidity_decimal + temp_integer + temp_decimal) != checksum )
			strLCD("Checksum Error\r\n");
		else
		{
			cmdLCD(0x80);
			strLCD("H : ");
			u32LCD(humidity_integer);
			charLCD('.');
			u32LCD(humidity_decimal);
			strLCD(" % RH ");
			cmdLCD(0xC0);
			strLCD("T : ");
			u32LCD(temp_integer);
			charLCD('.');
			u32LCD(temp_decimal);
			cmdLCD(223);
			strLCD("C");
			cmdLCD(0xD4);
			strLCD("Checksum : ");
			u32LCD(checksum);
			delayMS(3000);
			cmdLCD(0x01);
		}
		if(setPoint==temperature)
		{
			IOSET0 = 1<<BUZZER_PIN;
			delayMS(100);
			IOCLR0 = 1<<BUZZER_PIN;
		}
		store_DHT11_to_EEPROM(humidity,temperature,&eeprom_index);
		if(SEC==59)
		{
			interruptFlag=0;
			gcount++;
			if(gcount==UPDATE_TIME)
			{	
				updateToCloud(eeprom_index);
			}
		}
	}
}
u8* convertToString(u8 num)
{
	static u8 ptr[10];
	int i=0;
	while(num)
	{
		ptr[i]=num%10+48;
		num/=10;
		i++;
	}
	ptr[i]='\0';
	mystrrev(ptr);
	return ptr;
}
void mystrrev(u8* ptr)
{
	u8 ch;
	int i=0,j=strlen(ptr)-1;
	for(;i<j;i++,j--)
	{
		  ch = ptr[i];
		  ptr[i] = ptr[j];
		  ptr[j] = ch;
	}
}
