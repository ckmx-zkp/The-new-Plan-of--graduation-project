#include "usart.h"
//#include "usart2.h"
#include "adc.h"
#include "time.h"
#include "mlx90614.h"
#include <stdarg.h>
#include <stdio.h>

#define 	ADC_Con 0x20
#define 	TEM_con 0x30
#define  	SW_RESET()	       NVIC_SystemReset()  
extern uint16_t USART_Tem;

uint8_t USART_RX_BUF[20];     //接收缓冲,最大USART_REC_LEN个字节.
uint16_t USART_RX_STA=0;       //接收状态标记	  


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
int fputc(int ch, FILE *f)
{      
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET); 
    USART_SendData(USART1,(uint8_t)ch);   
	return ch;
}
#endif  

//uint16_t BLE_USARTControl(unsigned char Dat)
//{
//		if(Dat == 0x01)
//			return ADC_Con;
//		else if(Dat == 0x02)
//			return TEM_con;
//		
//			
//}


void USART_Configuration(void)//串口初始化函数
{  

			GPIO_InitTypeDef  GPIO_InitStructure;
			USART_InitTypeDef USART_InitStructure;
			NVIC_InitTypeDef NVIC_InitStructure;
							
			RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA, ENABLE);
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE );
							
			GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_1);
			GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_1);        
			/*
			*  USART1_TX -> PA9 , USART1_RX ->        PA10
			*/                                
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;                 
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
			USART_Init(USART1, &USART_InitStructure); //配置入结构体

			

			/* TIM3 clock enable */
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

			/*  TIM3 中断嵌套设计*/
			NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);
	
	
	
			USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启中断
			USART_Cmd(USART1, ENABLE);//使能串口1

	}			

		
void USART1_IRQHandler(void)                	//串口1中断服务程序
{
		//unsigned char Res;
		uint16_t Res;
		/*if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{
				Res =USART_ReceiveData(USART1);//(USART1->DR);	//读取接收到的数据
			
				USART1->TDR= Res;
				
				USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		 } */
		if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  															//接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{
				Res =USART_ReceiveData(USART1);																										//(USART1->DR);	//读取接收到的数据
				if((USART_RX_STA&0x8000)==0)																											//接收未完成
				{
						if(USART_RX_STA&0x4000)																													//接收到了0x0d
						{
								if(Res!=0x0a)
										USART_RX_STA=0;																									//接收错误,重新开始
								else 
										USART_RX_STA|=0x8000;																										//接收完成了 
						}
						else 																																						//还没收到0X0D
						{	
								if(Res==0x0d)
										USART_RX_STA|=0x4000;
								else
								{
										USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
										USART_RX_STA++;
										USART_ClearITPendingBit(USART1, USART_IT_RXNE);
										if(USART_RX_BUF[0] == 'R')
										{
												SW_RESET();
										}
										if(USART_RX_STA>(20-1))
												USART_RX_STA=0;														//接收数据错误,重新开始接收	  
								}		 
					}
				}   		 
  } 

} 
		
void UART_send_byte(uint8_t byte) //发送1字节数据
{
 while(!((USART1->ISR)&(1<<7)));
 USART1->TDR=byte;	
}		

void UART_Send(uint8_t *Buffer, uint32_t Length)
{
	while(Length != 0)
	{
		while(!((USART1->ISR)&(1<<7)));//等待发送完
		USART1->TDR= *Buffer;
		Buffer++;
		Length--;
	}
}

uint8_t UART_Recive(void)
{	
	while(!(USART1->ISR & (1<<5)));//等待接收到数据
	return(USART1->RDR);			 //读出数据
}

//发送字符串
void USART1_SendString(unsigned char const *buf)
{
		
		while(*buf)
		{				    
			USART_SendData(USART1,*buf++);		
			while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET); 
      		USART_ClearFlag(USART1,USART_FLAG_TXE);
            
		}	
}


	
