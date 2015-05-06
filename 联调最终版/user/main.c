/******************** (C) COPYRIGHT 2015 毕业设计 ********************
 * 文件名  ：main
 * 描述    ：         
 * 描述    ：ADC单通道采样
 * 作者    ：张鲲鹏
**********************************************************************/

#include "stm32f0xx.h"
#include "usart.h"
#include "usart2.h"
#include "systick.h"
#include "adc.h"
#include "timer.h"
#include "mlx90614.h"

#define  SW_RESET()	       NVIC_SystemReset()  

float SM_Temp[10] = {0};
float SM_temp = 0;
uint16_t USART_Tem = 0;
extern uint8_t USART_RX_BUF[20];  
extern uint16_t USART_RX_STA;
uint8_t sta_smbus = 0;
uint8_t sta_init = 0;
uint8_t sta_reset = 0;
uint8_t sta_cnt = 0;
uint8_t i = 0;

int main(void)
{ 
		
		SystemInit(); 

		Systick_Init();
		USART_Configuration();
//		ADC_Configuration();
		SMBus_Init();
		printf("\r\nUSART1 is ready\r\n");
		
//
	

//printf(" ADC已初始化\n");
//		TIMER_Config();
//		SMBus_Init();
//		printf("SMBus Success\n");
		while(1)
		{
			
			if(USART_RX_BUF[0]=='H')
			{
					if(USART_RX_BUF[1]=='T')
					{
							sta_smbus = 1;
							TIM_DeInit(TIM3);
							USART_RX_STA = 0;
							USART_RX_BUF[0] = '0';
							sta_reset += 1;

					}
					if(USART_RX_BUF[1]=='R')
					{
							sta_smbus = 0;
							sta_init = 0;
							printf("pulse\n");
							ADC_Configuration();
							TIMER_Config();
							USART_RX_STA = 0;
							USART_RX_BUF[0] = '0';
							sta_reset += 1;
					}	
			}
			else if(sta_smbus == 1)
			{
					printf("SMBus Success\n");
//					SM_temp = SMBus_ReadTemp();
//					printf("%f\n", SM_temp);
					for(i = 0; i < 5; i ++)
					{	
							SM_Temp[i] = SMBus_ReadTemp();	
							SM_temp += SM_Temp[i];
							sta_cnt ++;
							if(sta_cnt == 5)
							{
									printf("%f\r\n", (SM_temp / 5));
									SW_RESET();
							}
					}
					sta_smbus = 0;

			}
			else if(sta_init == 1)
			{
					for(i = 0; i < 10; i ++)
					{	
							SM_Temp[i] = SMBus_ReadTemp();	
							SM_temp += SM_Temp[i];
					}

					Delay_ms(500);	
					sta_cnt ++;
					if(sta_cnt == 10)
					{
							printf("%f\r\n",SM_temp);
							SW_RESET();
					}
			}
			else if(sta_reset == 3 || USART_RX_BUF[0] == 'R')
			{
					sta_init = 0;
					USART_RX_STA = 0;
					USART_RX_BUF[0] = '0';
					SW_RESET();
			}
		
//				SM_Temp = SMBus_ReadTemp();
//				printf("%f\n", SM_Temp);
//				printf("USART1\r\n");
//				Delay_ms(500);
//				USART2_SendString("USART2\r\n");
//				Delay_ms(500);
		}
		
}

