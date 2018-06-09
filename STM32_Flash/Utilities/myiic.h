#ifndef __MYIIC_H
#define __MYIIC_H

#include "stm32f10x.h"
#include "bsp_SysTick.h"


/*�궨��----------------------------------------------------------------------------------------------*/
/*IO��������*/
#define SDA_IN()  {GPIOB -> CRH &= 0XFFFF0FFF; GPIOB -> CRH |= 8<<12;}/*����EEPROMоƬ��·ͼ����PB11Ϊ����/��������ģʽ*/
#define SDA_OUT() {GPIOB -> CRH &= 0XFFFF0FFF; GPIOB -> CRH |= 3<<12;}/*����EEPROMоƬ��·ͼ����PB11Ϊͨ���������ģʽ*/

/*IO��������*/ 
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
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�
void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	  
/*----------------------------------------------------------------------------------------------*/

#endif
















