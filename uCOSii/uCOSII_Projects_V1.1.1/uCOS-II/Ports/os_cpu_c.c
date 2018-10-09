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
* File      : OS_CPU_C.C
* Version   : V2.86
* By        : Jean J. Labrosse
*             Brian Nagel
*
* For       : ARMv7M Cortex-M3
* Mode      : Thumb2
* Toolchain : IAR EWARM
*********************************************************************************************************
*/

#define  OS_CPU_GLOBALS
#include <ucos_ii.h>

/*
*********************************************************************************************************
*                                          LOCAL VARIABLES
*********************************************************************************************************
*/

#if OS_TMR_EN > 0
static  INT16U  OSTmrCtr;
#endif

/*
*********************************************************************************************************
*                                          SYS TICK DEFINES
*********************************************************************************************************
*/
#if 0
#define  OS_CPU_CM3_NVIC_ST_CTRL    (*((volatile INT32U *)0xE000E010))   /* SysTick Ctrl & Status Reg. */
#define  OS_CPU_CM3_NVIC_ST_RELOAD  (*((volatile INT32U *)0xE000E014))   /* SysTick Reload  Value Reg. */
#define  OS_CPU_CM3_NVIC_ST_CURRENT (*((volatile INT32U *)0xE000E018))   /* SysTick Current Value Reg. */
#define  OS_CPU_CM3_NVIC_ST_CAL     (*((volatile INT32U *)0xE000E01C))   /* SysTick Cal     Value Reg. */
#define  OS_CPU_CM3_NVIC_PRIO_ST    (*((volatile INT8U  *)0xE000ED23))   /* SysTick Handler Prio  Reg. */

#define  OS_CPU_CM3_NVIC_ST_CTRL_COUNT                    0x00010000     /* Count flag.                */
#define  OS_CPU_CM3_NVIC_ST_CTRL_CLK_SRC                  0x00000004     /* Clock Source.              */
#define  OS_CPU_CM3_NVIC_ST_CTRL_INTEN                    0x00000002     /* Interrupt enable.          */
#define  OS_CPU_CM3_NVIC_ST_CTRL_ENABLE                   0x00000001     /* Counter mode.              */
#define  OS_CPU_CM3_NVIC_PRIO_MIN                               0xFF     /* Min handler prio.          */
#endif
/*
*********************************************************************************************************
*                                       OS INITIALIZATION HOOK
*                                            (BEGINNING)
*
* Description: This function is called by OSInit() at the beginning of OSInit().
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts should be disabled during this call.
*********************************************************************************************************
*/
#if OS_CPU_HOOKS_EN > 0 && OS_VERSION > 203
void  OSInitHookBegin (void)
{
#if OS_TMR_EN > 0                                /* 当使用 OS_TMR.C 定时器管理模块                     */
    OSTmrCtr = 0;                                /* 初始化系统节拍计数变量 OSTmrCtr 为0                */
#endif                                           /* 每个时钟节拍OSTmrCtr（全局变量，初始值为 0）增1    */
}
#endif

 #if OS_CPU_HOOKS_EN > 0u && OS_VERSION > 290u
void OSTaskReturnHook(OS_TCB *ptcb)
{
	(void)ptcb;	
}
#endif


/*
*********************************************************************************************************
*                                       OS INITIALIZATION HOOK
*                                               (END)
*
* Description: This function is called by OSInit() at the end of OSInit().
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts should be disabled during this call.
*********************************************************************************************************
*/
#if OS_CPU_HOOKS_EN > 0 && OS_VERSION > 203
void  OSInitHookEnd (void)
{
}
#endif

/*
*********************************************************************************************************
*                                          TASK CREATION HOOK
*
* Description: This function is called when a task is created.
*
* Arguments  : ptcb   is a pointer to the task control block of the task being created.
*
* Note(s)    : 1) Interrupts are disabled during this call.
*********************************************************************************************************
*/
#if OS_CPU_HOOKS_EN > 0
void  OSTaskCreateHook (OS_TCB *ptcb)
{
#if OS_APP_HOOKS_EN > 0                          /* 如果有定义应用任务                                 */
    App_TaskCreateHook(ptcb);                    /* 调用应用任务创建钩子函数                           */
#else
    (void)ptcb;                                  /* Prevent compiler warning                           */
                                                 /* 告诉编译器 ptcb 没用到                             */
#endif
}
#endif


/*
*********************************************************************************************************
*                                           TASK DELETION HOOK
*
* Description: This function is called when a task is deleted.
*
* Arguments  : ptcb   is a pointer to the task control block of the task being deleted.
*
* Note(s)    : 1) Interrupts are disabled during this call.
*********************************************************************************************************
*/
#if OS_CPU_HOOKS_EN > 0
void  OSTaskDelHook (OS_TCB *ptcb)
{
#if OS_APP_HOOKS_EN > 0
    App_TaskDelHook(ptcb);
#else
    (void)ptcb;                                  /* Prevent compiler warning                           */
#endif
}
#endif

