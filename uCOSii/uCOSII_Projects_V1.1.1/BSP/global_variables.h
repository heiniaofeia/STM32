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
#define                      OFF                           0          
#define                      ON                            1 
	 
#define                      FALSE                         0          
#define                      TRUE                          1 	
	 

/*
 * @details: PWM。
 */
#define                      PWM_FREQ_MIN                  0          
#define                      PWM_FREQ_MAX                  1000 

	 
/*---------------------------------------------------------------------------
                                Variable type
----------------------------------------------------------------------------*/
/*
 * @details: 栈数据。
 */
//struct tagStackCheck
//{
//	uint8_t                  Error;
//	OS_STK_DATA              StkD;
//};

/*
 * @details: ADC。
 */
struct tagADC1
{
	uint8_t                  DispBuf1[8];
	uint8_t                  DispBuf2[8];
};


/*
 * @details: 按键。
 */
struct tagMatrixkey
{
	uint8_t                  Value;
	uint8_t                  KeySingleDeal;	
};



/*
 * @details: 按键。
 */
struct tagMicrowaves
{
	uint8_t                  CtlSwitch;
//	uint8_t                  MicrStage;
	
	uint8_t                  UpdataFreqFlg;
	
	uint16_t                 Freq;
	uint16_t                 FreqMin;
	uint16_t                 FreqMax;
	
	uint16_t                 FeedbackVoltage;
	uint8_t                  DispBuf1[8];
};


/*---------------------------------------------------------------------------
                                Variable declaration
----------------------------------------------------------------------------*/
extern  struct tagADC1  ADC1Dat;
extern  struct tagMatrixkey  Matrixkey;
extern  struct tagMicrowaves  Microwaves;


/*---------------------------------------------------------------------------
                                Function declaration
----------------------------------------------------------------------------*/


#ifdef __cplusplus
}
#endif



#endif 

  
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
