/********************************************************************************
* @file    stmflash.c
* @author  Long 
* @version V1.0
* @date    2015-xx-xx
* @brief   ʹ��flashģ��EEPROM
******************************************************************************
* @attention
*
* ʵ��ƽ̨:���ذ� MINI STM32
* ע��	  :(1)STM32������������FPEC(�����̺Ͳ���������)ģ�鴦��ģ����ģ�����7��32λ�Ĵ���������Ŀ������ֲ�
*		   (2)STM32����ı��ÿ�α���д��16λ��д��32λҪ������д��
*		   (3)STM32��Flash��̵�ʱ��, ����Ҫ����д���ַ��Flash�Ǳ������˵�(�����浥Ԫ��ֵ��0xFFFF)
*		   (4)����������ҳΪ��λ
*		   (5)���浥ԪӦ�þ���ѡ�񿿽��������������ҳ(����)����Ϊǰ���ҳ(����)�洢�ų���Ĵ���
*******************************************************************************/
#include "stmflash.h"
 
 
 
#if STM32_FLASH_SIZE<256
#define STM_SECTOR_SIZE 1024 				//�ֽ�
#else 
#define STM_SECTOR_SIZE	2048
#endif		 
u16 STMFLASH_BUF[STM_SECTOR_SIZE/2];		//�����2K�ֽ�


/*********************************************************************************************************
*	�� �� ��: STMFLASH_ReadHalfWord
*	����˵��: ��ȡָ����ַ�İ���(16λ����)
*	��    �Σ�faddr:����ַ(�˵�ַ����Ϊ2�ı���!!)
*	�� �� ֵ: ��Ӧ����.
*********************************************************************************************************/
u16 STMFLASH_ReadHalfWord (u32 faddr)
{
	return (*(vu16*)faddr);		/*��addrǿ��ת��Ϊvu16ָ�룬Ȼ��ȥ��ָ��������ĵ�ַ��ֵ�����õ���addr��ַ��ֵ*/ 
}


/*********************************************************************************************************
*	�� �� ��: STMFLASH_Write_NoCheck
*	����˵��: ������д��
*	��    �Σ�WriteAddr:��ʼ��ַ; pBuffer:����ָ��; NumToWrite:����(16λ)�� 
*	�� �� ֵ: ��
*********************************************************************************************************/
#if STM32_FLASH_WREN					//���ʹ����д    
void STMFLASH_Write_NoCheck (u32 WriteAddr, u16 *pBuffer, u16 NumToWrite)   
{ 			 		 
	u16 i;
	for (i = 0; i < NumToWrite; i++)
	{
		FLASH_ProgramHalfWord (WriteAddr, pBuffer[i]);
	    WriteAddr += 2;					//��ַ����2(�԰��ֽ��в���)
	}  
} 


