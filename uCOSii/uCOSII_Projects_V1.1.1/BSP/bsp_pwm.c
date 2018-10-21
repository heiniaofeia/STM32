/*
 * @file   : bsp_pwm.c
 * @author : DragonFly
 * @version: V1.0.0
 * @date   : 2016.12.13
 * @history:
 * @details: pwm source file
 */
#include "bsp_pwm.h" 
#include "global_variables.h"


/*---------------------------------------------------------------------------
                                Variable definition
----------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
                                Function definition
----------------------------------------------------------------------------*/
/*
 * @function: TIM2_GPIO_Config
 * @details : 配置Time2输出pwm的引脚
 * @input   : NULL
 * @output  : NULL
 * @return  : NULL
 */
static void TIM2_GPIO_Config(void) 
{
	GPIO_InitTypeDef GPIO_InitStructure;

	
	/* GPIOA clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 

	/*GPIOA Configuration: TIM2 channel 1 and 2 as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}


/*
 * @function: TIM2_GPIO_Config
 * @details : 配置Time2输出pwm信号。
 * @input   : NULL
 * @output  : NULL
 * @return  : NULL
 */
static void TIM2_Configuration(void) 
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	uint16_t TIM2Period;
	
	
	/* 设置TIM3CLK 为 72MHZ */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM2Period = PWM_FREQ_MAX;
	/* Compute CCR1 value to generate a duty cycle at 50% for channel 1 and 1N */

	
	TIM_DeInit(TIM2);
	TIM_TimeBaseStructure.TIM_Prescaler = 71;                                   /* 时钟预分频数, 72分频. */
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;                 /* 向上计数模式, 即左对齐. */
	TIM_TimeBaseStructure.TIM_Period = TIM2Period;                              /* PWM周期. */
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;                     /* 采样分频, 不分频。 */
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	/* PWM15 Mode configuration: Channel1 ---------------------------------------------------------------*/
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                           /* 配置为PWM模式1*/
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	TIM_OCInitStructure.TIM_Pulse = 0;                                          /* 设置跳变值，当计数器计数到这个值时，电平发生跳变 */
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;                   /* 当定时器计数值小于CCR1_Val时为高电平 */
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);                                    /* 使能通道1 */
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);	
	/* ------------------------------------------------------------------------------------------------*/
	
	
//	TIM_ARRPreloadConfig(TIM2,DISABLE);											/* 允许或禁止在定时器工作的时候向ARR的缓冲器写入新值 */
	
//	TIM_ClearFlag(TIM2, TIM_FLAG_Update);										/* Clear TIM2 update pending flag */
//	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);									/* Enable TIM2 Update interrupt */

	TIM_Cmd(TIM2, ENABLE);
	TIM_CtrlPWMOutputs(TIM2, DISABLE);
}


/*
 * @function: TIM2_PWM_Init
 * @details : 初始化TIM2_PWM。
 * @input   : NULL
 * @output  : NULL
 * @return  : NULL
 */
void TIM2_PWM_Init(void)
{
	TIM2_GPIO_Config();
	TIM2_Configuration();	
	
	Microwaves.CtlSwitch = OFF;
	Microwaves.Freq = 0;
	Microwaves.FreqMin = PWM_FREQ_MIN;
	Microwaves.FreqMax = PWM_FREQ_MAX;
	
	Microwaves.FeedbackVoltage = 0;
}

/*********************************************END OF FILE**********************/
