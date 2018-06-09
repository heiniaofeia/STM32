/**
  ******************************************************************************
  * @file    bsp_SHUMAGUAN.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ����Ӧ��bsp��ɨ��ģʽ��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� iSO STM32 ������ 
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
#/**
  ******************************************************************************
  * @file    bsp_SHUMAGUAN.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ����Ӧ��bsp��ɨ��ģʽ��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� iSO STM32 ������ 
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
#include "1602.h" 
/**
  * @brief  ���ð����õ���I/O��
  * @param  ��
  * @retval ��
  */
 
void Delay(__IO u32 nCount)
{
	for(; nCount != 0; nCount--);
}

void lcd_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*���������˿ڣ�PA����ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	
	/* configuration LCD1602 Data I/O 0-7*/	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7; 
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	/* configuration LCD1602 RS(����/����ѡ���H/L),RW(��/дѡ���H/L),E(ʹ���ź�)*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12; 
	GPIO_Init(GPIOC, &GPIO_InitStructure);		   
}


void Lcd_Write_Com(uint8_t Com)
{	    
	GPIO_ResetBits(GPIOC, GPIO_Pin_10);								/*rs=0;*/
	GPIO_ResetBits(GPIOC, GPIO_Pin_11);								/*rw=0;*/
	GPIO_SetBits(GPIOC, GPIO_Pin_12);								/*E=1;*/
 
//	GPIOD -> ODR = ((GPIOD -> IDR) & 0xff00) | Com;					/*��ȡ��8λI/O��״ֵ̬����8λ����Ӱ��*/   
//	GPIO_Write(GPIOD, (GPIO_ReadInputData (GPIOD) & 0Xff00) | Com);
	GPIO_Write(GPIOD, Com);
	Delay_us(100);													/*ͨ����Ҫ��ʱ5ms���ң���Ȼ�п��ܳ���*/

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
	Delay_us(50);													/*ͨ����Ҫ��ʱ5ms���ң���Ȼ�п��ܳ���*/

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


    Lcd_Write_Com(0x38);/*��ʾģʽ����*/
    Lcd_Write_Com(0x08);/*��ʾ�ر�*/
    Lcd_Write_Com(0x01);/*��ʾ����*/ 
    Lcd_Write_Com(0x06);/*��ʾ����ƶ�����*/   
    Lcd_Write_Com(0x0C);/*?��ʾ�����Լ��������*/
}


