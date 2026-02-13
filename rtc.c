#include <LPC21xx.H>

#include "rtc_defines.h"
#include "lcd_defines.h"
#include "lcd.h"
#include "types.h"
void Init_RTC(void) 
{
  // Disable and reset the RTC
	CCR = RTC_RESET;
  // Set prescaler integer and fractional parts
	PREINT = PREINT_VAL;
	PREFRAC = PREFRAC_VAL;
  
  // Enable the RTC
	CCR = RTC_ENABLE;  
}
