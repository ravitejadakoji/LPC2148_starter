#include <lpc214x.h>
#include "rtc.h"

void RTC_Init(void)
{
	CCR = ((1<<RTC_CLKEN) | (1<<RTC_CLKSRC));
}

/*********************************************/

void RTC_SetDT(rtc_st *rtc)
{
	SEC = rtc->sec;
	MIN = rtc->min;
	HOUR = rtc->hour;
	DOW = rtc->weekday;
	DOM = rtc->date;
	MONTH = rtc->month;
	YEAR = rtc->year;
}


/*********************************************/

void RTC_GetDT(rtc_st *rtc)
{
	rtc->sec = SEC;
	rtc->min = MIN;
	rtc->hour = HOUR;
	rtc->weekday = DOW;
	rtc->date = DOM;
	rtc->month = MONTH;
	rtc->year = YEAR;
}
/**********************************************/
