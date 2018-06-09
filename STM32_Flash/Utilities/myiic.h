#ifndef __MYIIC_H
#define __MYIIC_H

#include "stm32f10x.h"
#include "bsp_SysTick.h"


/*宏定义----------------------------------------------------------------------------------------------*/
/*IO方向设置*/
#define SDA_IN()  {GPIOB -> CRH &= 0XFFFF0FFF; GPIOB -> CRH |= 8<<12;}/*根据EEPROM芯片电路图配置PB11为上拉/下拉输入模式*/
#define SDA_OUT() {GPIOB -> CRH &= 0XFFFF0FFF; GPIOB -> CRH |= 3<<12;}/*根据EEPROM芯片电路图配置PB11为通用推挽输出模式*/

/*IO操作函数*/ 
#define IIC_SCL(x)  if (x)	\
 					GPIO_SetBits(GPIOB,GPIO_Pin_10);\
 					else	\
 					GPIO_ResetBits(GPIOB,GPIO_Pin_10)
					
#define IIC_SDA(x)  if (x)	\
 					GPIO_SetBits(GPIOB,GPIO_Pin_11);\
 					else	\
 					GPIO_ResetBits(GPIOB,GPIO_Pin_11)
/*----------------------------------------------------------------------------------------------*/

					
/*----------------------------------------------------------------------------------------------*/
void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号
void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	  
/*----------------------------------------------------------------------------------------------*/

#endif
















