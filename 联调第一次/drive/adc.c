#include "stm32f0xx.h"
#include "usart.h"
#include "gpio.h"
#include "adc.h"

unsigned char adc_sig = 0;  //读ADC标志位

//***************************************************************************
// 函数名称    : void ADC_Configuration(void)
// 功能描述    : ADC参数初始化定义函数.
// 输入        : None
// 输出        : None
// 返回        : None
// 备注				 : 开启PB0(通道8)作为AD转换的通道
//***************************************************************************
void ADC_Configuration(void)
{
 // unsigned short adc_data;
  
  ADC_InitTypeDef ADC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
   /* ADC1 Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	/* Configure ADC Channel8 as analog input */
	//
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
 /* ADCs DeInit */  
  ADC_DeInit(ADC1);
  
  /* Initialize ADC structure */
  ADC_StructInit(&ADC_InitStructure);
  
  /* Configure the ADC1 in continous mode withe a resolutuion equal to 12 bits  */
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;		//ADC12位分辨率转换
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 				//连续转换使能
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//不触发
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;		//数据右对齐
  ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Backward;//数据被覆盖;
  ADC_Init(ADC1, &ADC_InitStructure); 
  
  /* Convert the ADC1 Channel 8 with 239.5 Cycles as sampling time */ 
  ADC_ChannelConfig(ADC1, ADC_Channel_8 , ADC_SampleTime_55_5Cycles);//ADC_SampleTime_239_5Cycles);   

  /* ADC Calibration */
  ADC_GetCalibrationFactor(ADC1);
  
  /* Enable ADCperipheral[PerIdx] */
  ADC_Cmd(ADC1, ENABLE);     
	ADC_StartOfConversion(ADC1);
  
  /* 等待ADC使能 */
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADEN)); 
  

}






