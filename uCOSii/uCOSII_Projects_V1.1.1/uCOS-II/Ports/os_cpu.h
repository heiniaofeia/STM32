/*
*********************************************************************************************************
*                                               uC/OS-II
*                                         The Real-Time Kernel
*
*
*                                (c) Copyright 2006, Micrium, Weston, FL
*                                          All Rights Reserved
*
*                                           ARM Cortex-M3 Port
*
* File      : OS_CPU.H
* Version   : V2.86
* By        : Jean J. Labrosse
*             Brian Nagel
*
* For       : ARMv7M Cortex-M3
* Mode      : Thumb2
* Toolchain : IAR EWARM
*********************************************************************************************************
*/

#ifndef  OS_CPU_H
#define  OS_CPU_H


#ifdef   OS_CPU_GLOBALS
#define  OS_CPU_EXT
#else                                            /* 如果没有定义 OS_CPU_GLOBALS                        */
#define  OS_CPU_EXT  extern                      /* 则用 OS_CPU_EXT 声明变量已经外部定义了。           */
#endif

/*
*********************************************************************************************************
*                                              DATA TYPES
*                                         (Compiler Specific)
*********************************************************************************************************
*/

typedef unsigned char  BOOLEAN;
typedef unsigned char  INT8U;                    /* Unsigned  8 bit quantity                           */
typedef signed   char  INT8S;                    /* Signed    8 bit quantity                           */
typedef unsigned short INT16U;                   /* Unsigned 16 bit quantity                           *//* 大多数 Cortex-M3 编译器，short 是 16 位,int 是 32 位 */
typedef signed   short INT16S;                   /* Signed   16 bit quantity                           */
typedef unsigned int   INT32U;                   /* Unsigned 32 bit quantity                           */
typedef signed   int   INT32S;                   /* Signed   32 bit quantity                           */
typedef float          FP32;                     /* Single precision floating point                    *//* 尽管包含了浮点数，但 uC/OS-II 中并没用到 */
typedef double         FP64;                     /* Double precision floating point                    */

typedef unsigned int   OS_STK;                   /* Each stack entry is 32-bit wide                    *//* M3 是 32 位，所以堆栈的数据类型 OS_STK 设置 32位 */
typedef unsigned int   OS_CPU_SR;                /* Define size of CPU status register (PSR = 32 bits) *//* M3 的状态寄存器（xPSR）是 32 位 */


/*
*********************************************************************************************************
*                                              Cortex-M1
*                                      Critical Section Management
*
* Method #1:  Disable/Enable interrupts using simple instructions.  After critical section, interrupts
*             will be enabled even if they were disabled before entering the critical section.
*             NOT IMPLEMENTED
*
* Method #2:  Disable/Enable interrupts by preserving the state of interrupts.  In other words, if
*             interrupts were disabled before entering the critical section, they will be disabled when
*             leaving the critical section.
*             NOT IMPLEMENTED
*
* Method #3:  Disable/Enable interrupts by preserving the state of interrupts.  Generally speaking you
*             would store the state of the interrupt disable flag in the local variable 'cpu_sr' and then
*             disable interrupts.  'cpu_sr' is allocated in all of uC/OS-II's functions that need to
*             disable interrupts.  You would restore the interrupt disable state by copying back 'cpu_sr'
*             into the CPU's status register.
*********************************************************************************************************
*/

#define  OS_CRITICAL_METHOD   3

#if OS_CRITICAL_METHOD == 3
#define  OS_ENTER_CRITICAL()  {cpu_sr = OS_CPU_SR_Save();}    /* 进入临界段 */
#define  OS_EXIT_CRITICAL()   {OS_CPU_SR_Restore(cpu_sr);}    /* 退出临界段 */
#endif

/*
*********************************************************************************************************
*                                        Cortex-M3 Miscellaneous
*********************************************************************************************************
*/

#define  OS_STK_GROWTH        1                   /* Stack grows from HIGH to LOW memory on ARM        */

#define  OS_TASK_SW()         OSCtxSw()           /* 定义任务切换宏                                    */

/*
*********************************************************************************************************
*                                              PROTOTYPES
*********************************************************************************************************
*/
                                                  /* OS_CRITICAL_METHOD = 1: 直接使用处理器的开关中断指令来实现宏                   */
                                                  /* OS_CRITICAL_METHOD = 2: 利用堆栈保存和恢复CPU的状态                            */
                                                  /* OS_CRITICAL_METHOD = 3: 利用编译器扩展功能获得程序状态字，保存在局部变量cpu_sr */
#if OS_CRITICAL_METHOD == 3                       /* See OS_CPU_A.ASM                                  */
OS_CPU_SR  OS_CPU_SR_Save(void);
void       OS_CPU_SR_Restore(OS_CPU_SR cpu_sr);
#endif

void       OSCtxSw(void);                         /* 用户任务切换                                      */
void       OSIntCtxSw(void);                      /* 中断任务切换函数                                  */
void       OSStartHighRdy(void);                  /* 在操作系统第一次启动的时候调用的任务切换          */

void       OS_CPU_PendSVHandler(void);            /* 用户中断处理函数，旧版本为 OSPendSV               */

                                                  /* 下面3个函数是为SysTick定时器服务的, 为了便于理解, */
												  /* 不采用官方的, 自己编写, 我们把它注释掉            */
//void       OS_CPU_SysTickHandler(void);           /* 系统定时中断处理函数，时钟节拍函数                */
//void       OS_CPU_SysTickInit(void);              /* 系统 SysTick 定时器初始化                         */                                                 
//INT32U     OS_CPU_SysTickClkFreq(void);           /* 返回 SysTick 定时器的时钟频率                     */
												  
#endif

