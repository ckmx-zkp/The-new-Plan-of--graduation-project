#include "usart.h"
#include "usart2.h"
#include <stdarg.h>
#include <stdio.h>

/*
 //加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
////定义_sys_exit()以避免使用半主机模式    
//_sys_exit(int x) 
//{ 
//	x = x; 
//} 
//重定义fputc函数 
int fputc2(int ch, FILE *f)
{      
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET); 
    USART_SendData(USART2,(uint8_t)ch);   
	return ch;
}
#endif  
*/

void USART2_Configuration(void)//串口初始化函数
{  

			GPIO_InitTypeDef  GPIO_InitStructure;
			USART_InitTypeDef USART_InitStructure;
			NVIC_InitTypeDef NVIC_InitStructure;
							
			RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA, ENABLE);
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE );
							
			GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_1);
			GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_1);        
			/*
			*  USART2_TX -> PA2 , USART2_RX ->        PA3
			*/                                
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;                 
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
			GPIO_Init(GPIOA, &GPIO_InitStructure);        
			
			USART_InitStructure.USART_BaudRate = 9600;//设置串口波特率
			USART_InitStructure.USART_WordLength = USART_WordLength_8b;//设置数据位
			USART_InitStructure.USART_StopBits = USART_StopBits_1;//设置停止位
			USART_InitStructure.USART_Parity = USART_Parity_No;//设置效验位
			USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//设置流控制
			USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//设置工作模式
			USART_Init(USART2, &USART_InitStructure); //配置入结构体

			

			/* TIM3 clock enable */
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

			/*  TIM3 中断嵌套设计*/
			NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);
	
	
	
			USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启中断
			USART_Cmd(USART2, ENABLE);//使能串口1

	}			

		
void USART2_IRQHandler(void)                	//串口1中断服务程序
{
	unsigned char Res;

	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		Res =USART_ReceiveData(USART2);//(USART1->DR);	//读取接收到的数据
		if(Res != NULL)
		{
				USART_SendData(USART1, Res);
		}
		USART2->TDR= Res;
     } 

} 
		
void UART2_send_byte(uint8_t byte) //发送1字节数据
{
 while(!((USART2->ISR)&(1<<7)));
 USART2->TDR=byte;	
}		

void UART2_Send(uint8_t *Buffer, uint32_t Length)
{
	while(Length != 0)
	{
		while(!((USART2->ISR)&(1<<7)));//等待发送完
		USART2->TDR= *Buffer;
		Buffer++;
		Length--;
	}
}

uint8_t UART2_Recive(void)
{	
	while(!(USART2->ISR & (1<<5)));//等待接收到数据
	return(USART2->RDR);			 //读出数据
}

//发送字符串
void USART2_SendString(unsigned char const *buf)
{
		
		while(*buf)
		{				    
			USART_SendData(USART2,*buf++);		
			while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET); 
      		USART_ClearFlag(USART2,USART_FLAG_TXE);
            
		}	
}


	
