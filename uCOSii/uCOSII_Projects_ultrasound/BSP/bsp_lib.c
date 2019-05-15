/*
 * @file   : bsp_lib.c
 * @author : long
 * @version: V1.0.0
 * @date   : 2016.12.13
 * @history:
 * @details: lib source file
 */
#include "bsp_lib.h"  




/*---------------------------------------------------------------------------
                                Variable definition
----------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
                                Function definition
----------------------------------------------------------------------------*/
/*
 * @function: RoughDelay_us
 * @details : ��ͨ��ʱ������8MHz�ⲿ���񣬱�Ƶ��72MHz, nop��ʱ1/72us��
			  ����ȡֵ1, ��ʱ1.39us; 
			  ����ȡֵ10, ��ʱ11.14us.              
			  ����ȡֵ100, ��ʱ108.64us; 
			  ����ȡֵ1000, ��ʱ1.08502ms.
 * @input   : time: ��ʱʱ�䡣
 * @output  : NULL
 * @return  : NULL
 */
void RoughDelay_us(uint32_t time)
{
	uint32_t i = 0;
	
	
	for(i = 0; i < time; i++)
	{
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	}
}
