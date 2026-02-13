#include "types.h"
#include <LPC214x.h>
#include "pin_function_defines.h"
void cfgPortPinFunc(u32 portNo,u32 pinNo,u32 pinFunc)
{
	if(portNo==0)
	{
		if(pinNo<=15)
		{
			PINSEL0 = (PINSEL0&~(3<<(pinNo*2)))|(pinFunc<<(pinNo*2));
		}
		else if(pinNo>15 && pinNo<=31)
		{
			PINSEL1 = (PINSEL1&~(3<<((pinNo-16)*2)))|(pinFunc<<((pinNo-16)*2));
		}
	}
}
