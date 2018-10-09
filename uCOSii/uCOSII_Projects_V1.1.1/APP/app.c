/*
 * @file   : app.c
 * @author : DragonFly
 * @version: V1.0.0
 * @date   : 2016.12.21
 * @history:
 * @details: app source file
 */
#include "includes.h"
#include "app_cfg.h"
#include "app.h"
#include "system_stm32f10x.h"



/*---------------------------------------------------------------------------
                                Variable definition
----------------------------------------------------------------------------*/
/*
 * @details: 定义任务栈大小。
 */
OS_STK  startup_task_stk[STARTUP_TASK_STK_SIZE];	
OS_STK  task_led1_stk[TASK_LED1_STK_SIZE];
OS_STK  task_led2_stk[TASK_LED2_STK_SIZE];
OS_STK  task_matrikey_stk[TASK_MATRIXKEY_STK_SIZE];
OS_STK  task_lcd1602_stk[TASK_LCD1602_STK_SIZE];
OS_STK  task_ADC1_stk[TASK_ADC1_STK_SIZE];


/*---------------------------------------------------------------------------
                                Function definition
----------------------------------------------------------------------------*/
/*
 * @function: Task_Start
 * @details : 创建起始任务。
              只有OSTaskCreateExt()支持堆栈检测。注意不能在
			  OSTaskCreateExt()中调用OSTaskCreateExt()，否则会导致UCOS异常。
 * @input   : p_arg: 参数。
 * @output  : NULL
 * @return  : NULL
 */
void Task_Start(void *p_arg)
{
	(void)p_arg;                                                                // 'p_arg' 并没有用到，防止编译器提示警告
	
	//创建任务2.
//	OSTaskCreate(Task_LED1, (void *)0, &task_led1_stk[TASK_LED1_STK_SIZE - 1], TASK_LED1_PRIO);
	OSTaskCreateExt((void (*)(void *))Task_LED1,
					(void *)0,
					(OS_STK *)&task_led1_stk[TASK_LED1_STK_SIZE - 1],
					(INT8U)TASK_LED1_PRIO,
					(INT16U)TASK_LED1_PRIO,
					(OS_STK *)&task_led1_stk[0],
					(INT32U) TASK_LED1_STK_SIZE,
					(void*)0,
					(INT16U)(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));	
	
	//创建任务3.
//	OSTaskCreate(Task_LED2, (void *)0, &task_led2_stk[TASK_LED2_STK_SIZE - 1], TASK_LED2_PRIO);	
	OSTaskCreateExt((void (*)(void *))Task_LED2,
					(void *)0,
					(OS_STK *)&task_led2_stk[TASK_LED2_STK_SIZE - 1],
					(INT8U)TASK_LED2_PRIO,
					(INT16U)TASK_LED2_PRIO,
					(OS_STK *)&task_led2_stk[0],
					(INT32U) TASK_LED2_STK_SIZE,
					(void*)0,
					(INT16U)(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));
	
		
	//创建矩阵按键任务.
//	OSTaskCreate(Task_Matrixkey, (void *)0, &task_matrikey_stk[TASK_MATRIXKEY_STK_SIZE - 1], TASK_MATRIXKEY_PRIO);	
	OSTaskCreateExt((void (*)(void *))Task_Matrixkey,
					(void *)0,
					(OS_STK *)&task_matrikey_stk[TASK_MATRIXKEY_STK_SIZE - 1],
					(INT8U)TASK_MATRIXKEY_PRIO,
					(INT16U)TASK_MATRIXKEY_PRIO,
					(OS_STK *)&task_matrikey_stk[0],
					(INT32U) TASK_MATRIXKEY_STK_SIZE,
					(void*)0,
					(INT16U)(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));						
					
					
	//创建lcd1602任务.
//	OSTaskCreate(Task_LCD1602, (void *)0, &task_lcd1602_stk[TASK_LCD1602_STK_SIZE - 1], TASK_LCD1602_PRIO);	
	OSTaskCreateExt((void (*)(void *))Task_LCD1602,
					(void *)0,
					(OS_STK *)&task_lcd1602_stk[TASK_LCD1602_STK_SIZE - 1],
					(INT8U)TASK_LCD1602_PRIO,
					(INT16U)TASK_LCD1602_PRIO,
					(OS_STK *)&task_lcd1602_stk[0],
					(INT32U) TASK_LCD1602_STK_SIZE,
					(void*)0,
					(INT16U)(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));				

					
	//创建ADC1任务.
//	OSTaskCreate(Task_ADC1, (void *)0, &task_ADC1_stk[TASK_ADC1_STK_SIZE - 1], TASK_ADC1_PRIO);	
	OSTaskCreateExt((void (*)(void *))Task_ADC1,
					(void *)0,
					(OS_STK *)&task_ADC1_stk[TASK_ADC1_STK_SIZE - 1],
					(INT8U)TASK_ADC1_PRIO,
					(INT16U)TASK_ADC1_PRIO,
					(OS_STK *)&task_ADC1_stk[0],
					(INT32U) TASK_ADC1_STK_SIZE,
					(void*)0,
					(INT16U)(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));					
	
	
	//删除Task_Start任务。删除任务后无法查看该任务的堆栈情况。
//	OSTaskDel(TASK_STARTUP_PRIO);
					
	while(1)
	{
		OSTimeDlyHMSM(0, 0, 0, 500);
	}
}


