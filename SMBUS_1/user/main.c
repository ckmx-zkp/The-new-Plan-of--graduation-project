/******************** (C) COPYRIGHT 2015 毕业设计 ********************
 * 文件名  ：main
 * 描述    ：         
 * 描述    ：ADC单通道采样
 * 作者    ：张鲲鹏
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
		//printf(" ADC已初始化\n");
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

