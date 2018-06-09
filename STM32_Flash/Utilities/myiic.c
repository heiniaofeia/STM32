/**
  ******************************************************************************
  * @file    myiic.c
  * @author  Long 
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   用gpio模拟i2c总线, 适用于STM32系列CPU。该模块不包括应用层命令帧，仅包括I2C总线基本操作函数。
  ******************************************************************************
  * @attention
  *
  * 实验平台:主控板 MINI STM32
  * 
  ******************************************************************************
  */
#include "myiic.h"



/*********************************************************************************************************
*	函 数 名: IIC_Init
*	功能说明: IIC的GPIO口初始化
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************/
void IIC_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_10|GPIO_Pin_11); 	//PB10,PB11 输出高
}


/*********************************************************************************************************
*	函 数 名: IIC_Init
*	功能说明: 产生IIC起始信号
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************/
void IIC_Start(void)
{
	SDA_OUT();     	//sda线输出
	IIC_SDA(1);		//IIC_SDA=1;	  	  
	IIC_SCL(1);		//IIC_SCL=1;
	Delay_us(4);
 	IIC_SDA(0);		//IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	Delay_us(4);
	IIC_SCL(0);		//IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}


/*********************************************************************************************************
*	函 数 名: IIC_Stop
*	功能说明: 产生IIC停止信号
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************/
void IIC_Stop(void)
{
	SDA_OUT();		//sda线输出
	IIC_SCL(0);		//IIC_SCL=0;
	IIC_SDA(0);		//IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	Delay_us(4);
	IIC_SCL(1);		//IIC_SCL=1; 
	IIC_SDA(1);		//IIC_SDA=1;//发送I2C总线结束信号
	Delay_us(4);							   	
}

/*********************************************************************************************************
*	函 数 名: IIC_Wait_Ack
*	功能说明: 等待应答信号到来
*	形    参：无
*	返 回 值: 1，接收应答失败;0，接收应答成功
*********************************************************************************************************/      
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	
	SDA_IN();      								//SDA设置为输入  
	IIC_SDA(1);
	Delay_us(1);
	
	IIC_SCL(1);									//IIC_SCL=1;
	Delay_us(1);	 
	
	while(GPIO_ReadInputData(GPIOB) & 0x0800)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL(0);									//IIC_SCL=0;//时钟输出0 	   
	return 0;  
}


/*********************************************************************************************************
*	函 数 名: IIC_Ack
*	功能说明: 产生ACK应答
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************/      
void IIC_Ack(void)
{
	IIC_SCL(0);		//IIC_SCL=0;
	SDA_OUT();
	IIC_SDA(0);		//IIC_SDA=0;
	Delay_us(2);
	IIC_SCL(1);		//IIC_SCL=1;
	Delay_us(2);
	IIC_SCL(0);		//IIC_SCL=0;
}

/*********************************************************************************************************
*	函 数 名: IIC_Ack
*	功能说明: 不产生ACK应答	
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************/      	    
void IIC_NAck(void)
{
	IIC_SCL(0);		//IIC_SCL=0;
	SDA_OUT();
	IIC_SDA(1);		//IIC_SDA=1;
	Delay_us(2);
	IIC_SCL(1);		//IIC_SCL=1;
	Delay_us(2);
	IIC_SCL(0);		//IIC_SCL=0;
}	


/*********************************************************************************************************
*	函 数 名: IIC_Send_Byte
*	功能说明: IIC发送一个字节，返回从机有无应答
*	形    参：数据txd
*	返 回 值: 无
*********************************************************************************************************/      	    		  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL(0);						//IIC_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC_SDA(1);				//IIC_SDA=1;
		else
			IIC_SDA(0);				//IIC_SDA=0;
		txd<<=1; 	  
		Delay_us(2);   				//对TEA5767这三个延时都是必须的
		IIC_SCL(1);					//IIC_SCL=1;
		Delay_us(2); 
		IIC_SCL(0);					//IIC_SCL=0;	
		Delay_us(2);
    }	 
} 

/*********************************************************************************************************
*	函 数 名: IIC_Read_Byte
*	功能说明: IIC读一个字节，返回从机有无应答，ack=1时，发送ACK，ack=0，发送nACK 
*	形    参：数据ack
*	返 回 值: 无
*********************************************************************************************************/      	    		  

  
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i, receive=0;
	SDA_IN();												//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC_SCL(0);											//IIC_SCL=0; 
        Delay_us(2);
		IIC_SCL(1);											//IIC_SCL=1;
        receive<<=1;
        if(GPIO_ReadInputData(GPIOB) & 0x0800) receive++; 	//读PB11口的状态值  
		Delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();											//发送nACK
    else
        IIC_Ack(); 											//发送ACK   
    return receive;
}



