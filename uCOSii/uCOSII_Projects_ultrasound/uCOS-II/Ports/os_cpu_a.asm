;********************************************************************************************************
;                                               uC/OS-II
;                                         The Real-Time Kernel
;
;                               (c) Copyright 1992-2006, Micrium, Weston, FL
;                                          All Rights Reserved
;
;                                           ARM Cortex-M3 Port
;
; File      : OS_CPU_A.ASM
; Version   : V2.86
; By        : Jean J. Labrosse
;             Brian Nagel
;
; For       : ARMv7M Cortex-M3
; Mode      : Thumb2
; Toolchain : IAR EWARM
;********************************************************************************************************

;********************************************************************************************************
;                                           PUBLIC FUNCTIONS
;********************************************************************************************************

    EXTERN  OSRunning                                           ; External references
    EXTERN  OSPrioCur
    EXTERN  OSPrioHighRdy
    EXTERN  OSTCBCur
    EXTERN  OSTCBHighRdy
    EXTERN  OSIntNesting
    EXTERN  OSIntExit
    EXTERN  OSTaskSwHook


    EXPORT  OS_CPU_SR_Save                                      ; Functions declared in this file
    EXPORT  OS_CPU_SR_Restore
    EXPORT  OSStartHighRdy
    EXPORT  OSCtxSw
    EXPORT  OSIntCtxSw
    EXPORT  OS_CPU_PendSVHandler

;********************************************************************************************************
;                                                EQUATES
;********************************************************************************************************

NVIC_INT_CTRL   EQU     0xE000ED04                              ; Interrupt control state register.中断控制及状态寄存器 ICSR 的地址。
NVIC_SYSPRI14   EQU     0xE000ED22                              ; System priority register (priority 14).系统异常优先级寄存器 PRI_14。
NVIC_PENDSV_PRI EQU           0xFF                              ; PendSV priority value (lowest).定义 PendSV 的可编程优先级为 255，即最低。原因在<<ARM Cortex-M3 权威指南>>的 7.6 节已有说明。
NVIC_PENDSVSET  EQU     0x10000000                              ; Value to trigger PendSV exception.中断控制及状态寄存器 ICSR 的位 28，写 1 可以悬起 PendSV 中断。读取它则返回 PendSV 的状态。

;********************************************************************************************************
;                                      CODE GENERATION DIRECTIVES
;********************************************************************************************************

;        RSEG CODE:CODE:NOROOT(2)               ;RSEG CODE：选择段 code。第二个 CODE 表示代码段的意思，只读。
                                                ;NOROOT 表示：如果这段中的代码没调用，则允许连接器丢弃这段。
                                                ;(2)表示：4 字节对齐。假如是(n)，则表示 2^n 对齐
                                               
	AREA |.text|, CODE, READONLY, ALIGN=2 	;AREA |.text| 选择段 |.text|。
                                      		;CODE表示代码段，READONLY表示只读（缺省）
                                      		;ALIGN=2表示4字节对齐。若ALIGN=n，这2^n对齐
	THUMB                                 	;Thumb 代码
	REQUIRE8                              	;指定当前文件要求堆栈八字节对齐
	PRESERVE8                             	;令指定当前文件保持堆栈八字节对齐


;********************************************************************************************************
;                                   CRITICAL SECTION METHOD 3 FUNCTIONS
;
; Description: Disable/Enable interrupts by preserving the state of interrupts.  Generally speaking you
;              would store the state of the interrupt disable flag in the local variable 'cpu_sr' and then
;              disable interrupts.  'cpu_sr' is allocated in all of uC/OS-II's functions that need to
;              disable interrupts.  You would restore the interrupt disable state by copying back 'cpu_sr'
;              into the CPU's status register.
;
; Prototypes :     OS_CPU_SR  OS_CPU_SR_Save(void);
;                  void       OS_CPU_SR_Restore(OS_CPU_SR cpu_sr);
;
;
; Note(s)    : 1) These functions are used in general like this:
;
;                 void Task (void *p_arg)
;                 {
;                 #if OS_CRITICAL_METHOD == 3          /* Allocate storage for CPU status register */
;                     OS_CPU_SR  cpu_sr;
;                 #endif
;
;                          :
;                          :
;                     OS_ENTER_CRITICAL();             /* cpu_sr = OS_CPU_SaveSR();                */
;                          :
;                          :
;                     OS_EXIT_CRITICAL();              /* OS_CPU_RestoreSR(cpu_sr);                */
;                          :
;                          :
;                 }
;********************************************************************************************************

