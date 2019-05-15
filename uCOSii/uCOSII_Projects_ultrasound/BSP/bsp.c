/*
*********************************************************************************************************
*                                     MICIRUM BOARD SUPPORT PACKAGE
*
*                             (c) Copyright 2013; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                        BOARD SUPPORT PACKAGE
*
*                                     ST Microelectronics STM32
*                                              on the
*
*                                     Micrium uC-Eval-STM32F107
*                                        Evaluation Board
*
* Filename      : bsp.c
* Version       : V1.00
* Programmer(s) : EHS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#define  BSP_MODULE
#include <bsp.h>


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             REGISTERS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            REGISTER BITS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/
/*
#if ((CPU_CFG_TS_TMR_EN          != DEF_ENABLED) && \
     (APP_CFG_PROBE_OS_PLUGIN_EN == DEF_ENABLED) && \
     (OS_PROBE_HOOKS_EN          >  0u))
#error  "CPU_CFG_TS_EN                  illegally #define'd in 'cpu.h'"
#error  "                              [MUST be  DEF_ENABLED] when    "
#error  "                               using uC/Probe COM modules    "
#endif

*/
/*
*********************************************************************************************************
*                                               BSP_Init()
*
* Description : Initialize the Board Support Package (BSP).
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) This function SHOULD be called before any other BSP function is called.
*
*               (2) CPU instruction / data tracing requires the use of the following pins :
*                   (a) (1) Aysynchronous     :  PB[3]
*                       (2) Synchronous 1-bit :  PE[3:2]
*                       (3) Synchronous 2-bit :  PE[4:2]
*                       (4) Synchronous 4-bit :  PE[6:2]
*
*                   (b) The uC-Eval board MAY utilize the following pins depending on the application :
*                       (1) PE[5], MII_INT
*                       (1) PE[6], SDCard_Detection
*
*                   (c) The application may wish to adjust the trace bus width depending on I/O
*                       requirements.
*********************************************************************************************************
*/


/*
 * @function: SysTick_init
 * @details : 配置SysTick定时器
 * @input   : NULL
 * @output  : NULL
 * @return  : NULL
 */
void SysTick_init(void)
{
    SysTick_Config(SystemCoreClock / OS_TICKS_PER_SEC);                         /* 初始化并使能SysTick定时器 */
}


/*
 * @function: BSP_Init
 * @details : 时钟初始化、硬件初始化
 * @input   : NULL
 * @output  : NULL
 * @return  : NULL
 */
void BSP_Init(void)
{
	SystemInit();                                                              /* 配置系统时钟为72M. */	
	SysTick_init();                                                            /* 初始化并使能SysTick定时器. */
	LED_Init();                                                                /* LED 初始化. */
	MatrixkeyInit();
	Lcd1602_Init();
	TIM8_PWM_Init();
	ADC1Init();
	
//	UserParaInit();
}


/*-------------------------------------------------------------------------------
* Function Name  : NVIC_Configuration
* Description    : Configures NVIC.
* Input          : None
* Output         : None
* Return         : None
NVIC_PriorityGroup    	NVIC_IRQChannel	  	NVIC_IRQChannel		描述
                      	的先占优先级 	   	的从优先级

NVIC_PriorityGroup_0    0                  	0-15 			 	先占优先级 0 位
															 	从优先级 4位
NVIC_PriorityGroup_1  	0-1  				0-7 				先占优先级 1 位
													 			从优先级 3位
NVIC_PriorityGroup_2  	0-3  				0-3 				先占优先级 2 位 
													 			从优先级 2位
NVIC_PriorityGroup_3  	0-7  				0-1 				先占优先级 3 位 
																从优先级 1位   
NVIC_PriorityGroup_4  	0-15  				0 					先占优先级 4 位
																从优先级 0位 
注意：数值越小，优先级越高  
-------------------------------------------------------------------------------*/
void NVIC_Configuration(void)
{
//	NVIC_InitTypeDef NVIC_InitStructure;

	/*Configure two bits for preemption priority*/
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);			   

	/* Enable the TIM1 Interrupt */
//	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);

	/* Enable the TIM8 Interrupt */
//	NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
	
	/* Enable the TIM2 gloabal Interrupt */
//	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
	
	/* Enable the TIM3 gloabal Interrupt */
//	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);

//	/* Enable the TIM4 gloabal Interrupt */
//	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
	
	/* Enable the TIM5 gloabal Interrupt */
//	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);

//	/* Enable the TIM6 gloabal Interrupt */
//    NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;	  
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;	
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
////	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x100);/*配置中断向量偏移表，参数1指定中断向量表在ARM还是在代码存储器中，默认是Flash，所以不设置也不要紧，使用RAM调试的时候必须设置*/
//												 /*参数2是向量表的基址偏移域，在固件库文档中说到：对于Flash，这个值一定要比0x08000100高，对于RAM这个值要比0x100高，而且这个值一定要是256(4*64)的整数倍*/		

//	/* Enable the TIM7 gloabal Interrupt */
//    NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;	  
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;	
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
////	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x100);/*配置中断向量偏移表，参数1指定中断向量表在ARM还是在代码存储器中，默认是Flash，所以不设置也不要紧，使用RAM调试的时候必须设置*/

	/* Enable the DMAChannel1_IRQChannel  Interrupt */
//	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
}
