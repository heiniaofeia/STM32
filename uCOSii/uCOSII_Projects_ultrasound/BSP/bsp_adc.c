/*
 * @file   : bsp_adc.c
 * @author : DragonFly
 * @version: V1.0.0
 * @date   : 2016.12.13
 * @history:
 * @details: adc source file
 */
#include "bsp_adc.h"



/*---------------------------------------------------------------------------
                                Variable definition
----------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
                                Function definition
----------------------------------------------------------------------------*/
/*
 * @function: ADC1Config
 * @details : 配置ADC1.
 * @input   : NULL
 * @output  : NULL
 * @return  : NULL
 */   																   
void ADC1Config(void)
{ 	
	ADC_InitTypeDef   ADC_InitStructure; 
	GPIO_InitTypeDef  GPIO_InitStructure;

	//使能ADC1通道时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);


	//PA1 作为模拟通道输入引脚                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;                               //模拟输入引脚
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	
	//复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值
	ADC_DeInit(ADC1); 
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;                          //ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;                                //DISABLE: 模数转换工作在单通道模式; ENABLE: 模数转换工作在多通道模式.
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;                         //模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;         //转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;                      //ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;                                     //顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);                                         //根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   
	
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);                                           //设置ADC分频因子8, 得到ADC1工作频率: 72M/8=MHz. 注意: ADC最大时间不能超过14M.
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	
	ADC_Cmd(ADC1, ENABLE);	                                                    //使能指定的ADC1.
	
	ADC_ResetCalibration(ADC1);                                                 //使能复位校准  
	while(ADC_GetResetCalibrationStatus(ADC1));                                 //等待复位校准结束
	
	ADC_StartCalibration(ADC1);                                                 //开启AD校准
	while(ADC_GetCalibrationStatus(ADC1));                                      //等待校准结束

	ADC_SoftwareStartConvCmd(ADC1, DISABLE);                                    //使能指定的ADC1的软件转换启动功能, 由于没有采用外部触发，所以使用软件触发ADC转换.
}


/*
 * @function: Get_ADC1
 * @details : 获取ADC通道的数据.
 * @input   : 1.ch: 通道编号.
 * @output  : NULL
 * @return  : ADC通道的数据.
 */ 
uint16_t Get_ADC1(u8 ch)   
{
  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_55Cycles5);            //ADC1,ADC通道,采样时间为239.5周期	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);                                     //使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));                             //等待转换结束

	return ADC_GetConversionValue(ADC1);                                        //返回最近一次ADC1规则组的转换结果
}


/*
 * @function: ADC1Init
 * @details : 初始化ADC1.
 * @input   : NULL
 * @output  : NULL
 * @return  : NULL
 */ 
void ADC1Init(void)
{
	ADC1Config();
}
