#include <lpc214x.h>
#include "gpio.h"
#include "stdutils.h"

void GPIO_PinFun(uint8_t var_pinNum, uint8_t var_pinFun)
{
	uint8_t v_portNum;
	v_portNum = var_pinNum >> 5;
	var_pinNum = var_pinNum & 0x1F;
	
	v_portNum = v_portNum * 2;
	if(var_pinNum >= 16)
	{
		v_portNum++;
		var_pinNum = var_pinNum - 16;
	}
	
	var_pinNum = var_pinNum * 2;
	
	switch(v_portNum)
	{
		case 0:
			PINSEL0 &= ~(0x03UL << var_pinNum);
			PINSEL0 |= (((uint32_t)var_pinFun) << var_pinNum);
			break;
		
		case 1:
			PINSEL1 &= ~(0x03UL << var_pinNum);
			PINSEL1 |= (((uint32_t)var_pinFun) << var_pinNum);
			break;
		
		case 2:
			PINSEL2 &= ~(0x03UL << var_pinNum);
			PINSEL2 |= (((uint32_t)var_pinFun) << var_pinNum);
			break;
	}
}

/***************************************************/

void GPIO_PinDir(uint8_t var_pinNum, uint8_t var_pinDir)
{
	uint8_t v_portNum;
	v_portNum = var_pinNum >> 5;
	var_pinNum = var_pinNum & 0x1F;
	
	switch(v_portNum)
	{
		case 0:
			UpdateBit(IO0DIR, var_pinNum, var_pinDir);
			break;
		
		case 1:
			UpdateBit(IO1DIR, (var_pinNum + 16), var_pinDir);
			break;
	}
}

/***************************************************/

void GPIO_PinWrite(uint8_t var_pinNum, uint8_t var_pinVal)
{
	uint8_t v_portNum;
	v_portNum = var_pinNum >> 5;
	var_pinNum = var_pinNum & 0x1F;
	
	switch(v_portNum)
	{
		case 0:
			UpdateBit(IO0DIR, var_pinNum, var_pinVal);
			break;
		
		case 1:
			UpdateBit(IO1DIR, (var_pinNum + 16), var_pinVal);
			break;
	}
}

/***************************************************/

uint8_t GPIO_PinRead(uint8_t var_pinNum)
{
	uint8_t v_portNum;
	uint8_t pinStatus = 0;
	
	v_portNum = var_pinNum >> 5;
	var_pinNum = var_pinNum & 0x1F;
	
	switch(v_portNum)
	{
		case 0:
			pinStatus = IsBitSet(IO0PIN, var_pinNum);
			break;
		
		case 1:
			pinStatus = IsBitSet(IO1PIN, (var_pinNum + 16));
			break;
	}
	return pinStatus;
}

/*******************************************************/