/*
*********************************************************************************************************
*                                             IDLE TASK HOOK
*
* Description: This function is called by the idle task.  This hook has been added to allow you to do
*              such things as STOP the CPU to conserve power.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts are enabled during this call.
*********************************************************************************************************
*/
#if OS_CPU_HOOKS_EN > 0 && OS_VERSION >= 251
void  OSTaskIdleHook (void)
{
#if OS_APP_HOOKS_EN > 0
    App_TaskIdleHook();
#endif
}
#endif

/*
*********************************************************************************************************
*                                           STATISTIC TASK HOOK
*
* Description: This function is called every second by uC/OS-II's statistics task.  This allows your
*              application to add functionality to the statistics task.
*
* Arguments  : none
*********************************************************************************************************
*/

#if OS_CPU_HOOKS_EN > 0
void  OSTaskStatHook (void)
{
#if OS_APP_HOOKS_EN > 0
    App_TaskStatHook();
#endif
}
#endif

/*
*********************************************************************************************************
*                                        INITIALIZE A TASK'S STACK
*
* Description: This function is called by either OSTaskCreate() or OSTaskCreateExt() to initialize the
*              stack frame of the task being created.  This function is highly processor specific.
*
* Arguments  : task          is a pointer to the task code
*
*              p_arg         is a pointer to a user supplied data area that will be passed to the task
*                            when the task first executes.
*
*              ptos          is a pointer to the top of stack.  It is assumed that 'ptos' points to
*                            a 'free' entry on the task stack.  If OS_STK_GROWTH is set to 1 then
*                            'ptos' will contain the HIGHEST valid address of the stack.  Similarly, if
*                            OS_STK_GROWTH is set to 0, the 'ptos' will contains the LOWEST valid address
*                            of the stack.
*
*              opt           specifies options that can be used to alter the behavior of OSTaskStkInit().
*                            (see uCOS_II.H for OS_TASK_OPT_xxx).
*
* Returns    : Always returns the location of the new top-of-stack once the processor registers have
*              been placed on the stack in the proper order.
*
* Note(s)    : 1) Interrupts are enabled when your task starts executing.
*              2) All tasks run in Thread mode, using process stack.
*********************************************************************************************************
*/

OS_STK *OSTaskStkInit (void (*task)(void *p_arg), void *p_arg, OS_STK *ptos, INT16U opt)
{
    OS_STK *stk;


    (void)opt;                                   /* 'opt' is not used, prevent warning                 */
    stk       = ptos;                            /* Load stack pointer                                 */

                                                 /* Registers stacked as if auto-saved on exception    *//* 中断后 xPSR，PC，LR，R12，R3-R0 被自动保存到栈中*/
    *(stk)    = (INT32U)0x01000000L;             /* xPSR                                               */
    *(--stk)  = (INT32U)task;                    /* Entry Point                                        *//* 任务入口 (PC) */
    *(--stk)  = (INT32U)0xFFFFFFFEL;             /* R14 (LR) (init value will cause fault if ever used)*/
    *(--stk)  = (INT32U)0x12121212L;             /* R12                                                */
    *(--stk)  = (INT32U)0x03030303L;             /* R3                                                 */
    *(--stk)  = (INT32U)0x02020202L;             /* R2                                                 */
    *(--stk)  = (INT32U)0x01010101L;             /* R1                                                 */
    *(--stk)  = (INT32U)p_arg;                   /* R0 : argument                                      *//*  R0 : 变量 */

                                                 /* Remaining registers saved on process stack         *//* 剩下的寄存器需要手动保存在堆栈 */
    *(--stk)  = (INT32U)0x11111111L;             /* R11                                                */
    *(--stk)  = (INT32U)0x10101010L;             /* R10                                                */
    *(--stk)  = (INT32U)0x09090909L;             /* R9                                                 */
    *(--stk)  = (INT32U)0x08080808L;             /* R8                                                 */
    *(--stk)  = (INT32U)0x07070707L;             /* R7                                                 */
    *(--stk)  = (INT32U)0x06060606L;             /* R6                                                 */
    *(--stk)  = (INT32U)0x05050505L;             /* R5                                                 */
    *(--stk)  = (INT32U)0x04040404L;             /* R4                                                 */

    return (stk);
}

