/******************** (C) COPYRIGHT 2015 ��ҵ��� ********************
 * �ļ���  ��main
 * ����    ��         
 * ����    ��ADC��ͨ������
 * ����    ��������
**********************************************************************/

#include "stm32f0xx.h"
#include "usart.h"
#include "systick.h"
#include "adc.h"
#include "timer.h"


int main(void)
{ 
		
		SystemInit();  
		Systick_Init();
		USART_Configuration();
		ADC_Configuration();
		printf(" ADC�ѳ�ʼ��\n");
		TIMER_Config();
		//printf("��ʱ����ʼ���ɹ�\n");
		
		//printf(" ADC�ѳ�ʼ��\n");
		while (1)
		{    
				
//				Value_temp = ADC_GetConversionValue(ADC1);
//				count_1 = (Value_temp * 3300)/4096;
//				printf("%d\n",count_1);
//				//ADC_Value[count_1] = Value_temp;
//				//USART1_SendString(ADC_Value);
//				Delay_ms(500);
		}
}

