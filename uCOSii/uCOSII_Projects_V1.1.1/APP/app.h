/*
 * @file   : app.h
 * @author : DragonFly
 * @version: V1.0.0
 * @date   : 2016.12.21
 * @history:
 * @details: app head file
 */
#ifndef	__APP_H__
#define	__APP_H__


#include "includes.h"



/*---------------------------------------------------------------------------
                                Macro definition
----------------------------------------------------------------------------*/
/*
 * @details: 1.起始任务优先级和任务堆栈大小。ucos规定，任务栈的单位为OS_STK,根
             据不同平台有不同的位宽定义，M3内核定义为32位，也就是4字节宽度。因
			 此，实际栈空间大小为y = x * 4 byte. 
			 2.关于定义栈空间原则，以任务使用率占用最大栈空间50%-80%为优，太小
			 会造成空间浪费，太大会造成栈溢出。
 */
#define  TASK_STARTUP_PRIO                       32                             /* 设置STARTUP任务优先级: 开始任务的优先级设置为最低. */
#define  STARTUP_TASK_STK_SIZE                   64                             /* 设置任务堆栈大小.                                   */

/*
 * @details: led任务优先级和任务堆栈大小。
 */
#define  TASK_LED1_PRIO                          31                             /* 设置LED1任务优先级.                                 */
#define  TASK_LED1_STK_SIZE                      36                             /* 设置任务堆栈大小.                                   */

#define  TASK_LED2_PRIO                          30                             /* 设置LED2任务优先级.                                 */
#define  TASK_LED2_STK_SIZE                      36                             /* 设置任务堆栈大小.                                   */

/*
 * @details: Matrixkey任务优先级和任务堆栈大小。
 */
#define  TASK_MATRIXKEY_PRIO                     29                             /* 设置矩阵按键任务优先级.                             */
#define  TASK_MATRIXKEY_STK_SIZE                 64                             /* 设置任务堆栈大小.                                   */

/*
 * @details: lcd1602任务优先级和任务堆栈大小。
 */
#define  TASK_LCD1602_PRIO                       28                             /* 设置LED1任务优先级.                                 */
#define  TASK_LCD1602_STK_SIZE                   64                             /* 设置任务堆栈大小.                                   */

/*
 * @details: ADC1任务优先级和任务堆栈大小。
 */
#define  TASK_ADC1_PRIO                          27                             /* 设置ADC1任务优先级.                                 */
#define  TASK_ADC1_STK_SIZE                      64                             /* 设置任务堆栈大小.                                   */


/*---------------------------------------------------------------------------
                                Variable type
----------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
                                Variable declaration
----------------------------------------------------------------------------*/
extern  OS_STK  startup_task_stk[STARTUP_TASK_STK_SIZE];	
extern  OS_STK  task_led1_stk[TASK_LED1_STK_SIZE];
extern  OS_STK  task_led2_stk[TASK_LED2_STK_SIZE];
extern  OS_STK  task_matrikey_stk[TASK_MATRIXKEY_STK_SIZE];
extern  OS_STK  task_lcd1602_stk[TASK_LCD1602_STK_SIZE];
extern  OS_STK  task_ADC1_stk[TASK_ADC1_STK_SIZE];


/*---------------------------------------------------------------------------
                                Function declaration
----------------------------------------------------------------------------*/
/*
 * @details: 用户任务声明。
 */
void Task_Start(void *p_arg);
void Task_LED1(void *p_arg);
void Task_LED2(void *p_arg);
void Task_Matrixkey(void *p_arg);
void Task_LCD1602(void *p_arg);
void Task_ADC1(void *p_arg);


#endif

