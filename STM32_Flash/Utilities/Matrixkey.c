#include "Matrixkey.h"

  
void Matrixkey_Init(void)/*矩阵键盘初始化函数；PE0~PE3设为输出模式，PE4~PE7设为输入模式*/
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}


uint8_t Get_KeyValue(void)
{
	uint8_t temp_key = 0;
    uint8_t key = 0;
    
    
	GPIO_Write(KEY_PORT, 0xfe00);
	temp_key = GPIO_ReadInputData(KEY_PORT) >> 8;
	temp_key = temp_key & 0xf0;/*屏蔽低四位*/    
	if(temp_key != 0xf0)
	{
		Delay_us(1000);
		temp_key = GPIO_ReadInputData(KEY_PORT) >> 8;
		temp_key = temp_key & 0xf0;
		if(temp_key != 0xf0)
		{
			temp_key = GPIO_ReadInputData(KEY_PORT) >> 8;
			switch(temp_key)
			{
				case 0xee: key = '1';  break;
				case 0xde: key = '2';  break;
				case 0xbe: key = '3';  break;
				case 0x7e: key = '+';  break;
			}	  
			while(temp_key != 0xf0)/*等待按键释放*/
			{
				temp_key = GPIO_ReadInputData(KEY_PORT) >> 8;
				temp_key = temp_key & 0xf0;
			}
		}	
	}    /* end of if(temp_key!=0xf0)*/

    
	GPIO_Write(KEY_PORT, 0xfd00);
	temp_key = GPIO_ReadInputData(KEY_PORT) >> 8;
	temp_key = temp_key & 0xf0;/*11110000*/
	if (temp_key != 0xf0)
	{
		Delay_us(1000);
		temp_key = GPIO_ReadInputData(KEY_PORT) >> 8;
		temp_key = temp_key & 0xf0;
		if(temp_key != 0xf0)
		{
			temp_key = GPIO_ReadInputData(KEY_PORT) >> 8;
			switch(temp_key)
			{
				case 0xed: key='4';  break;
				case 0xdd: key='5';  break;
				case 0xbd: key='6';  break;
				case 0x7d: key='-';  break;
			}	  
			while(temp_key != 0xf0)/*等待按键释放*/
			{
				temp_key = GPIO_ReadInputData(KEY_PORT) >> 8;
				temp_key = temp_key & 0xf0;
			}
		}	
	}    /* end of if(temp_key!=0xf0)*/

    
	GPIO_Write(KEY_PORT, 0xfb00);
	temp_key = GPIO_ReadInputData(KEY_PORT) >> 8;
	temp_key = temp_key & 0xf0;/*11110000*/
	if (temp_key != 0xf0)
	{
		Delay_us(1000);
		temp_key = GPIO_ReadInputData(KEY_PORT) >> 8;
		temp_key = temp_key & 0xf0;
		if(temp_key != 0xf0)
		{
			temp_key = GPIO_ReadInputData(KEY_PORT) >> 8;
			switch(temp_key)
			{
				case 0xeb: key='7';  break;
				case 0xdb: key='8';  break;
				case 0xbb: key='9';  break;
				case 0x7b: key='*';  break;
			}	  
			while(temp_key != 0xf0)/*等待按键释放*/
			{
				temp_key = GPIO_ReadInputData(KEY_PORT) >> 8;
				temp_key = temp_key & 0xf0;
			}
		}	
	}    /* end of if(temp_key!=0xf0)*/

    
	GPIO_Write(KEY_PORT, 0xf700);
	temp_key = GPIO_ReadInputData(KEY_PORT) >> 8;
	temp_key = temp_key & 0xf0;/*11110000*/
	if(temp_key != 0xf0)
	{
		Delay_us(1000);
		temp_key = GPIO_ReadInputData(KEY_PORT) >> 8;
		temp_key = temp_key & 0xf0;
		if(temp_key != 0xf0)
		{
			temp_key = GPIO_ReadInputData(KEY_PORT) >> 8;
			switch(temp_key)
			{
				case 0xe7: key='.';  break;
				case 0xd7: key='0';  break;
				case 0xb7: key='=';  break;
				case 0x77: key='/';  break;
			}	  
			while(temp_key != 0xf0)/*等待按键释放*/
			{
				temp_key = GPIO_ReadInputData(KEY_PORT) >> 8;
				temp_key = temp_key & 0xf0;
			}
		}	
	} 

	return key;
}

