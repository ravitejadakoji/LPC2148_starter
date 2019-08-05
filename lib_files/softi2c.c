#include "softi2c.h"
#include "gpio.h"
#include "delay.h"

uint8_t PINSDA;
uint8_t PINSCL;

/**********************************
 SoftI2C Local Function Prototypes
 **********************************/

static void softi2c_Clock(void);
static void softi2c_Ack(void);
static void softi2c_NoAck(void);

/*************************
 SoftI2C Local Functions
 ************************/
 
 static void softi2c_Clock(void)
 {
	 delay_us(1);
	 GPIO_PinWrite(PINSCL,HIGH);
	 delay_us(1);
	 GPIO_PinWrite(PINSDA,LOW);
 }
 
 /*********************************/
 
 static void softi2c_Ack(void)
 {
	 GPIO_PinWrite(PINSDA,LOW);
	 softi2c_Clock();
	 GPIO_PinWrite(PINSDA,HIGH);
 }
 
 /*********************************/
 
 static void softi2c_NoAck(void)
 {
	 GPIO_PinWrite(PINSDA,HIGH);
	 softi2c_Clock();
	 GPIO_PinWrite(PINSCL,HIGH);
 }
 
 /*********************************/
 
 /********************************
 SoftI2C Functions
 ********************************/
 
 void SoftI2C_Init(uint8_t var_sdaPin, uint8_t var_sclPin)
 {
	 PINSDA = var_sdaPin;
	 PINSCL = var_sclPin;
	 
	 GPIO_PinDir(PINSDA, OUTPUT);
	 GPIO_PinDir(PINSCL, OUTPUT);
}
 
/***********************************/

void SoftI2C_Start(void)
{
	GPIO_PinWrite(PINSCL, LOW);
	GPIO_PinWrite(PINSDA, HIGH);
	
	delay_us(1);
	
	GPIO_PinWrite(PINSCL, HIGH);
	
	delay_us(1);
	
	GPIO_PinWrite(PINSDA, LOW);
	
	delay_us(1);
	
	GPIO_PinWrite(PINSCL, LOW);
}

/***********************************/

void SoftI2C_Stop(void)
{
	GPIO_PinWrite(PINSCL, LOW);
	
	delay_us(1);
	
	GPIO_PinWrite(PINSDA, LOW);
	
	delay_us(1);
	
	GPIO_PinWrite(PINSCL, HIGH);
	
	delay_us(1);
	
	GPIO_PinWrite(PINSDA, HIGH);
}

/*********************************/

void SoftI2C_Write(uint8_t var_i2cData)
{
	uint8_t i;
	
	for(i=0;i<8;i++)
	{
		GPIO_PinWrite(PINSDA,GetBitStatus(var_i2cData,7));
		softi2c_Clock();
		var_i2cData = var_i2cData << 1;
	}
}

/************************************/

uint8_t SoftI2C_Read(uint8_t var_i2cAck)
{
	uint8_t i, v_i2cData = 0x00;
	
	GPIO_PinDir(PINSDA, INPUT);
	
	for(i=0;i<8;i++)
	{
		delay_us(1);
		GPIO_PinWrite(PINSCL, HIGH);
		delay_us(1);
		
		v_i2cData = v_i2cData << 1;
		v_i2cData = v_i2cData | GPIO_PinRead(PINSDA);
		
		GPIO_PinWrite(PINSCL, LOW);
	}
	
	GPIO_PinDir(PINSDA, OUTPUT);
	
	if(var_i2cAck == 1)
	{
		softi2c_Ack();
	}
	
	else
	{
		softi2c_NoAck();
	}
	
	return v_i2cData;
}

/*********************************************/

