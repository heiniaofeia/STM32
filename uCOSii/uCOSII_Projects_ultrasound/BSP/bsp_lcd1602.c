/*
 * @file   : bsp_lcd1602.c
 * @author : long
 * @version: V1.0.0
 * @date   : 2016.12.13
 * @history:
 * @details: lcd1602 source file
 */
#include "bsp_lcd1602.h"  
#include "bsp_lib.h"



/*
 * @function: Lcd1602_GPIO_Config
 * @details : ����lcd1602����
 * @input   :
 * @output  :
 * @return  :
 */
void Lcd1602_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/*���������˿ڣ�PA����ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);
	
	/* configuration LCD1602 Data I/O 0-7*/	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_Init(GPIOD, &GPIO_InitStructure);		

	/* configuration LCD2004 RS(����/����ѡ���H/L),RW(��/дѡ���H/L),E(ʹ���ź�) */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12; 
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/*
 * @function: Lcd_Write_Com
 * @details : write Command
 * @input   : 1.Com: �������
 * @output  : NULL
 * @return  : NULL
 */
void Lcd_Write_Com(uint8_t Com)
{	    
	GPIO_ResetBits(GPIOC, GPIO_Pin_10);                                        /* rs=0; */
	GPIO_ResetBits(GPIOC, GPIO_Pin_11);                                        /* rw=0; */
	GPIO_SetBits(GPIOC, GPIO_Pin_12);                                          /* E=1; */
 
//	GPIOD -> ODR = ((GPIOD -> IDR) & 0xff00) | Com;                            /* ��ȡ��8λI/O��״ֵ̬����8λ����Ӱ��. */   
//	GPIO_Write (GPIOD, (GPIO_ReadInputData (GPIOD) & 0Xff00) | Com);
	GPIO_Write(GPIOD, Com);
	RoughDelay_us(200);
	
	GPIO_ResetBits(GPIOC, GPIO_Pin_12);                                        /* E=0; */
}


/*
 * @function: Lcd_Write_Dat
 * @details : write data.
 * @input   : 1.Dat: д������ݡ�
 * @output  : NULL
 * @return  : NULL
 */
void Lcd_Write_Dat(uint8_t Dat)
{
	GPIO_SetBits(GPIOC, GPIO_Pin_10);                                          /* rs=1; */
	GPIO_ResetBits(GPIOC, GPIO_Pin_11);                                        /* rw=0; */
	GPIO_SetBits(GPIOC, GPIO_Pin_12);                                          /* E=1;  */

//	GPIOD -> ODR = ((GPIOD -> IDR) & 0xff00) | Dat;
//	GPIO_Write(GPIOD, (GPIO_ReadInputData(GPIOD) & 0Xff00) | Dat);
	GPIO_Write(GPIOD, Dat);
	
	RoughDelay_us(200);
	
	GPIO_ResetBits(GPIOC, GPIO_Pin_12);                                        /*E=0;*/	
}


/*
 * @function: LCD_Write_Char
 * @details : write char data.
 * @input   : 1.x: ������
              2.y: ������
              3.y: �ַ����ݡ�
 * @output  : NULL
 * @return  : NULL
 */
void LCD_Write_Char(uint8_t x, uint8_t y, uint8_t Data) 
{     
	if(y == 0) 
	{     
		Lcd_Write_Com(0x80 + x);                                               /* LCD��1����ʾ��ַ1~20(0x80~0x93). */     
	}    
	else if(y == 1)  
	{
		Lcd_Write_Com(0xC0 + x);                                               /*LCD��2����ʾ��ַ1~20(0xc0~0xd3)*/  
	}  
	else if(y == 2)  
	{
		Lcd_Write_Com(0x94 + x);                                               /*LCD��3����ʾ��ַ1~20(0x94~0x93)*/     
	} 
	else if(y == 3)  
	{     
		Lcd_Write_Com(0xd4 + x);                                               /*LCD��4����ʾ��ַ1~20(0xd4~0xe7)*/     
	}  

	Lcd_Write_Dat(Data);  
}


/*
 * @function: LCD_Write_String
 * @details : write string.
 * @input   : 1.x: ������
              2.y: ������
              3.s: �ַ������ݡ�
 * @output  : NULL
 * @return  : NULL
 */
void LCD_Write_String(uint8_t x, uint8_t y, uint8_t *s) 
{        
    while(*s) 
    {     
        LCD_Write_Char(x, y, *s);     
        s++;
        x++;   
    }
}


/*
 * @function: LCD_Clear
 * @details : ����.
 * @input   : NULL
 * @output  : NULL
 * @return  : NULL
 */
void LCD_Clear(void) 
{ 
    Lcd_Write_Com(0x01);
	RoughDelay_us(2000);   
}


/*
 * @function: Read_Busy
 * @details : Read LCD2004 state.
 * @input   : NULL
 * @output  : NULL
 * @return  : NULL
 */
void Read_Busy(void)
{
//    GPIO_SetBits(GPIOD, GPIO_Pin_7);
    
    GPIO_SetBits(GPIOC, GPIO_Pin_10);                                          /* RS = 0. */
    GPIO_ResetBits(GPIOC, GPIO_Pin_11);                                        /* RW = 1. */
    GPIO_SetBits(GPIOC, GPIO_Pin_12);                                          /* E=1; */
    
    while( (GPIOD->IDR) & 0x80);    
    GPIO_ResetBits(GPIOC, GPIO_Pin_12);                                        /* E=0; */
}


/*
 * @function: Lcd1602_Init
 * @details : ��ʼ��lcd1602
 * @input   :
 * @output  :
 * @return  :
 */
void Lcd1602_Init(void)
{
	Lcd1602_GPIO_Config();
	
	
	Lcd_Write_Com(0x38);                                                       /* ��ʾģʽ���õ�һ�Σ�����8λ��ʽ��2�У�5x7. */
	RoughDelay_us(3000);                                                       /* ��ʱ3ms. */       
	Lcd_Write_Com(0x38);                                                       /* ��ʾģʽ���õڶ���. */
	RoughDelay_us(3000);                                                       /* ��ʱ3ms. */       
	Lcd_Write_Com(0x38);                                                       /* ��ʾģʽ���õ����. �*/
	RoughDelay_us(3000);                                                       /* ��ʱ3ms. */       
	Lcd_Write_Com(0x38);                                                       /* ��ʾģʽ���õ��Ĵ�. */
	RoughDelay_us(3000);                                                       /* ��ʱ3ms. */       

	Lcd_Write_Com(0x08);                                                       /* ��ʾ�ر�. */
	Lcd_Write_Com(0x01);                                                       /* ��ʾ����. */ 
	RoughDelay_us(3000);                                                       /* ��ʱ3ms. */       
	Lcd_Write_Com(0x06);                                                       /* ��ʾ����ƶ�����,��LCDÿ�ӵ�1byte���ݺ�AC�Զ���1. */   
	Lcd_Write_Com(0x0C);                                                       /* ��ʾ�����Լ��������. */	
}

/*********************************************END OF FILE**********************/
