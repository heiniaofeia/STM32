/*
 * @file   : Matrixkey.h
 * @author : DragonFly
 * @version: V1.0.0
 * @date   : 2016.12.13
 * @history:
 * @details: Matrixkey head file
 */
#ifndef __MATRIXKEY_H__
#define __MATRIXKEY_H__


#include "stm32f10x.h"
#include "global_variables.h"




/*---------------------------------------------------------------------------
                                Macro definition
----------------------------------------------------------------------------*/
#define KEY_PORT GPIOE


/*---------------------------------------------------------------------------
                                Variable type
----------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                                Variable declaration
----------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
                                Function declaration
----------------------------------------------------------------------------*/
void MatrixkeyInit(void);
uint8_t GetKeyValue(void);


#endif