/*
*********************************************************************************************************
*                                           TASK SWITCH HOOK
*
* Description: This function is called when a task switch is performed.  This allows you to perform other
*              operations during a context switch.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts are disabled during this call.
*              2) It is assumed that the global pointer 'OSTCBHighRdy' points to the TCB of the task that
*                 will be 'switched in' (i.e. the highest priority task) and, 'OSTCBCur' points to the
*                 task being switched out (i.e. the preempted task).
*********************************************************************************************************
*/
#if (OS_CPU_HOOKS_EN > 0) && (OS_TASK_SW_HOOK_EN > 0)
void  OSTaskSwHook (void)
{
#if OS_APP_HOOKS_EN > 0
    App_TaskSwHook();
#endif
}
#endif

/*
*********************************************************************************************************
*                                           OS_TCBInit() HOOK
*
* Description: This function is called by OS_TCBInit() after setting up most of the TCB.
*
* Arguments  : ptcb    is a pointer to the TCB of the task being created.
*
* Note(s)    : 1) Interrupts may or may not be ENABLED during this call.
*********************************************************************************************************
*/
#if OS_CPU_HOOKS_EN > 0 && OS_VERSION > 203
void  OSTCBInitHook (OS_TCB *ptcb)
{
#if OS_APP_HOOKS_EN > 0
    App_TCBInitHook(ptcb);
#else
    (void)ptcb;                                  /* Prevent compiler warning                           */
#endif
}
#endif

/*
*********************************************************************************************************
*                                               TICK HOOK
*
* Description: This function is called every tick.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts may or may not be ENABLED during this call.
*********************************************************************************************************
*/
#if (OS_CPU_HOOKS_EN > 0) && (OS_TIME_TICK_HOOK_EN > 0)
void  OSTimeTickHook (void)
{
#if OS_APP_HOOKS_EN > 0
    App_TimeTickHook();                          /* 应用软件的时钟节拍钩子                             */
#endif

#if OS_TMR_EN > 0                                /* 如果有启动定时器管理                               */
    OSTmrCtr++;                                  /* 计时变量 OSTmrCtr 加 1                             */

    /* 如果时间到了 */
	if(OSTmrCtr >= (OS_TICKS_PER_SEC / OS_TMR_CFG_TICKS_PER_SEC)) 
	{
        OSTmrCtr = 0;                            /* 计时清 0                                           */
        OSTmrSignal();                           /* 发送信号量 OSTmrSemSignal(初始值为 0), 以便软件定  */
                                                 /* 时器扫描任务 OSTmr_Task 能请求到信号量而继续运行.  */
	}
#endif
}
#endif

/*
*********************************************************************************************************
*                                         OS_CPU_SysTickHandler()
*
* Description: Handle the system tick (SysTick) interrupt, which is used to generate the uC/OS-II tick
*              interrupt.
*
* Arguments  : none.
*
* Note(s)    : 1) This function MUST be placed on entry 15 of the Cortex-M3 vector table.
*********************************************************************************************************
*/
#if 0
void  OS_CPU_SysTickHandler (void)
{
    OS_CPU_SR  cpu_sr;


    OS_ENTER_CRITICAL();                         /* Tell uC/OS-II that we are starting an ISR          */
    OSIntNesting++;
    OS_EXIT_CRITICAL();

    OSTimeTick();                                /* Call uC/OS-II's OSTimeTick()                       */

    OSIntExit();                                 /* Tell uC/OS-II that we are leaving the ISR          */
}
#endif
/*
*********************************************************************************************************
*                                          OS_CPU_SysTickInit()
*
* Description: Initialize the SysTick.
*
* Arguments  : none.
*
* Note(s)    : 1) This function MUST be called after OSStart() & after processor initialization.
*********************************************************************************************************
*/
#if 0
void  OS_CPU_SysTickInit (void)
{
    INT32U  cnts;

                                                 /* OS_CPU_SysTickClkFreq()获取时钟频率                */
												 /* OS_TICKS_PER_SEC 定义每秒时钟节拍中断的次数,       */    
												 /* 即时钟节拍时间为 1/OS_TICKS_PER_SEC                */
    cnts = OS_CPU_SysTickClkFreq() / OS_TICKS_PER_SEC;

    OS_CPU_CM3_NVIC_ST_RELOAD = (cnts - 1);      
                                                 /* Set prio of SysTick handler to min prio.           */
    OS_CPU_CM3_NVIC_PRIO_ST   = OS_CPU_CM3_NVIC_PRIO_MIN;
                                                 /* Enable SysTick timer.                              */
    OS_CPU_CM3_NVIC_ST_CTRL  |= OS_CPU_CM3_NVIC_ST_CTRL_CLK_SRC | OS_CPU_CM3_NVIC_ST_CTRL_ENABLE;
                                                 /* Enable SysTick timer interrupt.                    */
    OS_CPU_CM3_NVIC_ST_CTRL  |= OS_CPU_CM3_NVIC_ST_CTRL_INTEN;
}

#endif