//#if STM32_FLASH_SIZE < 256
//#define STM_SECTOR_SIZE 1024			//�ֽ�
//#else 
//#define STM_SECTOR_SIZE	2048
//#endif		 
//u16 STMFLASH_BUF[STM_SECTOR_SIZE / 2];  	//�����2K�ֽ�
/*********************************************************************************************************
*	�� �� ��: STMFLASH_Write_NoCheck
*	����˵��: ��ָ����ַ��ʼд��ָ�����ȵ�����
*	��    �ΣWWriteAddr:��ʼ��ַ(�˵�ַ����Ϊ2�ı���!!); 
*			  pBuffer:����ָ��; 
*			  NumToWrite:����(16λ)��(����Ҫд���16λ���ݵĸ���.)
*	�� �� ֵ: ��
*********************************************************************************************************/
void STMFLASH_Write (u32 WriteAddr, u16 *pBuffer, u16 NumToWrite)	
{
	u32 SectoePosition;	   												/*������ַ*/
	u16 SectorOffset;	   												/*������ƫ�Ƶ�ַ(16λ�ּ���)*/
	u16 SectorRemain;	 												/*������ʣ���ַ(16λ�ּ���)*/	   
 	u16 i;    
	u32 OffsetAddress;	   												/*ȥ��0X08000000��ĵ�ַ(ƫ�Ƶ�ַ)*/
	
	if (WriteAddr < STM32_FLASH_BASE || (WriteAddr >= (STM32_FLASH_BASE + 1024 * STM32_FLASH_SIZE)))	/*д��ĵ�ַ��Χ��Ҫ����0x0800 0000-0x0807 FFFF֮��*/ 
	{
		return;															/*�Ƿ���ַ*/
	}
	
	FLASH_Unlock ();													/*����*/
	
	OffsetAddress = WriteAddr - STM32_FLASH_BASE;						/*ʵ��ƫ�Ƶ�ַ.*/
	SectoePosition = OffsetAddress / STM_SECTOR_SIZE;					/*������ַ  0~127 for STM32F103RBT6*/
	SectorOffset = (OffsetAddress % STM_SECTOR_SIZE) / 2;				/*�������ڵ�ƫ��(2���ֽ�Ϊ������λ.)*/
	SectorRemain = (STM_SECTOR_SIZE / 2) - SectorOffset;				/*����ʣ��ռ��С */  

	if (NumToWrite <= SectorRemain)										/*Ҫд������ݳ���С������ʣ��Ĵ洢��Ԫ����*/
	{
		SectorRemain = NumToWrite;										/*�����ڸ�������Χ*/
	}
	
	while(1) 
	{	
		STMFLASH_Read (SectoePosition * STM_SECTOR_SIZE + STM32_FLASH_BASE, STMFLASH_BUF, STM_SECTOR_SIZE / 2);	//������������������
		
		for (i = 0; i < SectorRemain; i++)											/*У������*/
		{
			if (STMFLASH_BUF[SectorOffset+i] != 0XFFFF) break;						/*д���ַ��Flash�洢��ֵ��0xFFFF��������д���µ�����*/	  
		}
		
		if (i < SectorRemain)														/*��Ҫ����*/
		{
			FLASH_ErasePage (SectoePosition * STM_SECTOR_SIZE+STM32_FLASH_BASE);	/*��������������������ҳΪ��λ����Ϊ�޷��Ե����洢��Ԫ���в���*/
			
			for (i = 0; i < SectorRemain; i++)										/*����*/
			{
				STMFLASH_BUF[i + SectorOffset] = pBuffer[i];						/*������װ�뻺��*/	  
			}
			STMFLASH_Write_NoCheck (SectoePosition * STM_SECTOR_SIZE + STM32_FLASH_BASE, STMFLASH_BUF, STM_SECTOR_SIZE / 2);	/*д����������*/  
		}
		else 
		{
			STMFLASH_Write_NoCheck (WriteAddr, pBuffer, SectorRemain);				/*д�Ѿ������˵�,ֱ��д������ʣ������.*/ 	
		}	
		
		if (NumToWrite == SectorRemain) 
		{
			break;																	/*д�������,����while()ѭ��*/
		}
		else																		/*д��δ����*/
		{
			SectoePosition++;														/*������ַ��1*/
			SectorOffset = 0;														/*ƫ��λ�ù�0*/	 
		   	pBuffer += SectorRemain;  												/*ָ��ƫ��*/
			WriteAddr += SectorRemain;												/*д��ַƫ��*/	 			
		   	NumToWrite -= SectorRemain;												/*�ֽ�(16λ)���ݼ�*/
			
			if (NumToWrite > (STM_SECTOR_SIZE / 2))									/*���һ�������������������ͼ���д��һ������*/
			{
				SectorRemain = STM_SECTOR_SIZE / 2;									/*��һ����������д����*/
			}
			else
			{
				SectorRemain = NumToWrite;											/*��һ����������д����*/
			}
		}	 
	}
	
	FLASH_Lock();																	/*����*/
}
#endif


/*********************************************************************************************************
*	�� �� ��: STMFLASH_Read
*	����˵��: ��ָ����ַ��ʼ����ָ�����ȵ�����
*	��    �ΣWReadAddr:��ʼ��ַ
*			  pBuffer:����ָ��; 
*			  NumToWrite:����(16λ)��(����Ҫд���16λ���ݵĸ���.)
*	�� �� ֵ: ��
*********************************************************************************************************/
void STMFLASH_Read (u32 ReadAddr, u16 *pBuffer, u16 NumToRead)   	
{
	u16 i;
	for (i = 0; i < NumToRead; i++)
	{
		pBuffer[i] = STMFLASH_ReadHalfWord (ReadAddr);					/*��ȡ2���ֽ�.*/
		ReadAddr += 2;													/*ƫ��2���ֽ�.*/
	}
}


/*********************************************************************************************************
*	�� �� ��: Test_Write
*	����˵��: ��ָ����ַ��ʼ����ָ�����ȵ�����
*	��    �ΣWWriteAddr:��ʼ��ַ
*			  WriteData:Ҫд������� 
*	�� �� ֵ: ��
*********************************************************************************************************/
void Test_Write (u32 WriteAddr, u16 WriteData)   	
{
	STMFLASH_Write (WriteAddr, &WriteData,1);				//д��һ���� 
}
















