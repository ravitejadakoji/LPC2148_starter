#ifndef __UART_H__
#define __UART_H__

#include <lpc214x.h>
#include "clockinit.h"
#include "gpio.h"
#include "stdutils.h"

/**********************************
LPC2148 UART Baud Rate Min and Max
**********************************/

#define C_MinBaudRate 2400
#define C_MaxBaudRate 115200UL

/**********************************
LPC2148 UART Control Register Bits
**********************************/

#define UART_RDR 0x00u
#define UART_THRE 0x05u

/**********************************
LPC2148 UART Channel Configuration
**********************************/

#define C_UART0 0u
#define C_UART1 1u

#define C_MaxUARTCha 2u

/*******************************************
LPC2148 UART Macros to Enable/Disable API's
********************************************/

#define Enable_UART_TXSTR 1
#define Enable_UART_RXSTR 1
#define Enable_UART_TXNum 1
#define Enable_UART_TXFloat 1
#define Enable_UART_Printf 1

/****************************************
LPC2148	UART Constants and Macros
****************************************/

#define C_DefaultDigitsToTX 0xFFu
#define C_MaxDigitsToTX 10u
#define C_BinaryBitsToTX 16u
#define C_MaxDigitsToTXPrintf C_DefaultDigitsToTX

/*********************************
LPC2148 UART Function Prototypes
*********************************/

void UART_Init(uint8_t var_uartCha, uint32_t var_baudRate);
void UART_SetBaudRate(uint8_t var_uartCha, uint32_t var_baudRate);

void UART_TXChar(uint8_t var_uartCha, char var_txData);
char UART_RXChar(uint8_t var_uartCha);

void UART_TXSTR(uint8_t var_uartCha, char *ptr_str);
uint8_t UART_RXSTR(uint8_t var_uartCha, char *ptr_str);

void UART_TXNum(uint8_t var_uartCha, uint8_t var_numSys, uint32_t var_number_32, uint8_t var_numOfDigitsToTX);
void UART_TXFloat(uint8_t var_uartCha, float var_floatNum_32);

void UART_Printf(uint8_t var_uartCha, const char *argList, ...);

/**************************************************************/
#endif

