/********************************************************************************
* @file    stmflash.c
* @author  Long 
* @version V1.0
* @date    2015-xx-xx
* @brief   使用flash模拟EEPROM
******************************************************************************
* @attention
*
* 实验平台:主控板 MINI STM32
* 注意	  :(1)STM32的闪存编程是由FPEC(闪存编程和擦除控制器)模块处理的，这个模块包含7个32位寄存器，具体的看数据手册
*		   (2)STM32闪存的编程每次必须写入16位，写入32位要分两次写入
*		   (3)STM32在Flash编程的时候, 必须要求其写入地址的Flash是被擦出了的(即储存单元的值是0xFFFF)
*		   (4)擦除扇区以页为单位
*		   (5)储存单元应该尽量选择靠近主储存器后面的页(扇区)，因为前面的页(扇区)存储着程序的代码
*******************************************************************************/
#include "stmflash.h"
 
 
 
#if STM32_FLASH_SIZE<256
#define STM_SECTOR_SIZE 1024 				//字节
#else 
#define STM_SECTOR_SIZE	2048
#endif		 
u16 STMFLASH_BUF[STM_SECTOR_SIZE/2];		//最多是2K字节


/*********************************************************************************************************
*	函 数 名: STMFLASH_ReadHalfWord
*	功能说明: 读取指定地址的半字(16位数据)
*	形    参：faddr:读地址(此地址必须为2的倍数!!)
*	返 回 值: 对应数据.
*********************************************************************************************************/
u16 STMFLASH_ReadHalfWord (u32 faddr)
{
	return (*(vu16*)faddr);		/*将addr强行转化为vu16指针，然后去该指针所真相的地址的值，即得到了addr地址的值*/ 
}


/*********************************************************************************************************
*	函 数 名: STMFLASH_Write_NoCheck
*	功能说明: 不检查的写入
*	形    参：WriteAddr:起始地址; pBuffer:数据指针; NumToWrite:半字(16位)数 
*	返 回 值: 无
*********************************************************************************************************/
#if STM32_FLASH_WREN					//如果使能了写    
void STMFLASH_Write_NoCheck (u32 WriteAddr, u16 *pBuffer, u16 NumToWrite)   
{ 			 		 
	u16 i;
	for (i = 0; i < NumToWrite; i++)
	{
		FLASH_ProgramHalfWord (WriteAddr, pBuffer[i]);
	    WriteAddr += 2;					//地址增加2(以半字进行操作)
	}  
} 


