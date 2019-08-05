#ifndef __SOFTI2C_H__
#define __SOFTI2C_H__

#include "stdutils.h"

/***********************
 SoftI2C Function Prototypes
 **********************/

void SoftI2C_Init(uint8_t var_sdaPin, uint8_t var_sclPin);
void SoftI2C_Start(void);
void SoftI2C_Stop(void);
void SoftI2C_Write(uint8_t var_i2cData);
uint8_t SoftI2C_Read(uint8_t var_i2cAck);

#endif
