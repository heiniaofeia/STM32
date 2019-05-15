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
 * @details : ����SysTick��ʱ��
 * @input   : NULL
 * @output  : NULL
 * @return  : NULL
 */
void SysTick_init(void)
{
    SysTick_Config(SystemCoreClock / OS_TICKS_PER_SEC);                         /* ��ʼ����ʹ��SysTick��ʱ�� */
}


/*
 * @function: BSP_Init
 * @details : ʱ�ӳ�ʼ����Ӳ����ʼ��
 * @input   : NULL
 * @output  : NULL
 * @return  : NULL
 */
void BSP_Init(void)
{
	SystemInit();                                                              /* ����ϵͳʱ��Ϊ72M. */	
	SysTick_init();                                                            /* ��ʼ����ʹ��SysTick��ʱ��. */
	LED_Init();                                                                /* LED ��ʼ��. */
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
NVIC_PriorityGroup    	NVIC_IRQChannel	  	NVIC_IRQChannel		����
                      	����ռ���ȼ� 	   	�Ĵ����ȼ�

NVIC_PriorityGroup_0    0                  	0-15 			 	��ռ���ȼ� 0 λ
															 	�����ȼ� 4λ
NVIC_PriorityGroup_1  	0-1  				0-7 				��ռ���ȼ� 1 λ
													 			�����ȼ� 3λ
NVIC_PriorityGroup_2  	0-3  				0-3 				��ռ���ȼ� 2 λ 
													 			�����ȼ� 2λ
NVIC_PriorityGroup_3  	0-7  				0-1 				��ռ���ȼ� 3 λ 
																�����ȼ� 1λ   
NVIC_PriorityGroup_4  	0-15  				0 					��ռ���ȼ� 4 λ
																�����ȼ� 0λ 
ע�⣺��ֵԽС�����ȼ�Խ��  
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
////	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x100);/*�����ж�����ƫ�Ʊ�����1ָ���ж���������ARM�����ڴ���洢���У�Ĭ����Flash�����Բ�����Ҳ��Ҫ����ʹ��RAM���Ե�ʱ���������*/
//												 /*����2��������Ļ�ַƫ�����ڹ̼����ĵ���˵��������Flash�����ֵһ��Ҫ��0x08000100�ߣ�����RAM���ֵҪ��0x100�ߣ��������ֵһ��Ҫ��256(4*64)��������*/		

//	/* Enable the TIM7 gloabal Interrupt */
//    NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;	  
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;	
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
////	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x100);/*�����ж�����ƫ�Ʊ�����1ָ���ж���������ARM�����ڴ���洢���У�Ĭ����Flash�����Բ�����Ҳ��Ҫ����ʹ��RAM���Ե�ʱ���������*/

	/* Enable the DMAChannel1_IRQChannel  Interrupt */
//	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
}
