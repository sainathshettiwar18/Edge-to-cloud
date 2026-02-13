#include <LPC214x.h>
#include "types.h"
#include "delay.h"
#include "lcd_defines.h"
#include "defines.h"
void WriteLCD(u8 byte)
{
	IOCLR0 = 1<<LCD_RW;
	WRITEBYTE(IOPIN0,LCD_DATA,byte);
	IOSET0 = 1<<LCD_EN;
	delayUS(1);
	IOCLR0 = 1<<LCD_EN;
	delayMS(2);
}
void cmdLCD(u8 cmdByte)
{
	IOCLR0 = 1<<LCD_RS;
	WriteLCD(cmdByte);
}
void Init_LCD(void)
{
	IODIR0|=(0xFF<<LCD_DATA)|(1<<LCD_RS)|(1<<LCD_RW)|(1<<LCD_EN);
	delayMS(15);
	cmdLCD(0x30);
	delayMS(4);
	delayUS(100);
	cmdLCD(0x30);
	delayUS(100);
	cmdLCD(0x30);
	cmdLCD(MODE_8BIT_2LINE);
	cmdLCD(DISP_ON_CUR_ON);
	cmdLCD(CLR_LCD);
	cmdLCD(SHIFT_CUR_RIGHT);
}
void charLCD(u8 asciival)
{
	IOSET0 = 1<<LCD_RS;
	WriteLCD(asciival);
}
void strLCD(u8* str)
{
	while(*str)
		charLCD(*str++);
}
void u32LCD(u32 n)
{
	s32 i=0;
	u8 a[10];
	if(n==0)
	{
		charLCD('0');
	}
	else
	{
		while(n>0)
		{
			a[i++] = n%10+48;
			n/=10;
		}
		for(--i;i>=0;i--)
		{
			charLCD(a[i]);
		}
	}
}
void s32LCD(s32 num)
{
	if(num<0)
	{
		charLCD('-');
		num = -num;
	}
	u32LCD(num);
}
void f32LCD(f32 fnum,u32 nDP)
{
	u32 num,i;
	if(fnum<0.0)
	{
		charLCD('-');
		fnum = -fnum;
	}
	num = fnum;
	u32LCD(num);
	charLCD('.');
	for(i=0;i<nDP;i++)
	{
		fnum = (fnum-num)*10;
		num = fnum;
		charLCD(num+48);
	}
}
void buildCGRAM(u8* p,u8 nBytes)
{
	u32 i;
	cmdLCD(GOTO_CGRAM_START);
	IOSET0 = 1<<LCD_RS;
	for(i=0;i<nBytes;i++)
	{
		WriteLCD(p[i]);
	}
	cmdLCD(GOTO_LINE1_POS0);
}
