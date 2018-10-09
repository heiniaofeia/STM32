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
 * @details : 配置led引脚
 * @input   :
 * @output  :
 * @return  :
 */
void LED_GPIO_Config(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure;									/* 定义一个GPIO_InitTypeDef类型的结构体. */	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);					/* 开启LED的外设时钟. */													   

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;		            /* 选择要控制的GPIOB引脚.  */		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   						/* 设置引脚模式为通用推挽输出*/ 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 						/* 设置引脚速率为50MHz. */ 
	GPIO_Init(GPIOB, &GPIO_InitStructure);									/* 调用库函数，初始化GPIOB0. */														   
}


/*
 * @function: LED_GPIO_Config
 * @details : 配置led引脚
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
