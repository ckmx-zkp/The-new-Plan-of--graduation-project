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
#include "mlx90614.h"

float SM_Temp = 0;


int main(void)
{ 
		
		SystemInit();  
		Systick_Init();
		USART_Configuration();
		//ADC_Configuration();
		//printf(" ADC�ѳ�ʼ��\n");
		//TIMER_Config();
		SMBus_Init();
		printf("SMBus Success\n");
		while(1)
		{
				SM_Temp = SMBus_ReadTemp();
				printf("%f\n", SM_Temp);
				Delay_ms(500);
		}
}

