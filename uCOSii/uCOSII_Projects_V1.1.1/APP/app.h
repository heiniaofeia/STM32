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
 * @details: 1.��ʼ�������ȼ��������ջ��С��ucos�涨������ջ�ĵ�λΪOS_STK,��
             �ݲ�ͬƽ̨�в�ͬ��λ���壬M3�ں˶���Ϊ32λ��Ҳ����4�ֽڿ�ȡ���
			 �ˣ�ʵ��ջ�ռ��СΪy = x * 4 byte. 
			 2.���ڶ���ջ�ռ�ԭ��������ʹ����ռ�����ջ�ռ�50%-80%Ϊ�ţ�̫С
			 ����ɿռ��˷ѣ�̫������ջ�����
 */
#define  TASK_STARTUP_PRIO                       32                             /* ����STARTUP�������ȼ�: ��ʼ��������ȼ�����Ϊ���. */
#define  STARTUP_TASK_STK_SIZE                   64                             /* ���������ջ��С.                                   */

/*
 * @details: led�������ȼ��������ջ��С��
 */
#define  TASK_LED1_PRIO                          31                             /* ����LED1�������ȼ�.                                 */
#define  TASK_LED1_STK_SIZE                      36                             /* ���������ջ��С.                                   */

#define  TASK_LED2_PRIO                          30                             /* ����LED2�������ȼ�.                                 */
#define  TASK_LED2_STK_SIZE                      36                             /* ���������ջ��С.                                   */

/*
 * @details: Matrixkey�������ȼ��������ջ��С��
 */
#define  TASK_MATRIXKEY_PRIO                     29                             /* ���þ��󰴼��������ȼ�.                             */
#define  TASK_MATRIXKEY_STK_SIZE                 64                             /* ���������ջ��С.                                   */

/*
 * @details: lcd1602�������ȼ��������ջ��С��
 */
#define  TASK_LCD1602_PRIO                       28                             /* ����LED1�������ȼ�.                                 */
#define  TASK_LCD1602_STK_SIZE                   64                             /* ���������ջ��С.                                   */

/*
 * @details: ADC1�������ȼ��������ջ��С��
 */
#define  TASK_ADC1_PRIO                          27                             /* ����ADC1�������ȼ�.                                 */
#define  TASK_ADC1_STK_SIZE                      64                             /* ���������ջ��С.                                   */


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
 * @details: �û�����������
 */
void Task_Start(void *p_arg);
void Task_LED1(void *p_arg);
void Task_LED2(void *p_arg);
void Task_Matrixkey(void *p_arg);
void Task_LCD1602(void *p_arg);
void Task_ADC1(void *p_arg);


#endif