/*
 * @function: Task_LED1
 * @details : 任务2。
 * @input   : NULL
 * @output  : NULL
 * @return  : NULL
 */
void Task_LED1(void *p_arg)
{
	(void)p_arg;                	
	
	while(1)
	{
		macLED1_ON();
		OSTimeDlyHMSM(0, 0, 0, 500);
		macLED1_OFF();
		OSTimeDlyHMSM(0, 0, 0, 500);
	}
}


/*
 * @function: Task_LED2
 * @details : 任务3。
 * @input   : NULL
 * @output  : NULL
 * @return  : NULL
 */
void Task_LED2(void *p_arg)
{
    (void)p_arg;      
	
	while(1)
	{
		macLED2_ON();;
		OSTimeDlyHMSM(0, 0, 0, 500);
		macLED2_OFF();
		OSTimeDlyHMSM(0, 0, 0, 500);  
	}
}


/*
 * @function: Task_Matrixkey
 * @details : 任务3。
 * @input   : NULL
 * @output  : NULL
 * @return  : NULL
 */
void Task_Matrixkey(void *p_arg)
{
	uint8_t key_val;
	
    (void)p_arg;      
	
	while(1)
	{
		key_val = GetKeyValue();
		if( 0 != key_val )
		{
			LCD_Write_Char(12, 0, key_val); 
		}
		
		OSTimeDlyHMSM(0, 0, 0, 100);
	}
}


/*
 * @function: Task_LCD1602
 * @details : lcd1602任务。
 * @input   : NULL
 * @output  : NULL
 * @return  : NULL
 */
void Task_LCD1602(void *p_arg)
{
	OS_STK_DATA  stk_data;
	INT8U        err;
	uint8_t      dis_stack_free[8];	
	uint8_t      dis_stack_used[8];	
	
	
	(void)p_arg;
	
	LCD_Write_String(0, 0, "free:");
	LCD_Write_String(0, 1, "used:");
	
	while(1)
	{
		//删除Task_Start任务。删除Task_Start任务后无法查看该任务的堆栈情况。
//		err = OSTaskStkChk(TASK_STARTUP_PRIO, &stk_data);
		err = OSTaskStkChk(TASK_ADC1_PRIO, &stk_data);
		
		if(err == OS_ERR_NONE)
		{
			sprintf((char *)dis_stack_free, "%d", stk_data.OSFree);	
			sprintf((char *)dis_stack_used, "%d", stk_data.OSUsed);	
			
			LCD_Write_String(5, 0, (uint8_t *)"     ");
			LCD_Write_String(5, 1, (uint8_t *)"     ");
			LCD_Write_String(12, 0, (uint8_t *)"     ");
			
			LCD_Write_String(5, 0, &dis_stack_free[0]);
			LCD_Write_String(5, 1, &dis_stack_used[0]);
			
			LCD_Write_String(12, 0, &ADC1Dat.DispBuf[0]);
		}
		
		OSTimeDlyHMSM(0, 0, 0, 1000);
	}
}



/*
 * @function: Task_ADC1
 * @details : ADC1任务。
 * @input   : NULL
 * @output  : NULL
 * @return  : NULL
 */
void Task_ADC1(void *p_arg)
{
	uint32_t conver_val_temp;     
	
	
	(void)p_arg;
	
	
	while(1)
	{
		conver_val_temp = (Get_ADC1(ADC_Channel_0) * 3);
		sprintf(&ADC1Dat.DispBuf[0], "%d", conver_val_temp);
		
		
		OSTimeDlyHMSM(0, 0, 0, 1000);
	}
}
