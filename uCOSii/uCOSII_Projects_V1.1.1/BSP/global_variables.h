/*
 * @file   : PvGridInv_Variables.h
 * @author : long
 * @version: V1.0.0
 * @date   : 2016.12.13
 * @history:
 * @details: PvGridInv_Variables head file
 */
#ifndef __GLOBAL_VARIABLES_H__
#define __GLOBAL_VARIABLES_H__


#ifdef __cplusplus
 extern "C" {
#endif 

#include "ucos_ii.h"
#include "stm32f10x.h" 

 

/*---------------------------------------------------------------------------
                                Macro definition
----------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
                                Variable type
----------------------------------------------------------------------------*/
/*
 * @details: Õ»Êý¾Ý¡£
 */
//struct tagStackCheck
//{
//	uint8_t                  Error;
//	OS_STK_DATA              StkD;
//};

/*
 * @details: ADC¡£
 */
struct tagADC1
{
	uint8_t                  DispBuf[16];
};



/*---------------------------------------------------------------------------
                                Variable declaration
----------------------------------------------------------------------------*/
extern  struct tagADC1  ADC1Dat;


/*---------------------------------------------------------------------------
                                Function declaration
----------------------------------------------------------------------------*/


#ifdef __cplusplus
}
#endif



#endif 

  
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
