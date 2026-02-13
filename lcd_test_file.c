#include "types.h"
#include "delay.h"
#include "lcd_defines.h"
#include "lcd.h"
u8 cgramLUT[8] = {0x15,0x15,0x15,0x1F,0x04,0x04,0x04,0x04};
int main()
{
	Init_LCD();
	while(1)
	{
		cmdLCD(CLR_LCD);
		charLCD('H');
		cmdLCD(GOTO_LINE2_POS0);
		strLCD("TESTING");
		delayMS(100);
		cmdLCD(CLR_LCD);
		u32LCD(123456789);
		cmdLCD(GOTO_LINE2_POS0);
		f32LCD(1234.56789,5);
		delayMS(100);
		cmdLCD(CLR_LCD);
		buildCGRAM(cgramLUT,8);
		charLCD(0);
		delayMS(100);
	}
}
