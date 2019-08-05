#include <lpc214x.h>
#include "delay.h"

void delay_us (uint32_t count_us)
{
	uint32_t i=0,j=0;
	for(i=0;i<count_us;i++)
	{
		for(j=0;j<10;j++);
	}
}


void delay_ms (uint32_t count_ms)
{
	uint32_t i=0;
	for(i=0;i<count_ms;i++)
	{
		delay_us(1000);
	}
}

void delay_sec (uint32_t count_sec)
{
	uint32_t i=0;
	for(i=0;i<count_sec;i++)
	{
		delay_ms(1000);
	}
}
