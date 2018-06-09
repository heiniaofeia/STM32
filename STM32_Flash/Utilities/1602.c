/**
  ******************************************************************************
  * @file    bsp_SHUMAGUAN.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   按键应用bsp（扫描模式）
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 iSO STM32 开发板 
  * 论坛    :http://www.chuxue123.com
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
#/**
  ******************************************************************************
  * @file    bsp_SHUMAGUAN.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   按键应用bsp（扫描模式）
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 iSO STM32 开发板 
  * 论坛    :http://www.chuxue123.com
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
#include "1602.h" 
/**
  * @brief  配置按键用到的I/O口
  * @param  无
  * @retval 无
  */
 
void Delay(__IO u32 nCount)
{
	for(; nCount != 0; nCount--);
}

void lcd_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*开启按键端口（PA）的时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	
	/* configuration LCD1602 Data I/O 0-7*/	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7; 
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	/* configuration LCD1602 RS(数据/命令选择端H/L),RW(读/写选择端H/L),E(使能信号)*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12; 
	GPIO_Init(GPIOC, &GPIO_InitStructure);		   
}


void Lcd_Write_Com(uint8_t Com)
{	    
	GPIO_ResetBits(GPIOC, GPIO_Pin_10);								/*rs=0;*/
	GPIO_ResetBits(GPIOC, GPIO_Pin_11);								/*rw=0;*/
	GPIO_SetBits(GPIOC, GPIO_Pin_12);								/*E=1;*/
 
//	GPIOD -> ODR = ((GPIOD -> IDR) & 0xff00) | Com;					/*读取高8位I/O口状态值，低8位不受影响*/   
//	GPIO_Write(GPIOD, (GPIO_ReadInputData (GPIOD) & 0Xff00) | Com);
	GPIO_Write(GPIOD, Com);
	Delay_us(100);													/*通常需要延时5ms左右，不然有可能出错*/

	GPIO_ResetBits(GPIOC, GPIO_Pin_12);								/*E=0;*/
}


void Lcd_Write_Dat(uint8_t Dat)
{ 
	GPIO_SetBits(GPIOC, GPIO_Pin_10);								/*rs=1;*/
	GPIO_ResetBits(GPIOC, GPIO_Pin_11);								/*rw=0;*/
	GPIO_SetBits(GPIOC, GPIO_Pin_12);								/*E=1;*/

//	GPIOD -> ODR = ((GPIOD -> IDR) & 0xff00) | Dat;
//	GPIO_Write(GPIOD, (GPIO_ReadInputData(GPIOD) & 0Xff00) | Dat);
	GPIO_Write(GPIOD, Dat);
	Delay_us(50);													/*通常需要延时5ms左右，不然有可能出错*/

	GPIO_ResetBits(GPIOC, GPIO_Pin_12);								/*E=0;*/	
}


void LCD_Write_Char(uint8_t x, uint8_t y, uint8_t Data) 
 {     
    if (y == 0) 
 	{     
        Lcd_Write_Com(0x80 + x);     
 	}    
    else 
 	{     
        Lcd_Write_Com(0xC0 + x);     
 	}  
    
    Lcd_Write_Dat(Data);  
}



void LCD_Clear(void) 
{ 
    Lcd_Write_Com(0x01);
    Delay_us(500);
}


void Read_Busy()
{
    GPIOD -> IDR = (GPIOC -> IDR & 0x80);
    
    GPIO_SetBits(GPIOC, GPIO_Pin_10);							/*RS = 0*/
    GPIO_ResetBits(GPIOC, GPIO_Pin_11);							/*RW = 1*/
    GPIO_SetBits(GPIOC, GPIO_Pin_12);							/*E=1;*/
    
    while(GPIOC -> IDR & 0x80);    
    GPIO_ResetBits(GPIOC, GPIO_Pin_2);							/*E=0;*/
}


void LCD_Write_String(uint8_t x, uint8_t y, uint8_t *s) 
{        
    while(*s) 
    {     
        LCD_Write_Char(x, y, *s);     
        s++;
        x++;   
    }
}


void Lcd_Int(void)
{ 
	Delay_us(15000); 
    Lcd_Write_Com(0x38);
    Delay_us(5000);  
    Lcd_Write_Com(0x38); 
    Delay_us(5000);
    Lcd_Write_Com(0x38); 


    Lcd_Write_Com(0x38);/*显示模式设置*/
    Lcd_Write_Com(0x08);/*显示关闭*/
    Lcd_Write_Com(0x01);/*显示清屏*/ 
    Lcd_Write_Com(0x06);/*显示光标移动设置*/   
    Lcd_Write_Com(0x0C);/*?显示开启以及光标设置*/
}


