#include "myheader.h"
u8 humidity,temperature;
u8 id=1,response;
extern u8 setPoint;
int main()
{
	Init_RTC();
	RTC_nmin_Alarm();
	Init_LCD();
	Init_eint0();
	InitUART0();
	Init_i2c();
	Init_KPM();
	strLCD("ESP01 CONNECTING");
	delayMS(500);
	cmdLCD(CLR_LCD);
	//esp01_connectAP();
	WRITEBIT(IODIR0,BUZZER_PIN,1);
	while(1)
	{
		int status = dht11_Read(&humidity,&temperature);

		if(status==0)

		{

			cmdLCD(CLR_LCD);

			strLCD("T: ");

			u32LCD(temperature);

			cmdLCD(GOTO_LINE2_POS0);

			strLCD("RH: ");

			u32LCD(humidity);

		}

		else if(status==1)

		{

			cmdLCD(CLR_LCD);

			strLCD("NO RESPONSE");

		}

		else if(status==2)

		{

			cmdLCD(CLR_LCD);

			strLCD("CHECKSUM ERROR!");

		}
		
		
		//display_DHT11(&humidity,&temperature);
		//esp01_sendToThingspeak("32",0);
		//delayMS(200);
		//esp01_sendToThingspeak("80",1);
		//store_DHT11_to_EEPROM(humidity,temperature);
		//if(temperature>=setPoint)
		//{
		//	setPointAction();
	//	}
	//	else
		//	WRITEBIT(IOPIN0,BUZZER_PIN,0);
		
	}
}
