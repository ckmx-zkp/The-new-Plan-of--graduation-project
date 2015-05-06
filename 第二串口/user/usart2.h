#ifndef __USART2_H
#define	__USART2_H

#include "stm32f0xx.h"
#include <stdio.h>




void USART2_Configuration(void);
int fputc2(int ch, FILE *f);
void UART2_send_byte(uint8_t byte);
void UART2_Send(uint8_t *Buffer, uint32_t Length);
uint8_t UART2_Recive(void);
void USART2_SendString(unsigned char const *buf);
#endif /* __UART_H */
