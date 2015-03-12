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
  
  /* 等待ADC使能 */
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADEN)); 
  
  /* ADC1 regular Software Start Conv */ 
//  ADC_StartOfConversion(ADC1); 
//  
//   /* Test EOC flag */
//  while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
//    
//    /* Get ADC1 converted data */
//  adc_data =ADC_GetConversionValue(ADC1);
//  uart2_trx[uart2_rx++] = adc_data >> 8 ;
//  uart2_trx[uart2_rx++] = adc_data  ;
}


//*****************************************************************************
// 函数名称    : void Read_ADC(void)
// 功能描述    : 读采集到的ADC数据，并把采集到的数据通过串口发送出去.
// 输入        : None
// 输出        : None
// 返回        : None
//****************************************************************************
//void Read_ADC(void)
//{
//  unsigned short result=0;
//  unsigned short id;
//  unsigned char a,b,c,d,i;
//  
//  for(i=0;i<8;i++)
//  {
//    ADC_StartOfConversion(ADC1);   //启动ADC1转换
//    do
//     {
//       id =  ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC);//读取转换标志
//     }while(!id);    //等待，只到转换完成
//  
//    result += ADC_GetConversionValue(ADC1);
//  }
//  result = result>>3;   //取8次采样的平均值
//    
//  result = (unsigned int)(((unsigned long)result)*3300>>12); //把采集到的数值转换成电压数据
//   a = result/1000;
//   b = (result - a*1000)/100;
//   c = (result - a*1000 - b*100)/10;
//   d = result - a*1000 - b*100 - c*10;
//                        
// // send_string("ADC Value = V");
//  Uart2_PutChar(0X56); // "V"
//  Uart2_PutChar(0X3D); // "="
//  
//  Uart2_PutChar(a+48);
//  Uart2_PutChar(0x2e);  //“.”
//  Uart2_PutChar(b+48);
//  Uart2_PutChar(c+48);
//  Uart2_PutChar(d+48);
//  Uart2_PutChar(0X56); //"V"
//  Uart2_PutChar(0XD);
//  Uart2_PutChar(0XA);
//}




