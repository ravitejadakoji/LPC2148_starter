#include <stdarg.h>
#include "uart.h"
#include "gpio.h"

void UART_Init(uint8_t var_uartCha, uint32_t var_baudRate)
{
	switch(var_uartCha)
	{
		case 0:
			GPIO_PinFun(P0_0, PINSEL_FUN_1);
			GPIO_PinFun(P0_1, PINSEL_FUN_1);
			U0LCR = 0x83;
			UART_SetBaudRate(var_uartCha, var_baudRate);
			U0LCR = 0x03;
			break;
		
		case 1:
			GPIO_PinFun(P0_8, PINSEL_FUN_1);
			GPIO_PinFun(P0_9, PINSEL_FUN_1);
			U1LCR = 0x83;
			UART_SetBaudRate(var_uartCha, var_baudRate);
			U1LCR = 0x03;
			break;
	}
}

/*********************************************************/

void UART_SetBaudRate(uint8_t var_uartCha, uint32_t var_baudRate)
{
	uint32_t v_regVal;
	switch(var_uartCha)
	{
		case 0:
			v_regVal = pclk / (16*var_baudRate);
			U0DLL = (uint8_t) v_regVal & 0xFF;
			U0DLM = (uint8_t) (v_regVal >> 0x08) & 0xFF;
			break;
		
		case 1:
			v_regVal = pclk / (16*var_baudRate);
			U1DLL = v_regVal & 0xFF;
			U1DLM = (v_regVal >> 0x08) & 0xFF;
			break;
			
	}
}

/*********************************************************/

void UART_TXChar(uint8_t var_uartCha, char var_txData)
{
	switch(var_uartCha)
	{
		case 0:
			while (IsBitCleared(U0LSR, UART_THRE));
			U0THR = var_txData;
			break;
		
		case 1:
			while (IsBitCleared(U1LSR, UART_THRE));
			U1THR = var_txData;
			break;
	}
}

/*********************************************************/

char UART_RXChar(uint8_t var_uartCha)
{
	char ch = 0;
	switch(var_uartCha)
	{
		case 0:
			while (IsBitCleared(U0LSR, UART_RDR));
			ch = U0RBR;
			break;
		
		case 1:
			while (IsBitCleared(U1LSR, UART_RDR));
			ch = U1RBR;
			break;
	}
	return ch;
}

/**************************************************/

#if ((Enable_UART_TXSTR == 1) || (Enable_UART_Printf == 1))

void UART_TXSTR(uint8_t var_uartCha, char *ptr_str)
{
	while(*ptr_str)
		UART_TXChar(var_uartCha, *ptr_str++);
}

#endif

/***************************************************/

#if (Enable_UART_RXSTR == 1)

uint8_t UART_RXSTR(uint8_t var_uartCha, char *ptr_str)
{
	char c;
	uint8_t len = 0;
	while(1)
	{
		c = UART_RXChar(var_uartCha);
		UART_TXChar(var_uartCha, c); /*******/
		
		if((c == '\r') || (c == '\n'))
		{
			if(len != 0)
			{
				ptr_str[len] = 0;
				break;
			}
		}
		
		else if ((c == '\b') && (len != 0))
		{
			len--;
		}
		
		else
		{
			ptr_str[len] = c;
			len++;
		}
	
	}
	return len;
}

#endif

#if ((Enable_UART_TXNum == 1) || (Enable_UART_TXFloat == 1) || (Enable_UART_Printf == 1))
void UART_TXNum(uint8_t var_uartCha, uint8_t var_numSys, uint32_t var_number_32, uint8_t var_numOfDigitsToTX)
{
	uint8_t i=0,arr[10];
	
	if(var_numSys == C_BINARY)
	{
		while(var_numOfDigitsToTX != 0)
		{
			i = GetBitStatus(var_number_32,(var_numOfDigitsToTX-1));
			UART_TXChar(var_uartCha, DecToAscii(i));
			var_numOfDigitsToTX--;
		}
	}
	
	else if(var_number_32 == 0)
	{
		//for(i=0;((i<var_numOfDigitsToTX)&&(i<C_MaxDigitsToTX));i++)
			UART_TXChar(var_uartCha, '0');
	}
	
	else
	{
		for(i=0;i<var_numOfDigitsToTX;i++)
		{
			if(var_number_32 != 0)
			{
				arr[i] = GetMod32(var_number_32,var_numSys);
				var_number_32 = var_number_32 / var_numSys;
			}
			
			else if((var_numOfDigitsToTX == C_DefaultDigitsToTX) || (var_numOfDigitsToTX > C_MaxDigitsToTX))
			{
				break;
			}
			
			else
			{
				arr[i] = 0;
			}
		}
		while(i)
		{
			UART_TXChar(var_uartCha, HexToAscii(arr[i-1]));
			i--;
		}
	}
}

#endif

/*********************************/

