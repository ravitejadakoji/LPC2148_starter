#include <lpc214x.h>
#include "clockinit.h"

#define PLOCK 0x00000400

void ClockInit(void)
{
	PLL0CON = 0x01;
	PLL0CFG = 0x24;
	
	PLL0FEED = 0xAA;
	PLL0FEED = 0x55;
	
	while(!(PLL0STAT & PLOCK))
	{
		;
	}
	PLL0CON = 0x03;
	
	PLL0FEED = 0xAA;
	PLL0FEED = 0x55;
	
	VPBDIV = 0x01;
}