OS_CPU_SR_Save                                                  ; OS_ENTER_CRITICAL() 里进入临界段调用，保存现场环境。
    MRS     R0, PRIMASK                                         ; Set prio int mask to mask all (except faults). 读取 PRIMASK 到 R0(保存全局中断标记，除了故障中断)。
    CPSID   I                                                   ; PRIMASK=1，关中断。
    BX      LR                                                  ; 返回，返回值保存在 R0。

OS_CPU_SR_Restore                                               ; OS_EXIT_CRITICAL() 里退出临界段调用，恢复现场环境。
    MSR     PRIMASK, R0                                         ; 读取 R0 到 PRIMASK 中(恢复全局中断标记)，通过 R0 传递参数。
    BX      LR

;********************************************************************************************************
;                                          START MULTITASKING
;                                       void OSStartHighRdy(void)
;
; Note(s) : 1) This function triggers a PendSV exception (essentially, causes a context switch) to cause
;              the first task to start.
;
;           2) OSStartHighRdy() MUST:
;              a) Setup PendSV exception priority to lowest;
;              b) Set initial PSP to 0, to tell context switcher this is first run;
;              c) Set OSRunning to TRUE;
;              d) Trigger PendSV exception;
;              e) Enable interrupts (tasks will run with interrupts enabled).
;********************************************************************************************************

OSStartHighRdy
    LDR     R0, =NVIC_SYSPRI14                                  ; Set the PendSV exception priority. 装载系统异常优先级寄存器 PRI_14数据到寄存器R0，即设置 PendSV 中断优先级的寄存器
    LDR     R1, =NVIC_PENDSV_PRI                                ; 装载 PendSV 的可编程优先级(255)
    STRB    R1, [R0]                                            ; 无符号字节寄存器存储。R1 是要存储的寄存器

    MOVS    R0, #0                                              ; Set the PSP to 0 for initial context switch call
    MSR     PSP, R0                                             ; 将 R0 的内容加载到程序状态寄存器 PSR 的指定字段中。

    LDR     R0, =OSRunning                                      ; OSRunning = TRUE
    MOVS    R1, #1
    STRB    R1, [R0]

    LDR     R0, =NVIC_INT_CTRL                                  ; Trigger the PendSV exception (causes context switch)。装载中断控制及状态寄存器 ICSR 的地址。
    LDR     R1, =NVIC_PENDSVSET                                 ; 中断控制及状态寄存器 ICSR 的位 28。
    STR     R1, [R0]                                            ; 设置中断控制及状态寄存器 ICSR 位 28 为 1，以悬起(允许)PendSV 中断.

    CPSIE   I                                                   ; Enable interrupts at processor level. 开中断(前面已经讲解过)

OSStartHang
    B       OSStartHang                                         ; Should never get here


;********************************************************************************************************
;                               PERFORM A CONTEXT SWITCH (From task level)
;                                           void OSCtxSw(void)
;
; Note(s) : 1) OSCtxSw() is called when OS wants to perform a task context switch.  This function
;              triggers the PendSV exception which is where the real work is done.
;********************************************************************************************************

OSCtxSw                                                         ; 悬起(允许)PendSV 中断
    LDR     R0, =NVIC_INT_CTRL                                  ; Trigger the PendSV exception (causes context switch). 装载 中断控制及状态寄存器 ICSR 的地址。
    LDR     R1, =NVIC_PENDSVSET                                 ; 中断控制及状态寄存器 ICSR 的位 28
    STR     R1, [R0]                                            ; 设置中断控制及状态寄存器 ICSR 位 28 为 1，以悬起(允许)PendSV 中断。
    BX      LR                                                  ; 返回。

;********************************************************************************************************
;                             PERFORM A CONTEXT SWITCH (From interrupt level)
;                                         void OSIntCtxSw(void)
;
; Notes:    1) OSIntCtxSw() is called by OSIntExit() when it determines a context switch is needed as
;              the result of an interrupt.  This function simply triggers a PendSV exception which will
;              be handled when there are no more interrupts active and interrupts are enabled.
;********************************************************************************************************

OSIntCtxSw
    LDR     R0, =NVIC_INT_CTRL                                  ; Trigger the PendSV exception (causes context switch)
    LDR     R1, =NVIC_PENDSVSET
    STR     R1, [R0]
    BX      LR

