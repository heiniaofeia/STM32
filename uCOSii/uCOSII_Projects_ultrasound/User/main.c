/*
 * @file   : main.c
 * @author : DragonFly
 * @version: V1.0.0
 * @date   : 2016.12.13
 * @history:
 * @details: main source file
 */
#include "stm32f10x.h"
#include <stdio.h>
#include <string.h>

#include "includes.h"
#include "app.h"
#include "app_cfg.h"
#include "bsp.h"



/*
 * @function: Main
 * @details : 
 * @input   : NULL
 * @output  : NULL
 * @return  : NULL
 */ 
int main(void)
{
	/* Peripheral initialization */
	BSP_Init();
	OSInit();

//	OSTaskCreate(Task_Start, (void *)0, &startup_task_stk[STARTUP_TASK_STK_SIZE - 1], TASK_STARTUP_PRIO);
	OSTaskCreateExt((void (*)(void *))Task_Start,
					(void *)0,
					(OS_STK *)&startup_task_stk[STARTUP_TASK_STK_SIZE - 1],
					(INT8U)TASK_STARTUP_PRIO,
					(INT16U)TASK_STARTUP_PRIO,
					(OS_STK *)&startup_task_stk[0],
					(INT32U) STARTUP_TASK_STK_SIZE,
					(void*)0,
					(INT16U)(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));
	
	OSStart();
	
	
    return 0;
}
/*********************************************END OF FILE**********************/
