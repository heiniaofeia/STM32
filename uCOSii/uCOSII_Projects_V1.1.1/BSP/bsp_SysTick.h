#ifndef __BSP_SYSTICK_H
#define __BSP_SYSTICK_H

#include "stm32f10x.h"

void SysTick_Init(void);
void Delay_us(__IO u32 nTime);
extern void TimingDelay_Decrement(void);

#endif /* __SYSTICK_H */
