/*
 * @file   : Matrixkey.c
 * @author : DragonFly
 * @version: V1.0.0
 * @date   : 2016.12.13
 * @history:
 * @details: Matrixkey source file
 */
#include "Matrixkey.h"
#include "bsp_lib.h"
#include <ucos_ii.h>


/*---------------------------------------------------------------------------
                                Variable definition
----------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
                                Function definition
----------------------------------------------------------------------------*/
/*
 * @function: MatrixkeyConfig
 * @details : 配置矩阵按键
 * @input   : NULL
 * @output  : NULL
 * @return  : NULL
 */ 
void MatrixkeyConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	
	
	/*矩阵键盘初始化函数；PE0~PE3设为输出模式，PE4~PE7设为输入模式*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}


/*
 * @function: GetKeyValue
 * @details : 获取按键值
 * @input   : NULL
 * @output  : NULL
 * @return  : 按键值
 */ 
uint8_t GetKeyValue(void)
{
	uint8_t temp_key = 0;
    uint8_t key = 0;
    
    
	GPIO_Write(KEY_PORT, 0x00FE);
	temp_key = GPIO_ReadInputData(KEY_PORT);
	temp_key = temp_key & 0xF0;
	if(temp_key != 0xF0)
	{
//		RoughDelay_us(1000);
		OSTimeDlyHMSM(0, 0, 0, 10);
		temp_key = GPIO_ReadInputData(KEY_PORT);
		temp_key = (temp_key & 0xF0);
		if(temp_key != 0xF0)
		{
			switch(temp_key)
			{
				case 0xee: key = '1';  break;
				case 0xde: key = '4';  break;
				case 0xbe: key = '7';  break;
				case 0x7e: key = '.';  break;
			}	  
		}	
	}

    
	GPIO_Write(KEY_PORT, 0x00FD);
	temp_key = GPIO_ReadInputData(KEY_PORT);
	temp_key = temp_key & 0xF0;
	if (temp_key != 0xF0)
	{
//		RoughDelay_us(1000);
		OSTimeDlyHMSM(0, 0, 0, 10);
		temp_key = GPIO_ReadInputData(KEY_PORT);
		temp_key = temp_key & 0x0F;
		if(temp_key != 0xF0)
		{
			temp_key = GPIO_ReadInputData(KEY_PORT);
			switch(temp_key)
			{
				case 0xed: key='2';  break;
				case 0xdd: key='5';  break;
				case 0xbd: key='8';  break;
				case 0x7d: key='0';  break;
			}	  

		}	
	}

    
	GPIO_Write(KEY_PORT, 0x00FB);
	temp_key = GPIO_ReadInputData(KEY_PORT);
	temp_key = temp_key & 0xF0;
	if (temp_key != 0xF0)
	{
//		RoughDelay_us(1000);
		OSTimeDlyHMSM(0, 0, 0, 10);
		temp_key = GPIO_ReadInputData(KEY_PORT);
		temp_key = temp_key & 0x0F;
		if(temp_key != 0x0F)
		{
			temp_key = GPIO_ReadInputData(KEY_PORT);
			switch(temp_key)
			{
				case 0xeb: key='3';  break;
				case 0xdb: key='6';  break;
				case 0xbb: key='9';  break;
				case 0x7b: key='=';  break;
			}	  
		}	
	}

    
	GPIO_Write(KEY_PORT, 0x00F7);
	temp_key = GPIO_ReadInputData(KEY_PORT);
	temp_key = temp_key & 0xF0;
	if(temp_key != 0xF0)
	{
//		RoughDelay_us(1000);
		OSTimeDlyHMSM(0, 0, 0, 10);
		temp_key = GPIO_ReadInputData(KEY_PORT);
		temp_key = temp_key & 0xF0;
		if(temp_key != 0xF0)
		{
			temp_key = GPIO_ReadInputData(KEY_PORT);
			switch(temp_key)
			{
				case 0xe7: key='+';  break;
				case 0xd7: key='-';  break;
				case 0xb7: key='*';  break;
				case 0x77: key='/';  break;
			}
		}	
	} 

	return key;
}


/*
 * @function: MatrixkeyInit
 * @details : 初始化矩阵按键
 * @input   : NULL
 * @output  : NULL
 * @return  : NULL
 */ 
void MatrixkeyInit(void)
{
	MatrixkeyConfig();
	
	Matrixkey.Value = 0;
}
