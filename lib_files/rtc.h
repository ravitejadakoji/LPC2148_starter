#ifndef __RTC_H__
#define __RTC_H__

#include "stdutils.h"

/*********************

LPC2148 RTC Structure
*********************/

typedef struct
{
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t weekday;
	uint8_t date;
	uint8_t month;
	uint16_t year;
}rtc_st;


/***************************
RTC Register Bit Locations
****************************/

#define RTC_CLKEN 0
#define RTC_CLKSRC 4

/*******************************
LPC2148 RTC Function Prototypes
*******************************/

void RTC_Init(void);
void RTC_SetDT(rtc_st *rtc);
void RTC_GetDT(rtc_st *rtc);


#endif
