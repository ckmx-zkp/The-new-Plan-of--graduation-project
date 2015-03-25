#include "stm32f0xx.h"
#include "usart.h"
#include "gpio.h"
#include "adc.h"

unsigned char adc_sig = 0;  //��ADC��־λ

//***************************************************************************
// ��������    : void ADC_Configuration(void)
// ��������    : ADC������ʼ�����庯��.
// ����        : None
// ���        : None
// ����        : None
// ��ע				 : ����PB0(ͨ��8)��ΪADת����ͨ��
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
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;		//ADC12λ�ֱ���ת��
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 				//����ת��ʹ��
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//������
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;		//�����Ҷ���
  ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Backward;//���ݱ�����;
  ADC_Init(ADC1, &ADC_InitStructure); 
  
  /* Convert the ADC1 Channel 8 with 239.5 Cycles as sampling time */ 
  ADC_ChannelConfig(ADC1, ADC_Channel_8 , ADC_SampleTime_55_5Cycles);//ADC_SampleTime_239_5Cycles);   

  /* ADC Calibration */
  ADC_GetCalibrationFactor(ADC1);
  
  /* Enable ADCperipheral[PerIdx] */
  ADC_Cmd(ADC1, ENABLE);     
	ADC_StartOfConversion(ADC1);
  
  /* �ȴ�ADCʹ�� */
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADEN)); 
  

}






