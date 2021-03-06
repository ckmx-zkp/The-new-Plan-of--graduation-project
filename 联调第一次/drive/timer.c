#include "timer.h"
#include "adc.h"
#include "usart.h"
#include "systick.h"

//储存AD的变量定义
uint16_t Value_temp;
uint16_t count_1 = 0;
uint16_t count_2 = 0;
uint16_t ADC_Test[2560] = {0};


//***************************************************************************
// 函数名称    : void delay_ms(uint16_t time)
// 功能描述    : 一个短延时函数
// 输入        : None
// 输出        : None
// 返回        : None
// 备注				 : 测试时使用
//***************************************************************************
void delay_ms(uint16_t time)
{
    uint16_t i, j, k;
    for (i = 0; i < 80; i++)
    {
				for(k = 0; k < 125; k++)
						
						for (j = 0; j < time; j++);
    }
}

//***************************************************************************
// 函数名称    : void delay_ms(uint16_t time)
// 功能描述    : 一个短延时函数
// 输入        : None
// 输出        : None
// 返回        : None
// 备注				 : 测试时使用
//***************************************************************************
void TIMER_Config(void)
{

    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
     /* TIM3 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //使能定时器3
    /* 计算预分频值 */
    //PrescalerValue = (uint16_t) (SystemCoreClock  / 1000) - 1;//1KHz,1ms

    /* Time 定时器基础设置 */
    TIM_TimeBaseStructure.TIM_Period = 124;
    TIM_TimeBaseStructure.TIM_Prescaler = 1499;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    /* 预分频器配置 */
    //TIM_PrescalerConfig(TIM3, PrescalerValue, TIM_PSCReloadMode_Immediate);
    
    /*  设定中断优先级*/
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
		TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);/* TIM 中断使能 */
		TIM_Cmd(TIM3, ENABLE);/* TIM3 使能 */   
    

    

	
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
		if(count_2 == 2560)
		{
				TIM_Cmd(TIM3, DISABLE);
				//printf("采集结束，定时器关闭，接下来显示AD结果\n");
				//Delay_ms(100);
				for(count_2 = 0; count_2 < 2560; count_2++)
				{
						printf("%d\n",ADC_Test[count_2]);
						delay_ms(10);
						//Delay_ms(500);
				}
				
		}

  }

}















