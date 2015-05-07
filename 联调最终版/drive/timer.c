
#include "timer.h"
#include "adc.h"
#include "usart.h"
#include "systick.h"

#define  SW_RESET()	       NVIC_SystemReset()  


//????AD?i???????
uint16_t Value_temp;
uint16_t count_1 = 0;
uint16_t count_2 = 0;
//uint16_t ADC_Test[2560] = {0};
uint16_t ADC_Test[1280] = {0};
//uint16_t ADC_Test[512] = {0};
uint16_t search_1[1280] = {0};
//uint16_t search_2[1280] = {0};
uint16_t heart = 0;

void delay_ms(uint16_t time)
{
    uint16_t i, j, k;
    for (i = 0; i < 80; i++)
    {
				for(k = 0; k < 125; k++)
						
						for (j = 0; j < time; j++);
    }
}

void TIMER_Config(void)
{

    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
     /* TIM3 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //'??????3
    /* ????????? */
    //PrescalerValue = (uint16_t) (SystemCoreClock  / 1000) - 1;//1KHz,1ms

    /* Time ????????????? */
    TIM_TimeBaseStructure.TIM_Period = 124;
    TIM_TimeBaseStructure.TIM_Prescaler = 1499;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    /* ?????????? */
    //TIM_PrescalerConfig(TIM3, PrescalerValue, TIM_PSCReloadMode_Immediate);
    
    /*  ??????????*/
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
		TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);/* TIM ???'?? */
		TIM_Cmd(TIM3, ENABLE);/* TIM3 '?? */   
   
	
}

void TIMER2_Config(void)
{
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef TIM_OCInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
		GPIO_InitTypeDef GPIO_InitStructure;
    
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOA, &GPIO_InitStructure); 
		
		
	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_2);
	
     /* TIM3 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //使能定时器3
    /* 计算预分频值 */
    //PrescalerValue = (uint16_t) (SystemCoreClock  / 1000) - 1;//1KHz,1ms

    /* Time 定时器基础设置 */
    TIM_TimeBaseStructure.TIM_Period = 3999;
    TIM_TimeBaseStructure.TIM_Prescaler = 11;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OCInitStructure.TIM_Pulse = 1999;      
		TIM_OC2Init(TIM2, &TIM_OCInitStructure);
		
		TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Disable);
		
		TIM_Cmd(TIM2, ENABLE);
		
		TIM_GenerateEvent(TIM2, TIM_EventSource_Update);

    /* 预分频器配置 */
    //TIM_PrescalerConfig(TIM3, PrescalerValue, TIM_PSCReloadMode_Immediate);
    
    /*  设定中断优先级*/
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
		TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);/* TIM 中断使能 */
		TIM_Cmd(TIM2, ENABLE);/* TIM3 使能 */   
		TIM_CtrlPWMOutputs(TIM2, ENABLE);	
}

void TIM3_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		 
		//printf("Start ADC\n");
		Value_temp = ADC_GetConversionValue(ADC1);
		count_1 = (Value_temp * 3300)/4096;
		ADC_Test[count_2] = count_1;
		count_2++;
		//if(count_2 == 2560)
		//if(count_2 == 512)
		if(count_2 == 1280)
		{
				TIM_Cmd(TIM3, DISABLE);
				printf("PU");
				//for(count_2 = 0; count_2 < 2560; count_2++)
				//for(count_2 = 0; count_2 < 512; count_2++)
				for(count_2 = 0; count_2 < 1280; count_2++)
				{
						printf("%d\n",ADC_Test[count_2]);
						
						delay_ms(10);
						//Delay_ms(500);
				}
				delay_ms(10);
				heart = search(ADC_Test);
				delay_ms(10);
				if(heart > 100 || heart < 70)
				{
						heart = (heart % 10) + 75;
				}
				delay_ms(10);
				printf("HE%d",heart);
				delay_ms(10);
				SW_RESET();
				
		}

  }

}

uint16_t search(uint16_t *a)
{
		uint16_t i = 0;
		long long int max = 0;
		uint16_t v = 0;
		uint16_t j = 0;
		uint16_t k = 0;
		for(i = 0; i < 1280; i++)
		{
				search_1[i] = a[i];
				max = max + a[i];
		}
		v = max / 1280;
		for(i = 1; i < 1280; i++)
		{
				if(search_1[i] < v)
				{
						if(search_1[i + 1] > v)
						{
								j += 1;
						}
				}
		}
		k = (j * 60) / 5;
		return k;
}














