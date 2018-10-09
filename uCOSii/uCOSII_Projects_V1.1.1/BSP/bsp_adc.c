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
 * @function: LED_GPIO_Config
 * @details : ��ʼ��ADC, Ĭ�Ͻ�����ͨ��0~3.
 * @input   : NULL
 * @output  : NULL
 * @return  : NULL
 */   																   
void ADC1_Init(void)
{ 	
	ADC_InitTypeDef   ADC_InitStructure; 
	GPIO_InitTypeDef  GPIO_InitStructure;

	//ʹ��ADC1ͨ��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);

	//����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   

	//PA1 ��Ϊģ��ͨ����������                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;                               //ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	//��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ
	ADC_DeInit(ADC1); 
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;                          //ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;                               //ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;                          //ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;         //ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;                      //ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;                                     //˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);                                         //����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   
	
	
	//ʹ��ָ����ADC1
	ADC_Cmd(ADC1, ENABLE);	
	
	ADC_ResetCalibration(ADC1);                                                 //ʹ�ܸ�λУ׼  
	while(ADC_GetResetCalibrationStatus(ADC1));                                 //�ȴ���λУ׼����
	
	ADC_StartCalibration(ADC1);                                                 //����ADУ׼
	while(ADC_GetCalibrationStatus(ADC1));                                      //�ȴ�У׼����

//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);                                     //ʹ��ָ����ADC1�����ת����������
}


/*
 * @function: Get_ADC1
 * @details : ��ȡADCͨ��������.
 * @input   : 1.ch: ͨ�����.
 * @output  : NULL
 * @return  : ADCͨ��������.
 */ 
uint16_t Get_ADC1(u8 ch)   
{
  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5);           //ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);                                     //ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));                             //�ȴ�ת������

	return ADC_GetConversionValue(ADC1);                                        //�������һ��ADC1�������ת�����
}

