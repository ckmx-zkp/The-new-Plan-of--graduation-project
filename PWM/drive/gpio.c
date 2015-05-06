//****************************************Copyright (c)**************************************************
//                       �� �� OpenM0V �� �� �� �� ��                            
//
// �ⲿ�ֳ������IAR EWARM6.50���뻷��
// 
// оƬ�ͺ�          : STM32F051R8T6
// ����Ƶ��          : 8.000000 MHz
//
//--------------�ļ���Ϣ--------------------------------------------------------------------------------
//��   ��   ��: gpio.c
//��   ��   ��:����Ǯ
//����޸�����: 2013��11��01��
//��        ��: ��ʼ��LED�Ͱ�������ӦIO�ڣ�����ɨ����򣻰����������
//              
//��      �̣�

//********************************************************************************************************

#include "stm32f0xx.h"
#include "usart.h"
#include "gpio.h"
#include "adc.h"

unsigned char key_bit;

//*******************************************************************************
// ��������    : void gpio_conf(void)
// ��������    : IO�ڲ�����ʼ�����庯��.����PB3--7Ϊ�������LED��
//                ����PC0--3Ϊ���룬��Ϊ��������
//
// ����        : None
// ���        : None
// ����        : None
//******************************************************************************
void gpio_conf(void)
{
  GPIO_InitTypeDef        GPIO_InitStructure;
   /* GPIOB ����ʱ��ʹ�� */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

  /* ����PB3-7����Ϊ��� */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | 
                                GPIO_Pin_6 | GPIO_Pin_7    ;      //�������3-7
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   //��Ϊ���
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;   //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50MHzIO��
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //������ 
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
    /* GPIOB ����ʱ��ʹ�� */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

  /* ����PC0-3����Ϊ��� */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 ;  //�������3-7
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;   //��Ϊ����
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50MHzIO��
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //������ 
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}

//*******************************************************************************
// ��������    : void key1(void)
// ��������    : ����K1��������  
//               ��K1����LED1����һ�Σ�ͨ�����ڷ���0x31����
// ����        : None
// ���        : None
// ����        : None
//******************************************************************************
//void key1(void)
//{
//  LED1B();
//  uart2_trx[uart2_rx++] = 0X31;
//}

//*******************************************************************************
// ��������    : void key2(void)
// ��������    : ����K2��������  
//               ��K2����LED2����һ�Σ�ͨ�����ڷ���0x32����
// ����        : None
// ���        : None
// ����        : None
//******************************************************************************
//void key2(void)
//{  
//  LED2B();
//  uart2_trx[uart2_rx++] = 0X32;
//}

//*******************************************************************************
// ��������    : void key3(void)
// ��������    : ����K3��������  
//               ��K3����LED3����һ�Σ�ͨ�����ڷ���0x33����
// ����        : None
// ���        : None
// ����        : None
//******************************************************************************
void key3(void)
{
  LED3B();
  uart2_trx[uart2_rx++] = 0X33;
}

//*******************************************************************************
// ��������    : void key4(void)
// ��������    : ����K4��������  
//               ��K4����LED4����һ�Σ�ͨ�����ڷ���0x34����
// ����        : None
// ���        : None
// ����        : None
//******************************************************************************
void key4(void)
{
  LED4B();
  uart2_trx[uart2_rx++] = 0X34;
}

//*******************************************************************************
// ��������    : void key_work(void)
// ��������    : ����ɨ�躯��.��PC�ڶ�ȡ����ֵ��������ʱ�жϺ󣬶԰���ֵ���д���
//               ÿ�ΰ�������һ��
// ����        : None
// ���        : None
// ����        : None
//******************************************************************************
void key_work(void)
   { 
      unsigned char key_data;
      key_data = GPIO_ReadInputData(GPIOC);  //��ȡPC����˿�ֵ 
      key_data &= 0x0f;
      if(key_data < 0x0F)         //���С��0X7F��˵���а�������
       {     
         if(!(key_bit & 0x02))  //�жϰ����Ƿ񱻴�������û�б�����ִ��IF
          {   
            if(key_bit & 0x01)  //����Ѿ���ʱ��
             {  
               key_bit &= ~0x01;    //����ʱ��־
               key_bit |=  0x02;    //��λ�����Ѵ����־
               switch(key_data)
                {
                  case 0x0E :  key1(); break;  //����key1()����
                  case 0x0D :  key2(); break;  //����key2()����
                  case 0x0B :  key3(); break;  //����key3()����
                  case 0x07 :  key4(); break;  //����key4()����
                }  
             }  
           else               //���û����ʱ
            {
               key_bit |= 0x04;   //��λҪ��ʱ��־
            }
          }  
       }  
      else  //���û�м����£�ִ��else
       {
         key_bit &= ~0x07;    //�����еı�־λ 
       }  
   }  
