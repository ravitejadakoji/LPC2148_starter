#ifndef __PWM_H__
#define __PWM_H__

#include "stdutils.h"

/***************************************
LPC2148 PWM Configuration Bits Position
****************************************/

#define PWM_1 1u	/*((uint32_t)1<<0)*/
#define PWM_2 2u	/*((uint32_t)1<<1)*/
#define PWM_3 4u	/*((uint32_t)1<<2)*/
#define PWM_4 8u	/*((uint32_t)1<<5)*/
#define PWM_5 16u	/*((uint32_t)1<<4)*/
#define PWM_6 32u	/*((uint32_t)1<<5)*/

#define PWM_CHA_MASK 0x3Fu

#define TCR_CNT_EN 	0x00000001
#define TCR_RESET 	0x00000002
#define TCR_PWM_EN 	0x00000008

#define PWMSEL2 (1<<2)
#define PWMSEL3 (1<<3)
#define PWMSEL4 (1<<4)
#define PWMSEL5 (1<<5)
#define PWMSEL6 (1<<6)

#define PWMENA1 (1<<9)
#define PWMENA2 (1<<10)
#define PWMENA3 (1<<11)
#define PWMENA4 (1<<12)
#define PWMENA5 (1<<13)
#define PWMENA6 (1<<14)

#define LER0_EN (1<<0)
#define LER1_EN (1<<1)
#define LER2_EN (1<<2)
#define LER3_EN (1<<3)
#define LER4_EN (1<<4)
#define LER5_EN (1<<5)
#define LER6_EN (1<<6)

#define PWM_CYCLE 255

/**********************************
LPC2148 PWM Function Prototypes
**********************************/

void PWM_Init(uint32_t var_pwmPeriod);
void PWM_SetDutyCycle(uint32_t var_pwmPin, uint32_t var_dutyCycle);
void PWM_Start(uint32_t var_pwmPin);
void PWM_Stop(uint32_t var_pwmPin);

/***************************************/

#endif
