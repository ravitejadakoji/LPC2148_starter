#ifndef __EEPROM_H__
#define __EEPROM_H__

#include "stdutils.h"

/************************
AT24CXX IC Macros
*************************/

#define AT24C01 	128u 		/*1kb 1024b = 128B*/
#define AT24C02 	256u 		/*2kb 2048b = 256B*/
#define AT24C04 	512u 		/*4kb 4096b = 512B*/
#define AT24C08 	1024u 	/*8kb 8192b = 1024B*/
#define AT24C16 	2048u 	/*16kb 16384b = 2048B*/
#define AT24C32 	4096u 	/*32kb 32768b = 4096B*/
#define AT24C64 	8192u 	/*64kb 65536b = 8192B*/
#define AT24C128 	16384u 	/*128kb = 16384B*/
#define AT24C256 	32768u 	/*256kb = 32768B*/


/**********************************
AT24CXX IC Selection and Constants
************************************/

//#define C_EEPROMICType AT24C16

//#define C_MaxEEPROMSize C_EEPROMICType
#define C_EEPROMIDWrite 0xA0u
#define C_EEPROMIDRead 0xA1u

/*************************************
Configs to enable/disable EEPROM API's
**************************************/

#define Enable_EEPROM_WriteNBytes 1
#define Enable_EEPROM_ReadNBytes 	1
#define Enable_EEPROM_WriteString 1
#define Enable_EEPROM_ReadString 	1
#define Enable_EEPROM_Erase 			1

/**********************************
EEPROM Function Prototypes
**********************************/

void EEPROM_Init(uint16_t var_eepromIC, uint8_t var_sdaPin, uint8_t var_sclPin);

void EEPROM_WriteByte(uint16_t var_eepromAdd, uint8_t var_eepromData);
uint8_t EEPROM_ReadByte(uint16_t var_eepromAdd);

void EEPROM_WriteNBytes(uint16_t var_eepromAdd, uint8_t *ptr_ramAdd, uint16_t var_noOfBytes);
void EEPROM_ReadNBytes(uint16_t var_eepromAdd, uint8_t *ptr_ramAdd, uint16_t var_noOfBytes);

void EEPROM_WriteString(uint16_t var_eepromAdd, char *ptr_strptr);
void EEPROM_ReadString(uint16_t var_eepromAdd, char *ptr_strAdd);

void EEPROM_Erase(void);


#endif
