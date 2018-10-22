/*
 * @file   : bsp_pwm.c
 * @author : DragonFly
 * @version: V1.0.0
 * @date   : 2016.12.13
 * @history:
 * @details: pwm source file
 */
#include "bsp_pwm.h" 



/*---------------------------------------------------------------------------
                                Variable definition
----------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
                                Function definition
----------------------------------------------------------------------------*/
/*
 * @function: TIM2_GPIO_Config
 * @details : ����Time2���pwm������
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
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}


/*
 * @function: TIM2_GPIO_Config
 * @details : ����Time2���pwm�źš�
 * @input   : NULL
 * @output  : NULL
 * @return  : NULL
 */
static void TIM2_Configuration(void) 
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	
	/* ����TIM3CLK Ϊ 72MHZ */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

		
	TIM_DeInit(TIM2);
	TIM_TimeBaseStructure.TIM_Prescaler = 2879;                                 /* ʱ��Ԥ��Ƶ��, 2880��Ƶ. */
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;                 /* ���ϼ���ģʽ, �������. */
	TIM_TimeBaseStructure.TIM_Period = TIM2Period;                              /* PWM����. */
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;                     /* ������Ƶ, ����Ƶ�� */
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1 ---------------------------------------------------------------*/
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                           /* ����ΪPWMģʽ1*/
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
//	TIM_OCInitStructure.TIM_Pulse = 0;                                          /* ��������ֵ�������������������ֵʱ����ƽ�������� */
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;                   /* ����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ */
//	TIM_OC1Init(TIM2, &TIM_OCInitStructure);                                    /* ʹ��ͨ��1 */
//	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);	
	/* ------------------------------------------------------------------------------------------------*/
	
	/* PWM1 Mode configuration: Channel2 ---------------------------------------------------------------*/
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                           /* ����ΪPWMģʽ1*/
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	TIM_OCInitStructure.TIM_Pulse = 0;                                          /* ��������ֵ�������������������ֵʱ����ƽ�������� */
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;                    /* ����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ */
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);                                    /* ʹ��ͨ��1 */
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);	
	/* ------------------------------------------------------------------------------------------------*/
	
	
	TIM_ARRPreloadConfig(TIM2, ENABLE);                                         /* ������ֹ�ڶ�ʱ��������ʱ����ARR�Ļ�����д����ֵ */
	
//	TIM_ClearFlag(TIM2, TIM_FLAG_Update);										/* Clear TIM2 update pending flag */
//	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);									/* Enable TIM2 Update interrupt */

	TIM_Cmd(TIM2, ENABLE);
	TIM_CtrlPWMOutputs(TIM2, ENABLE);
}


/*
 * @function: TIM2_PWM_Init
 * @details : ��ʼ��TIM2_PWM��
 * @input   : NULL
 * @output  : NULL
 * @return  : NULL
 */
void TIM2_PWM_Init(void)
{
	TIM2_GPIO_Config();
	TIM2_Configuration();	
}

/*********************************************END OF FILE**********************/
