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
		{    
		}
}

