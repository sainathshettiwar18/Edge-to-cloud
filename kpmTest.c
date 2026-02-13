#include "types.h"
#include "delay.h"
#include "kpm.h"
#include "lcd_defines.h"
#include "lcd.h"
u32 keyV;
int main()
{
	Init_LCD();
	Init_KPM();
	strLCD("KPM TEST");
	while(1)
	{
		cmdLCD(GOTO_LINE2_POS0);
		keyV = KeyScan();
		while(colScan()==0);
		u32LCD(keyV);
		cmdLCD(GOTO_LINE2_POS0);
		strLCD("  ");
	}
}
