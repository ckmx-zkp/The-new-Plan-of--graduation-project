#include "usart.h"
#include "usart2.h"
#include <stdarg.h>
#include <stdio.h>




 //�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
////����_sys_exit()�Ա���ʹ�ð�����ģʽ    
//_sys_exit(int x) 
//{ 
//	x = x; 
//} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET); 
    USART_SendData(USART1,(uint8_t)ch);   
	return ch;
}
#endif  


void USART_Configuration(void)//���ڳ�ʼ������
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
			
			USART_InitStructure.USART_BaudRate = 9600;//���ô��ڲ�����
			USART_InitStructure.USART_WordLength = USART_WordLength_8b;//��������λ
			USART_InitStructure.USART_StopBits = USART_StopBits_1;//����ֹͣλ
			USART_InitStructure.USART_Parity = USART_Parity_No;//����Ч��λ
			USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//����������
			USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//���ù���ģʽ
			USART_Init(USART1, &USART_InitStructure); //������ṹ��

			

			/* TIM3 clock enable */
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

			/*  TIM3 �ж�Ƕ�����*/
			NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);
	
	
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�����ж�
			USART_Cmd(USART1, ENABLE);//ʹ�ܴ���1

	}			

		
void USART1_IRQHandler(void)                	//����1�жϷ������
{
		unsigned char Res;
		
		if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
				Res =USART_ReceiveData(USART1);//(USART1->DR);	//��ȡ���յ�������
				if(Res != NULL)
				{
						USART_SendData(USART2, Res);
				}
				USART1->TDR= Res;
		 } 

} 
		
void UART_send_byte(uint8_t byte) //����1�ֽ�����
{
 while(!((USART1->ISR)&(1<<7)));
 USART1->TDR=byte;	
}		

void UART_Send(uint8_t *Buffer, uint32_t Length)
{
	while(Length != 0)
	{
		while(!((USART1->ISR)&(1<<7)));//�ȴ�������
		USART1->TDR= *Buffer;
		Buffer++;
		Length--;
	}
}

uint8_t UART_Recive(void)
{	
	while(!(USART1->ISR & (1<<5)));//�ȴ����յ�����
	return(USART1->RDR);			 //��������
}

//�����ַ���
void USART1_SendString(unsigned char const *buf)
{
		
		while(*buf)
		{				    
			USART_SendData(USART1,*buf++);		
			while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET); 
      		USART_ClearFlag(USART1,USART_FLAG_TXE);
            
		}	
}


	
