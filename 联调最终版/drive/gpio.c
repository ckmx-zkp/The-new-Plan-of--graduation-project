//****************************************Copyright (c)**************************************************
//                       基 于 OpenM0V 试 验 板 程 序                            
//
// 这部分程序基于IAR EWARM6.50编译环境
// 
// 芯片型号          : STM32F051R8T6
// 晶振频率          : 8.000000 MHz
//
//--------------文件信息--------------------------------------------------------------------------------
//文   件   名: gpio.c
//创   建   人:喻金钱
//最后修改日期: 2013年11月01日
//描        述: 初始化LED和按键所对应IO口；按键扫描程序；按键处理程序
//              
//店      铺：

//********************************************************************************************************

#include "stm32f0xx.h"
#include "usart.h"
#include "gpio.h"
#include "adc.h"

unsigned char key_bit;

//*******************************************************************************
// 函数名称    : void gpio_conf(void)
// 功能描述    : IO口参数初始化定义函数.定义PB3--7为输出驱动LED灯
//                定义PC0--3为输入，作为按键引脚
//
// 输入        : None
// 输出        : None
// 返回        : None
//******************************************************************************
void gpio_conf(void)
{
  GPIO_InitTypeDef        GPIO_InitStructure;
   /* GPIOB 外设时钟使能 */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

  /* 配置PB3-7外设为输出 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | 
                                GPIO_Pin_6 | GPIO_Pin_7    ;      //外设口线3-7
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   //设为输出
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;   //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50MHzIO口
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //无上拉 
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
    /* GPIOB 外设时钟使能 */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

  /* 配置PC0-3外设为输出 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 ;  //外设口线3-7
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;   //设为输入
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50MHzIO口
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //无上拉 
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}

//*******************************************************************************
// 函数名称    : void key1(void)
// 功能描述    : 按键K1处理函数。  
//               按K1键，LED1跳变一次，通过串口发送0x31数据
// 输入        : None
// 输出        : None
// 返回        : None
//******************************************************************************
//void key1(void)
//{
//  LED1B();
//  uart2_trx[uart2_rx++] = 0X31;
//}

//*******************************************************************************
// 函数名称    : void key2(void)
// 功能描述    : 按键K2处理函数。  
//               按K2键，LED2跳变一次，通过串口发送0x32数据
// 输入        : None
// 输出        : None
// 返回        : None
//******************************************************************************
//void key2(void)
//{  
//  LED2B();
//  uart2_trx[uart2_rx++] = 0X32;
//}

//*******************************************************************************
// 函数名称    : void key3(void)
// 功能描述    : 按键K3处理函数。  
//               按K3键，LED3跳变一次，通过串口发送0x33数据
// 输入        : None
// 输出        : None
// 返回        : None
//******************************************************************************
void key3(void)
{
  LED3B();
  uart2_trx[uart2_rx++] = 0X33;
}

//*******************************************************************************
// 函数名称    : void key4(void)
// 功能描述    : 按键K4处理函数。  
//               按K4键，LED4跳变一次，通过串口发送0x34数据
// 输入        : None
// 输出        : None
// 返回        : None
//******************************************************************************
void key4(void)
{
  LED4B();
  uart2_trx[uart2_rx++] = 0X34;
}

//*******************************************************************************
// 函数名称    : void key_work(void)
// 功能描述    : 按键扫描函数.从PC口读取按键值，经过延时判断后，对按键值进行处理。
//               每次按键处理一次
// 输入        : None
// 输出        : None
// 返回        : None
//******************************************************************************
void key_work(void)
   { 
      unsigned char key_data;
      key_data = GPIO_ReadInputData(GPIOC);  //读取PC输入端口值 
      key_data &= 0x0f;
      if(key_data < 0x0F)         //如果小于0X7F，说明有按键按下
       {     
         if(!(key_bit & 0x02))  //判断按键是否被处理，按键没有被处理，执行IF
          {   
            if(key_bit & 0x01)  //如果已经延时了
             {  
               key_bit &= ~0x01;    //清延时标志
               key_bit |=  0x02;    //置位按键已处理标志
               switch(key_data)
                {
                  case 0x0E :  key1(); break;  //调用key1()函数
                  case 0x0D :  key2(); break;  //调用key2()函数
                  case 0x0B :  key3(); break;  //调用key3()函数
                  case 0x07 :  key4(); break;  //调用key4()函数
                }  
             }  
           else               //如果没有延时
            {
               key_bit |= 0x04;   //置位要延时标志
            }
          }  
       }  
      else  //如果没有键按下，执行else
       {
         key_bit &= ~0x07;    //清所有的标志位 
       }  
   }  