;********************************************************************************************************
;                                         HANDLE PendSV EXCEPTION
;                                     void OS_CPU_PendSVHandler(void)
;
; Note(s) : 1) PendSV is used to cause a context switch.  This is a recommended method for performing
;              context switches with Cortex-M3.  This is because the Cortex-M3 auto-saves half of the
;              processor context on any exception, and restores same on return from exception.  So only
;              saving of R4-R11 is required and fixing up the stack pointers.  Using the PendSV exception
;              this way means that context saving and restoring is identical whether it is initiated from
;              a thread or occurs due to an interrupt or exception.
;
;           2) Pseudo-code is:
;              a) Get the process SP, if 0 then skip (goto d) the saving part (first context switch);
;              b) Save remaining regs r4-r11 on process stack;
;              c) Save the process SP in its TCB, OSTCBCur->OSTCBStkPtr = SP;
;              d) Call OSTaskSwHook();
;              e) Get current high priority, OSPrioCur = OSPrioHighRdy;
;              f) Get current ready thread TCB, OSTCBCur = OSTCBHighRdy;
;              g) Get new process SP from TCB, SP = OSTCBHighRdy->OSTCBStkPtr;
;              h) Restore R4-R11 from new process stack;
;              i) Perform exception return which will restore remaining context.
;
;           3) On entry into PendSV handler:
;              a) The following have been saved on the process stack (by processor):
;                 xPSR, PC, LR, R12, R0-R3
;              b) Processor mode is switched to Handler mode (from Thread mode)
;              c) Stack is Main stack (switched from Process stack)
;              d) OSTCBCur      points to the OS_TCB of the task to suspend
;                 OSTCBHighRdy  points to the OS_TCB of the task to resume
;
;           4) Since PendSV is set to lowest priority in the system (by OSStartHighRdy() above), we
;              know that it will only be run when no other exception or interrupt is active, and
;              therefore safe to assume that context being switched out was using the process stack (PSP).
;********************************************************************************************************
  
OS_CPU_PendSVHandler                                            ; 当调用 OS_CPU_PendSVHandler() 时，CPU 就会自动保存 xPSR、PC、LR、R12、R0-R3 寄存器到堆栈。                  
    CPSID   I                                                   ; Prevent interruption during context switch. 关中断。
    MRS     R0, PSP                                             ; PSP is process stack pointer.
    CBZ     R0, OS_CPU_PendSVHandler_nosave                     ; Skip register save the first time. 当 PSP==0，执行 OSPendSV_nosave 函数

    SUBS    R0, R0, #0x20                                       ; Save remaining regs r4-11 on process stack. 装载 r4-11 到栈 ，共 8 个寄存器，32 位，4 个字节，即 8*4=32=0x20。
    STM     R0, {R4-R11}

    LDR     R1, =OSTCBCur                                       ; OSTCBCur->OSTCBStkPtr = SP; 即R1=&OSTCBCur。
    LDR     R1, [R1]                                            ; R1=*R1 (R1=OSTCBCur)
    STR     R0, [R1]                                            ; R0 is SP of process being switched out. *R1=R0 (*OSTCBCur=SP)。

                                                                ; At this point, entire context of process has been saved
OS_CPU_PendSVHandler_nosave
    PUSH    {R14}                                               ; Save LR exc_return value
    LDR     R0, =OSTaskSwHook                                   ; OSTaskSwHook();
    BLX     R0
    POP     {R14}

    LDR     R0, =OSPrioCur                                      ; OSPrioCur = OSPrioHighRdy; 设置当前优先级为最高优先级就绪任务的优先级。
    LDR     R1, =OSPrioHighRdy
    LDRB    R2, [R1]
    STRB    R2, [R0]

    LDR     R0, =OSTCBCur                                       ; OSTCBCur  = OSTCBHighRdy;
    LDR     R1, =OSTCBHighRdy
    LDR     R2, [R1]
    STR     R2, [R0]

    LDR     R0, [R2]                                            ; R0 is new process SP; SP = OSTCBHighRdy->OSTCBStkPtr;
    LDM     R0, {R4-R11}                                        ; Restore r4-11 from new process stack
    ADDS    R0, R0, #0x20
    MSR     PSP, R0                                             ; Load PSP with new process SP
    ORR     LR, LR, #0x04                                       ; Ensure exception return uses process stack
    CPSIE   I
    BX      LR                                                  ; Exception return will restore remaining context

    END
