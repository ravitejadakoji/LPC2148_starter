#include <lpc214x.h>
#include "pwm.h"
#include "gpio.h"
#include "stdutils.h"

static uint32_t v_PWMInitFlag = 0;

/*********************************************/

void PWM_Init(uint32_t var_pwmPeriod)
{
	PWMTCR = TCR_RESET;
	PWMPR = 0x00;
	PWMMCR = var_pwmPeriod;
	PWMMR0 = LER0_EN;
	PWMTCR = TCR_CNT_EN | TCR_PWM_EN;
}

/********************************************/

void PWM_SetDutyCycle(uint32_t var_pwmPin, uint32_t var_dutyCycle)
{
	uint32_t v_pinSel = 0;
	if(v_PWMInitFlag == 0)
	{
		PWM_Init(PWM_CYCLE);
		v_PWMInitFlag = 1;
	}
	
	var_pwmPin = var_pwmPin & PWM_CHA_MASK;
	
	while(var_pwmPin)
	{
		v_pinSel = (((~var_pwmPin)+1)&var_pwmPin);
		var_pwmPin = var_pwmPin & (~v_pinSel);
		
		switch(v_pinSel)
		{
			case PWM_1:
				GPIO_PinFun(P0_0,PINSEL_FUN_2);
				PWMMR1 = var_dutyCycle;
				PWMLER |= LER1_EN;
				break;
				
			case PWM_2:
				GPIO_PinFun(P0_7,PINSEL_FUN_2);
				PWMMR2 = var_dutyCycle;
				PWMLER |= LER2_EN;
				break;
			
			case PWM_3:
				GPIO_PinFun(P0_1,PINSEL_FUN_2);
				PWMMR3 = var_dutyCycle;
				PWMLER |= LER3_EN;
				break;
			
			case PWM_4:
				GPIO_PinFun(P0_8,PINSEL_FUN_2);
				PWMMR4 = var_dutyCycle;
				PWMLER |= LER4_EN;
				break;
			
			case PWM_5:
				GPIO_PinFun(P0_21,PINSEL_FUN_1);
				PWMMR5 = var_dutyCycle;
				PWMLER |= LER5_EN;
				break;
			
			case PWM_6:
				GPIO_PinFun(P0_9,PINSEL_FUN_2);
				PWMMR6 = var_dutyCycle;
				PWMLER |= LER6_EN;
				break;
			
			default:
				break;
		}
		
	}
}

/**************************************************************/

void PWM_Start(uint32_t var_pwmPin)
{
	uint32_t v_pinSel = 0;
	if(v_PWMInitFlag == 0)
	{
		PWM_Init(PWM_CYCLE);
		v_PWMInitFlag = 1;
	}
	
	var_pwmPin = var_pwmPin & PWM_CHA_MASK;
	
	while(var_pwmPin)
	{
		v_pinSel = (((~var_pwmPin)+1)&var_pwmPin);
		var_pwmPin = var_pwmPin & (~v_pinSel);
		
		switch(v_pinSel)
		{
			case PWM_1:
				PWMPCR |= PWMENA1;
				break;
			
			case PWM_2:
				PWMPCR |= PWMENA2;
				break;
			
			case PWM_3:
				PWMPCR |= PWMENA3;
				break;
			
			case PWM_4:
				PWMPCR |= PWMENA4;
				break;
			
			case PWM_5:
				PWMPCR |= PWMENA5;
				break;
			
			case PWM_6:
				PWMPCR |= PWMENA6;
				break;
			
			default:
				break;
		}
	}
}

/**************************************************************/

void PWM_Stop(uint32_t var_pwmPin)
{
	uint32_t v_pinSel = 0;
	
	var_pwmPin = var_pwmPin & PWM_CHA_MASK;
	
	while(var_pwmPin)
	{
		v_pinSel = (((~var_pwmPin)+1)&var_pwmPin);
		var_pwmPin = var_pwmPin & (~v_pinSel);
		
		switch(v_pinSel)
		{
			case PWM_1:
				PWMPCR &= ~PWMENA1;
				break;
			
			case PWM_2:
				PWMPCR &= ~PWMENA2;
				break;
			
			case PWM_3:
				PWMPCR &= ~PWMENA3;
				break;
			
			case PWM_4:
				PWMPCR &= ~PWMENA4;
				break;
			
			case PWM_5:
				PWMPCR &= ~PWMENA5;
				break;
			
			case PWM_6:
				PWMPCR &= ~PWMENA6;
				break;
			
			default:
				break;
		}
	}
}

/****************************************/

