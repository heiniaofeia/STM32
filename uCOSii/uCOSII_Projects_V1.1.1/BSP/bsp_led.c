/*
 * @file   : bsp_led.c
 * @author : DragonFly
 * @version: V1.0.0
 * @date   : 2016.12.13
 * @history:
 * @details: led source file
 */
#include "bsp_led.h"  



/*---------------------------------------------------------------------------
                                Variable definition
----------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
                                Function definition
----------------------------------------------------------------------------*/
/*
 * @function: LED_GPIO_Config
 * @details : ����led����
 * @input   :
 * @output  :
 * @return  :
 */
void LED_GPIO_Config(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure;									/* ����һ��GPIO_InitTypeDef���͵Ľṹ��. */	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);					/* ����LED������ʱ��. */													   

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;		            /* ѡ��Ҫ���Ƶ�GPIOB����.  */		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   						/* ��������ģʽΪͨ���������*/ 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 						/* ������������Ϊ50MHz. */ 
	GPIO_Init(GPIOB, &GPIO_InitStructure);									/* ���ÿ⺯������ʼ��GPIOB0. */														   
}


/*
 * @function: LED_GPIO_Config
 * @details : ����led����
 * @input   :
 * @output  :
 * @return  :
 */
void LED_Init(void)
{
	LED_GPIO_Config();

	macLED1_OFF();
	macLED2_OFF();
}

/*********************************************END OF FILE**********************/
