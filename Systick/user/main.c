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


int main(void)
{ 
		
		SystemInit();  
		Systick_Init();
		USART_Configuration();
		ADC_Configuration();
		printf(" ADC已初始化\n");
		TIMER_Config();
		//printf("定时器初始化成功\n");
		
		//printf(" ADC已初始化\n");
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

