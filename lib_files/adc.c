#include "adc.h"
#include "delay.h"
#include "stdutils.h"
#include "clockinit.h"
#include "gpio.h"

const adcChaConfig_st ADC0Config[C_MaxADC0Cha] = 
{
	{P_NC, PINSEL_FUN_0},
	{P0_28, PINSEL_FUN_1},
	{P0_29, PINSEL_FUN_1},
	{P0_30, PINSEL_FUN_1},
	{P0_25, PINSEL_FUN_1},
	{P_NC, PINSEL_FUN_0},
	{P0_4, PINSEL_FUN_3},
	{P0_5, PINSEL_FUN_3},
};

const adcChaConfig_st ADC1Config[C_MaxADC1Cha] = 
{
	{P0_6, PINSEL_FUN_3},
	{P0_8, PINSEL_FUN_3},
	{P0_10, PINSEL_FUN_3},
	{P0_12, PINSEL_FUN_3},
	{P0_13, PINSEL_FUN_3},
	{P0_15, PINSEL_FUN_3},
	{P0_21, PINSEL_FUN_2},
	{P0_22, PINSEL_FUN_1},
};

/*******************************************************/

void ADC_Init(void)
{
	uint32_t v_pclk;
	v_pclk = ADC_GetClkDivVal();
	
	AD0CR = ((1 << ADC_PDN) | v_pclk); 
	AD1CR = ((1 << ADC_PDN) | v_pclk); 
}

/******************************************************/

uint16_t ADC_GetADCVal(uint8_t var_adcCha)
{
	uint16_t v_adcRes;
	
	if(var_adcCha <= ADC0_7)
	{
		GPIO_PinFun(ADC0Config[var_adcCha].pinNum, ADC0Config[var_adcCha].pinFunSel);
		AD0CR = ((AD0CR & 0xFFFFFF00) | (0x01 << var_adcCha));
		
		delay_us(10);
		
		BitSet(AD0CR, ADC_START);
		while(GetBitStatus(AD0GDR, ADC_DONE) == 0);
		
		v_adcRes = ((AD0GDR >> ADC_RESULT) & 0x3FF);
		BitClear(AD0CR, ADC_START);
	}
	
	else if ((var_adcCha >= ADC1_0) && (var_adcCha <= ADC1_7))
	{
		var_adcCha = var_adcCha - ADC1_0;
		
		GPIO_PinFun(ADC1Config[var_adcCha].pinNum, ADC1Config[var_adcCha].pinFunSel);
		AD1CR = ((AD1CR & 0xFFFFFF00) | (0x01 << var_adcCha));
		
		delay_us(10);
		
		BitSet(AD1CR, ADC_START);
		while(GetBitStatus(AD1GDR, ADC_DONE) == 0);
		
		v_adcRes = ((AD1GDR >> ADC_RESULT) & 0x3FF);
		BitClear(AD1CR, ADC_START);
	}
	
	else
		{
			v_adcRes = 0;
		}
		
		return v_adcRes;
	}
	
