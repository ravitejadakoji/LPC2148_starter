#ifndef __ADC_H__
#define	__ADC_H__

#include <lpc214x.h>
#include "stdutils.h"
#include "gpio.h"

/*********************************
LPC2148 ADC Macros and Constants
*********************************/

#define ADC_BURST 16u
#define ADC_START 24u
#define ADC_PDN 21u
#define ADC_EDGE 27u

#define ADC_DONE 31u
#define ADC_RESULT 6u

#define ADC_Clock_Freq 10000000
#define ADC_GetClkDivVal() (((pclk / (uint32_t)ADC_Clock_Freq) - 1u) << 8u)

/*********************************
LPC2148 ADC Channel Constants
*********************************/

#define ADC0_0 P_NC
#define ADC0_1 1u		//P0.28
#define ADC0_2 2u		//P0.29
#define ADC0_3 3u		//P0.30
#define ADC0_4 4u		//P0.25
#define ADC0_5 P_NC
#define ADC0_6 6u		//P0.4
#define ADC0_7 7u		//P0.5

#define ADC1_0 8u		//P0.6
#define ADC1_1 9u		//P0.8
#define ADC1_2 10u	//P0.10
#define ADC1_3 11u	//P0.12
#define ADC1_4 12u	//P0.13
#define ADC1_5 13u	//P0.15
#define ADC1_6 14u	//P0.21
#define ADC1_7 15u	//P0.22

#define C_MaxADC0Cha 8u
#define C_MaxADC1Cha 8u

typedef struct
{
	uint8_t pinNum;
	uint8_t pinFunSel;
}adcChaConfig_st;

/***************************************/

/***************************************
LPC2148 ADC Function Prototypes
***************************************/

void ADC_Init(void);
uint16_t ADC_GetADCVal(uint8_t var_adcCha);

/**************************************/

#endif

