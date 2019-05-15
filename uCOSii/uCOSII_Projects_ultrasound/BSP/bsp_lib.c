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
 * @details : 普通延时函数。8MHz外部晶振，倍频至72MHz, nop耗时1/72us。
			  参数取值1, 延时1.39us; 
			  参数取值10, 延时11.14us.              
			  参数取值100, 延时108.64us; 
			  参数取值1000, 延时1.08502ms.
 * @input   : time: 延时时间。
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
