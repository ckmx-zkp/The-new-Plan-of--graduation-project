#ifndef __USART_H
#define	__USART_H

#include "stm32f0xx.h"
#include <stdio.h>




void USART_Configuration(void);
int fputc(int ch, FILE *f);
void UART_send_byte(uint8_t byte);
void UART_Send(uint8_t *Buffer, uint32_t Length);
uint8_t UART_Recive(void);
void USART1_SendString(unsigned char const *buf);
#endif /* __UART_H */
