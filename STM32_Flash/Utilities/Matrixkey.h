#ifndef __MATRIXKEY_H__
#define __MATRIXKEY_H__

#include "stm32f10x.h"
#include "bsp_SysTick.h"
#include "1602.h"

#define KEY_PORT GPIOE


void Matrixkey_Init(void);
unsigned char Get_KeyValue(void);

#endif
/* end of SysTick_Driver.h -------------------------------------------------------------*/

