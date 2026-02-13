#include "types.h"
#include "rtc.h"
#include "interrupts.h"
#include "dht11_eeprom.h"
#include <string.h>
#include "esp01.h"
extern u8 eeprom_index;
u8 humid,temper;
u8 hBuff[10],tBuff[10];
u8* convertToStr(u8);
u8* mystrcpy(u8*,u8*);
void mystrev(u8*);
u32 mystrlen(u8*);
void updateToCloud(u8 eeprom_index)
{
	u32 in,ind=1;
	for(in=0;in<eeprom_index-1;in++,ind++)
	{
		read_DHT11_record(ind,&humid,&temper);
		mystrcpy(hBuff,convertToStr(humid));
		mystrcpy(tBuff,convertToStr(temper));
		esp01_sendToThingspeak(tBuff,0);
		esp01_sendToThingspeak(hBuff,1);
	}
}
u8* convertToStr(u8 num)
{
	u8 ind=0;
	static u8 str[10];
	if(num==0)
	{
		str[ind++]='0';
		str[ind]='\0';
		return str;
	}
	while(num)
	{
		str[ind++] = num%10+48;
		num/=10;
	}
	str[ind]='\0';
	mystrev(str);
	return str;
}
u8* mystrcpy(u8* dstr,u8* sstr)
{
	u32 i=0;
	while(sstr[i])
	{
		dstr[i]=sstr[i];
		i++;
	}
	dstr[i]='\0';
	return dstr;
}
u32 mystrlen(u8* p)
{
	u32 i=0;
	while(p[i])
		i++;
	return i;
}
void mystrev(u8* p)
{
	u32 i,j;
	u8 t;
	u32 len = mystrlen(p)-1;
	for(i=0,j=len;i<j;i++,j--)
	{
		t = p[i];
		p[i] = p[j];
		p[j] = t;
	}
}
