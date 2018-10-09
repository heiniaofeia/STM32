/*
 * @file   : bsp_led.h
 * @author : long
 * @version: V1.0.0
 * @date   : 2016.12.13
 * @history:
 * @details: led head file
 */
#ifndef __BSP_LED_H__
#define	__BSP_LED_H__

#include "stm32f10x.h"
#include "global_variables.h"



/*---------------------------------------------------------------------------
                                Macro definition
----------------------------------------------------------------------------*/
/* ֱ�Ӳ����Ĵ����ķ�������IO */
#define	 mac_digitalHi(pGPIO, GPIO_data)         {pGPIO->BSRR = GPIO_data;}    //����Ϊ�ߵ�ƽ		
#define  mac_digitalLo(pGPIO, GPIO_data)         {pGPIO->BRR = GPIO_data;}     //����͵�ƽ
#define  mac_digitalToggle(pGPIO, GPIO_data)     {pGPIO->ODR ^= GPIO_data;}    //�����ת״̬


/* �������IO�ĺ� */
#define  macLED1_TOGGLE()                        mac_digitalToggle(GPIOB, GPIO_Pin_8)
#define  macLED1_OFF()                           mac_digitalHi(GPIOB, GPIO_Pin_8)
#define  macLED1_ON()                            mac_digitalLo(GPIOB, GPIO_Pin_8)

#define  macLED2_TOGGLE()                        mac_digitalToggle(GPIOB, GPIO_Pin_9)
#define  macLED2_OFF()                           mac_digitalHi(GPIOB, GPIO_Pin_9)
#define  macLED2_ON()                            mac_digitalLo(GPIOB, GPIO_Pin_9)


/*---------------------------------------------------------------------------
                                Variable type
----------------------------------------------------------------------------*/
extern struct tagStackCheck  LedStackCheck;


/*---------------------------------------------------------------------------
                                Variable declaration
----------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
                                Function declaration
----------------------------------------------------------------------------*/
void LED_GPIO_Config(void);
void LED_Init(void);

	
#endif 
