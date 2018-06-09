#ifndef __1602_H__
#define __1602_H__

#include "stm32f10x.h"
#include "bsp_SysTick.h"


 /*******
 *按键按下标置
 KEY_ON 0
 KEY_OFF 1
 ********/
//#define ON	0
//#define OFF	1

void lcd_GPIO_Config (void);
void Lcd_Write_Com (uint8_t Com);
void Lcd_Write_Dat (uint8_t Dat);
void Lcd_Int (void);
void Read_Busy(void);
void LCD_Clear (void); 
void LCD_Write_Char (uint8_t x, uint8_t y, uint8_t Data);
void LCD_Write_String (uint8_t x, uint8_t y, uint8_t *s); 
 

#endif