//#if STM32_FLASH_SIZE < 256
//#define STM_SECTOR_SIZE 1024			//字节
//#else 
//#define STM_SECTOR_SIZE	2048
//#endif		 
//u16 STMFLASH_BUF[STM_SECTOR_SIZE / 2];  	//最多是2K字节
/*********************************************************************************************************
*	函 数 名: STMFLASH_Write_NoCheck
*	功能说明: 从指定地址开始写入指定长度的数据
*	形    参WriteAddr:起始地址(此地址必须为2的倍数!!); 
*			  pBuffer:数据指针; 
*			  NumToWrite:半字(16位)数(就是要写入的16位数据的个数.)
*	返 回 值: 无
*********************************************************************************************************/
void STMFLASH_Write (u32 WriteAddr, u16 *pBuffer, u16 NumToWrite)	
{
	u32 SectoePosition;	   												/*扇区地址*/
	u16 SectorOffset;	   												/*扇区内偏移地址(16位字计算)*/
	u16 SectorRemain;	 												/*扇区内剩余地址(16位字计算)*/	   
 	u16 i;    
	u32 OffsetAddress;	   												/*去掉0X08000000后的地址(偏移地址)*/
	
	if (WriteAddr < STM32_FLASH_BASE || (WriteAddr >= (STM32_FLASH_BASE + 1024 * STM32_FLASH_SIZE)))	/*写入的地址范围需要是在0x0800 0000-0x0807 FFFF之间*/ 
	{
		return;															/*非法地址*/
	}
	
	FLASH_Unlock ();													/*解锁*/
	
	OffsetAddress = WriteAddr - STM32_FLASH_BASE;						/*实际偏移地址.*/
	SectoePosition = OffsetAddress / STM_SECTOR_SIZE;					/*扇区地址  0~127 for STM32F103RBT6*/
	SectorOffset = (OffsetAddress % STM_SECTOR_SIZE) / 2;				/*在扇区内的偏移(2个字节为基本单位.)*/
	SectorRemain = (STM_SECTOR_SIZE / 2) - SectorOffset;				/*扇区剩余空间大小 */  

	if (NumToWrite <= SectorRemain)										/*要写入的数据长度小于扇区剩余的存储单元长度*/
	{
		SectorRemain = NumToWrite;										/*不大于该扇区范围*/
	}
	
	while(1) 
	{	
		STMFLASH_Read (SectoePosition * STM_SECTOR_SIZE + STM32_FLASH_BASE, STMFLASH_BUF, STM_SECTOR_SIZE / 2);	//读出整个扇区的内容
		
		for (i = 0; i < SectorRemain; i++)											/*校验数据*/
		{
			if (STMFLASH_BUF[SectorOffset+i] != 0XFFFF) break;						/*写入地址的Flash存储的值是0xFFFF才能重新写入新的数据*/	  
		}
		
		if (i < SectorRemain)														/*需要擦除*/
		{
			FLASH_ErasePage (SectoePosition * STM_SECTOR_SIZE+STM32_FLASH_BASE);	/*擦除整个扇区，擦除以页为单位，因为无法对单个存储单元进行擦除*/
			
			for (i = 0; i < SectorRemain; i++)										/*复制*/
			{
				STMFLASH_BUF[i + SectorOffset] = pBuffer[i];						/*将数据装入缓存*/	  
			}
			STMFLASH_Write_NoCheck (SectoePosition * STM_SECTOR_SIZE + STM32_FLASH_BASE, STMFLASH_BUF, STM_SECTOR_SIZE / 2);	/*写入整个扇区*/  
		}
		else 
		{
			STMFLASH_Write_NoCheck (WriteAddr, pBuffer, SectorRemain);				/*写已经擦除了的,直接写入扇区剩余区间.*/ 	
		}	
		
		if (NumToWrite == SectorRemain) 
		{
			break;																	/*写入结束了,跳出while()循环*/
		}
		else																		/*写入未结束*/
		{
			SectoePosition++;														/*扇区地址增1*/
			SectorOffset = 0;														/*偏移位置归0*/	 
		   	pBuffer += SectorRemain;  												/*指针偏移*/
			WriteAddr += SectorRemain;												/*写地址偏移*/	 			
		   	NumToWrite -= SectorRemain;												/*字节(16位)数递减*/
			
			if (NumToWrite > (STM_SECTOR_SIZE / 2))									/*如果一个扇区容量还不够，就继续写下一个扇区*/
			{
				SectorRemain = STM_SECTOR_SIZE / 2;									/*下一个扇区还是写不完*/
			}
			else
			{
				SectorRemain = NumToWrite;											/*下一个扇区可以写完了*/
			}
		}	 
	}
	
	FLASH_Lock();																	/*上锁*/
}
#endif


/*********************************************************************************************************
*	函 数 名: STMFLASH_Read
*	功能说明: 从指定地址开始读出指定长度的数据
*	形    参ReadAddr:起始地址
*			  pBuffer:数据指针; 
*			  NumToWrite:半字(16位)数(就是要写入的16位数据的个数.)
*	返 回 值: 无
*********************************************************************************************************/
void STMFLASH_Read (u32 ReadAddr, u16 *pBuffer, u16 NumToRead)   	
{
	u16 i;
	for (i = 0; i < NumToRead; i++)
	{
		pBuffer[i] = STMFLASH_ReadHalfWord (ReadAddr);					/*读取2个字节.*/
		ReadAddr += 2;													/*偏移2个字节.*/
	}
}


/*********************************************************************************************************
*	函 数 名: Test_Write
*	功能说明: 从指定地址开始读出指定长度的数据
*	形    参WriteAddr:起始地址
*			  WriteData:要写入的数据 
*	返 回 值: 无
*********************************************************************************************************/
void Test_Write (u32 WriteAddr, u16 WriteData)   	
{
	STMFLASH_Write (WriteAddr, &WriteData,1);				//写入一个字 
}
















