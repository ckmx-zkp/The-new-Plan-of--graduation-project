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
		TIMER2_Config();
		//TIMER2_Config();
		//ADC_Configuration();
		//printf(" ADC�ѳ�ʼ��\n");
		//TIMER3_Config();
		//Delay_ms(2000);
		//SMBus_Init();
		//printf("SMBus Success\n");
		while(1)
		{
				/*SM_Temp = SMBus_ReadTemp();
				printf("%f\n", SM_Temp);
				Delay_ms(500);*/
		}
}
