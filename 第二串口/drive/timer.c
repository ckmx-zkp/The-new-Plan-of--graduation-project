#include "timer.h"
#include "adc.h"
#include "usart.h"
#include "systick.h"

//����AD�ı�������
uint16_t Value_temp;
uint16_t count_1 = 0;
uint16_t count_2 = 0;
uint16_t ADC_Test[50] = {0};

void TIMER_Config(void)
{

    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
     /* TIM3 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʹ�ܶ�ʱ��3
    /* ����Ԥ��Ƶֵ */
    //PrescalerValue = (uint16_t) (SystemCoreClock  / 1000) - 1;//1KHz,1ms

    /* Time ��ʱ���������� */
    TIM_TimeBaseStructure.TIM_Period = 3750;
    TIM_TimeBaseStructure.TIM_Prescaler = 1000;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    /* Ԥ��Ƶ������ */
    //TIM_PrescalerConfig(TIM3, PrescalerValue, TIM_PSCReloadMode_Immediate);
    
    /*  �趨�ж����ȼ�*/
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
		TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);/* TIM �ж�ʹ�� */
		TIM_Cmd(TIM3, ENABLE);/* TIM3 ʹ�� */   
    

    

	
}

void TIM3_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		ADC_StartOfConversion(ADC1); 
		//printf("Start ADC\n");
		Value_temp = ADC_GetConversionValue(ADC1);
		count_1 = (Value_temp * 3300)/4096;
		ADC_Test[count_2] = count_1;
		count_2++;
		if(count_2 == 50)
		{
				
				printf("�ɼ���������ʱ���رգ���������ʾAD���\n");
				//Delay_ms(100);
				for(count_2 = 0; count_2 < 50; count_2++)
				{
						printf("The value is %d\n",ADC_Test[count_2]);
						//Delay_ms(500);
				}
				TIM_Cmd(TIM3, DISABLE);
		}

  }

}