#if (Enable_UART_TXFloat == 1)
void UART_TXFloat(uint8_t var_uartCha, float var_floatNum_32)
{
	uint32_t v_tempNum_32;
	
	v_tempNum_32 = (uint32_t) var_floatNum_32;
	UART_TXNum(var_uartCha, C_DECIMAL, v_tempNum_32, C_DefaultDigitsToTX);
	
	UART_TXChar(var_uartCha, '.');
	
	var_floatNum_32 = var_floatNum_32 - v_tempNum_32;
	v_tempNum_32 = var_floatNum_32 * 1000000;
	UART_TXNum(var_uartCha, C_DECIMAL, v_tempNum_32, C_DefaultDigitsToTX);
}

#endif

/******************************************/

#if (Enable_UART_Printf == 1)
void UART_Printf(uint8_t var_uartCha, const char *argList, ...)
{
	const char *ptr;
	va_list argp;
	
	sint16_t v_num_16;
	sint32_t v_num_32;
	uint16_t v_num_u16;
	uint32_t v_num_u32;
	char *str;
	char ch;
	uint8_t v_numOfDigitsToTX;
	double v_floatNum_32;
		
	va_start(argp, argList);
	
	for(ptr=argList;*ptr != '\0';ptr++)
	{
		ch = *ptr;
		if(ch == '%')
		{
			ptr++;
			ch = *ptr;
			if((ch>=0x30) && (ch<=0x39))
			{
				v_numOfDigitsToTX = 0;
				while((ch>=0x30) && (ch<=0x39))
				{
					v_numOfDigitsToTX = (v_numOfDigitsToTX * 10) + (ch - 0x30);
					ptr++;
					ch = *ptr;
				}
			}
			
			else
			{
				v_numOfDigitsToTX = C_MaxDigitsToTXPrintf;
			}
			
			switch(ch)
			{
				case 'C':
				case 'c':
					ch = va_arg(argp,int);
					UART_TXChar(var_uartCha, ch);
					break;
				
				case 'd':
					v_num_16 = va_arg(argp,int);
				#if (Enable_UART_TXNum == 1)
					if(v_num_16<0)
					{
						v_num_16 = -v_num_16;
						UART_TXChar(var_uartCha, '-');
					}
					UART_TXNum(var_uartCha, C_DECIMAL,v_num_16,v_numOfDigitsToTX);
				#endif
					break;
					
				case 'D':
					v_num_32 = va_arg(argp,sint32_t);
				#if (Enable_UART_TXNum == 1)
					if(v_num_32<0)
					{
						v_num_32 = -v_num_32;
						UART_TXChar(var_uartCha, '-');
					}
					UART_TXNum(var_uartCha, C_DECIMAL, v_num_32, v_numOfDigitsToTX);
				#endif	
					break;
					
				case 'u':
					v_num_u16 = va_arg(argp,int);
				#if (Enable_UART_TXNum == 1)
					UART_TXNum(var_uartCha, C_DECIMAL, v_num_u16, v_numOfDigitsToTX);
				#endif
					break;
				
				case 'U':
					v_num_u32 = va_arg(argp,uint32_t);
				#if (Enable_UART_TXNum == 1)
					UART_TXNum(var_uartCha, C_DECIMAL, v_num_u32, v_numOfDigitsToTX);
				#endif
					break;
				
				case 'x':
					v_num_u16 = va_arg(argp,int);
				#if (Enable_UART_TXNum == 1)
					UART_TXNum(var_uartCha, C_HEX, v_num_u16, v_numOfDigitsToTX);
				#endif
					break;
				
				case 'X':
					v_num_u32 = va_arg(argp,uint32_t);
				#if (Enable_UART_TXNum == 1)
					UART_TXNum(var_uartCha, C_HEX, v_num_u32, v_numOfDigitsToTX);
				#endif
					break;
				
				case 'b':
					v_num_u16 = va_arg(argp,int);
				#if (Enable_UART_TXNum == 1)
					if(v_numOfDigitsToTX == C_MaxDigitsToTXPrintf)
					{
						v_numOfDigitsToTX = 16;
					}
					
					UART_TXNum(var_uartCha, C_BINARY, v_num_u16, C_MaxDigitsToTXPrintf);
				#endif
					break;
					
				case 'B':
					v_num_u32 = va_arg(argp,uint32_t);
				#if (Enable_UART_TXNum == 1)
					if(v_numOfDigitsToTX == C_MaxDigitsToTXPrintf)
					{
						v_numOfDigitsToTX = 32;
					}
					UART_TXNum(var_uartCha, C_BINARY, v_num_u32, C_MaxDigitsToTXPrintf);
				#endif
					break;
					
				case 'f':
				case 'F':
					v_floatNum_32 = va_arg(argp,double);
				#if (Enable_UART_TXFloat == 1)
					UART_TXFloat(var_uartCha, v_floatNum_32);
				#endif
					break;
					
				case 's':
				case 'S':
					str = va_arg(argp,char *);
					UART_TXSTR(var_uartCha, str);
					break;
					
				case '%':
					UART_TXChar(var_uartCha, '%');
					break;
			}
		}
		
		else
		{
			UART_TXChar(var_uartCha, ch);
		}
	}
	va_end(argp);
}

#endif

/********************************************/

