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
 * @function: TIM8_GPIO_Config
 * @details : ����Time8���pwm������
 * @input   : NULL
 * @output  : NULL
 * @return  : NULL
 */
static void TIM8_GPIO_Config(void) 
{
	GPIO_InitTypeDef GPIO_InitStructure;

	
	/* GPIOx clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
	
	
	/*GPIOA Configuration: TIM2 channel 1 and 2 as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
//	GPIO_Init(GPIOC, &GPIO_InitStructure);	
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
//	GPIO_Init(GPIOB, &GPIO_InitStructure);	

}


/*
 * @function: TIM1_Configuration
 * @details : ����TIM1�����PWM�źŵ�ģʽ�������ڡ����ԡ�ռ�ձ�
 *            TIMxCLK/CK_PSC --> TIMxCNT --> TIMx_ARR --> TIMxCNT ���¼���
 *                               TIMx_CCR(��ƽ�����仯)
 *            �ź�����=(TIMx_ARR +1 ) * ʱ������
 *            ռ�ձ�=TIMx_CCR/(TIMx_ARR +1) 
 * @input   : NULL
 * @output  : NULL
 * @return  : NULL
 */
void TIM8_Configuration(void)
{
#define  DEAD_TIME_VALUE(val)	( (u16) (  (val)*(72*0.001) )+(( ( (u16)( (val)*(72*0.001) ) * 10  ) % 10 ) < 5 ? 0 : 1 ))				 //	   ����ʱ��

	uint16_t    TIM8Period = 0;
	uint16_t    TIM8Channel1Pulse = 0;
	uint16_t    TIM8Channel3Pulse = 0;
	
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_BDTRInitTypeDef  TIM_BDTRInitStructure;

//	TIM8Period = 7199;															/* 10KHz, TIM_Pulse = 6/100,duty cycle: 5.20% */
//	TIM8Period = 4799;															/* 15KHz, TIM_Pulse = 6/100,duty cycle: 4.70%, TIM_Pulse = 6/100,duty cycle: 5.90% */		
//	TIM8Period = 3599;															/* 20KHz, TIM_Pulse = 6/100,duty cycle: 4.40%; TIM_Pulse = 7/100,duty cycle: 5.60% */
	TIM8Period = 2879;															/* 25KHz, TIM_Pulse = 7/100,duty cycle: 5.00%; TIM_Pulse = 8/100,duty cycle: 6.50% */	
//	TIM8Period = 2677;															/* 30KHz, TIM_Pulse = 8/100,duty cycle: 5.66% */
//	TIM8Period = 2057;															/* 35KHz, TIM_Pulse = 8/100,duty cycle: 5.24%; TIM_Pulse = 9/100,duty cycle: 5.96% */	
//	TIM8Period = 1799;															/* 40KHz, TIM_Pulse = 9/100,duty cycle: 5.60% */
//	TIM8Period = 1499;															/* 45KHz, TIM_Pulse = 8/100,duty cycle: 4.30%; TIM_Pulse = 9/100,duty cycle: 5.28% */
//	TIM8Period = 1439;															/* 50KHz, TIM_Pulse = 9/100,duty cycle: 5.00%;*/
//	TIM8Period = 1308;															/* 55KHz, TIM_Pulse = 10/100,duty cycle: 5.49% */
//	TIM8Period = 1199;															/* 60KHz, TIM_Pulse = 10/100,duty cycle: 5.40% */
//	TIM8Period = 1107;															/* 65KHz, TIM_Pulse = 10/100,duty cycle: 4.50% */
//	TIM8Period = 1028;															/* 70KHz */
//	TIM8Period = 959;															/* 75KHz, TIM_Pulse = 11/100,duty cycle: 5.2% */
//	TIM8Period = (uint16_t)((uint32_t)TIM8Period * 50 / 100);


	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	

	/* Compute CCR2 value to generate a duty cycle at 5% for channel 2 and 2N */
	TIM8Channel1Pulse = (uint16_t) ((uint32_t)(TIM8Period + 1) * 9 / 100);	
//	/* Compute CCR2 value to generate a duty cycle at 5% for channel 2 and 2N */
//	TIM8Channel2Pulse = (uint16_t) ((uint32_t)(TIM8Period + 1) * 9 / 100);	
	/* Compute CCR3 value to generate a duty cycle at 2% for channel 3 */	
	TIM8Channel3Pulse = (uint16_t) ((uint32_t)(TIM8Period + 1) * 2 / 100);	
	/*
	TIM1CLK = SystemCoreClock, Prescaler = 0, TIM1 counter clock = SystemCoreClock
	SystemCoreClock is set to 72 MHz for Low-density, Medium-density, High-density
	and Connectivity line devices and to 24 MHz for Low-Density Value line and
	Medium-Density Value line devices
	The Timer pulse is calculated as follows:
	 - ChannelxPulse = DutyCycle * (TIM1_Period - 1) / 100
	----------------------------------------------------------------------- */
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Prescaler = 0;									/* Ԥ��Ƶ��(719+1)=720 */
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1;		/* �������ģʽ: PWMƵ��Ϊ25Hz; ���ϼ���:PWMƵ��Ϊ50Hz */														
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;					/* ����ģʽ�����ϼ���*/
	TIM_TimeBaseStructure.TIM_Period = TIM8Period;								
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;						/* �ⲿʱ�ӷ�Ƶ����(0+1)=1��������û�õ� */
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;							/* �ظ������������ظ�������ٴβŸ�����һ������ж�(ֻ������TIM1��TIM8) */
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);

	/* PWM1&&PWM3 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_Pulse = TIM8Channel1Pulse;							/* ���õ�ƽ����ֵ����������������෴ */
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  					/* Use positive logic */
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;  				/* Use positive logic */
//	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCNPolarity_Low;
//	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;				/* IRF540�ߵ�ƽ��ͨ���������ùܽ�Ĭ�����0��ƽ */		
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
	
	/* PWM2&&PWM4 Mode configuration: Channel2 */
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
//	TIM_OCInitStructure.TIM_Pulse = TIM8Channel2Pulse;							/* ���õ�ƽ����ֵ����������������෴ */
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  					/* Use positive logic */
//	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;  				/* Use positive logic */
////	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCNPolarity_Low;
////	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
//	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;				/* IRF540�ߵ�ƽ��ͨ���������ùܽ�Ĭ�����0��ƽ */		
//	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
//	TIM_OC2Init(TIM8, &TIM_OCInitStructure);
//	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);

//	TIM_SelectOutputTrigger(TIM8, TIM_TRGOSource_OC2Ref);						/* ����ѡ��ʱ����TRGO; �������TIM1_CC4�������ͱ���ʹ�øú�������ΪCC4����TRGO������ */

	/* Mode configuration: Channel3 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	TIM_OCInitStructure.TIM_Pulse = TIM8Channel3Pulse;							/* ���õ�ƽ����ֵ����������������෴ */
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  					/* Use positive logic */
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;  				/* Use positive logic */
//	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCNPolarity_Low;
//	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;				/* IRF540�ߵ�ƽ��ͨ���������ùܽ�Ĭ�����0��ƽ */		
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;									
  	TIM_OC3Init(TIM8, &TIM_OCInitStructure);
	TIM_SelectOutputTrigger(TIM8, TIM_TRGOSource_OC3Ref);						/* ����ѡ��ʱ����TRGO; �������TIM1_CC4�������ͱ���ʹ�øú�������ΪCC4����TRGO������ */

    /* Automatic Output enable, Break, dead time and lock configuration*/
	TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
	TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
	TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_1; 
	TIM_BDTRInitStructure.TIM_DeadTime = DEAD_TIME_VALUE(800);					/* DeadTime ~800ns */
	TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;
	TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
	TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;		/* if used: may cause "TIM_CtrlPWMOutputs(TIM1, ENABLE)" lose efficacy */
	TIM_BDTRConfig(TIM8,&TIM_BDTRInitStructure);

//	TIM_ARRPreloadConfig(TIM8,DISABLE);											/* ������ֹ�ڶ�ʱ��������ʱ����ARR�Ļ�����д����ֵ */

//	TIM_ClearFlag(TIM8, TIM_FLAG_Update);										/* Clear TIM8 update pending flag */

//	TIM_ITConfig(TIM8, TIM_IT_Update, ENABLE);									/* Enable TIM8 Update interrupt */		

	TIM_Cmd(TIM8, ENABLE);														/* TIM1 enable counter ��ʼ�ȹر�TIM1*/ 
//	TIM_Cmd(TIM8, DISABLE);		

	TIM_CtrlPWMOutputs(TIM8, ENABLE);											/* Main Output Enable */
//	TIM_CtrlPWMOutputs(TIM8, DISABLE);
}


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
	
	uint16_t TIM2Period;
	
	
	/* ����TIM3CLK Ϊ 72MHZ */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM2Period = 100;
	/* Compute CCR1 value to generate a duty cycle at 50% for channel 1 and 1N */

	
	TIM_DeInit(TIM2);
	TIM_TimeBaseStructure.TIM_Prescaler = 719;                                  /* ʱ��Ԥ��Ƶ��, 719��Ƶ. */
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
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;                   /* ����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ */
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;                    /* ����ʱ������ֵС��CCR1_ValʱΪ�͵�ƽ */	
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);                                    /* ʹ��ͨ��1 */
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);	
	/*-------------------------------------------------------------------------------------------------------*/

	/* PWM1 Mode configuration: Channel3 ---------------------------------------------------------------*/
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                           /* ����ΪPWMģʽ1*/
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
//	TIM_OCInitStructure.TIM_Pulse = 0;                                          /* ��������ֵ�������������������ֵʱ����ƽ�������� */
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;                   /* ����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ */
//	TIM_OC3Init(TIM2, &TIM_OCInitStructure);                                    /* ʹ��ͨ��1 */
//	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);	
	/*-------------------------------------------------------------------------------------------------------*/
	
	TIM_ARRPreloadConfig(TIM2, ENABLE);                                         /* ������ֹ�ڶ�ʱ��������ʱ����ARR�Ļ�����д����ֵ */
	
//	TIM_ClearFlag(TIM2, TIM_FLAG_Update);										/* Clear TIM2 update pending flag */
//	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);									/* Enable TIM2 Update interrupt */

	TIM_Cmd(TIM2, ENABLE);
	TIM_CtrlPWMOutputs(TIM2, ENABLE);
}


/*
 * @function: TIM8_PWM_Init
 * @details : ��ʼ��TIM2_PWM��
 * @input   : NULL
 * @output  : NULL
 * @return  : NULL
 */
void TIM8_PWM_Init(void)
{
	TIM8_GPIO_Config();
	TIM8_Configuration();	
	
	Microwaves.CtlSwitch = OFF;
	Microwaves.Freq = 0;
	Microwaves.FreqMin = PWM_FREQ_MIN;
	Microwaves.FreqMax = PWM_FREQ_MAX;
	
	Microwaves.FeedbackVoltage = 0;
}

