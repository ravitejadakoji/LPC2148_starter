#ifndef __KEYPAD_H__
#define	__KEYPAD_H__

#include "gpio.h"
#include "stdutils.h"

/*************************************
Keypad Rows and Columns Configuration
**************************************/

#define C_MaxRows (4)
#define C_MaxCols (4)
#define C_DebounceMicro (10)
#define C_DefaultKey ('x')

/****************************
 Keypad Function Prototypes
 ***************************/

uint8_t KEYPAD_GetKey(void);
void KEYPAD_Init(
        gpioPins_et row_0,
        gpioPins_et row_1,
        gpioPins_et row_2,
        gpioPins_et row_3,
        gpioPins_et col_0,
        gpioPins_et col_1,
        gpioPins_et col_2,
        gpioPins_et col_3);

#endif	/* KEYPAD_H */
