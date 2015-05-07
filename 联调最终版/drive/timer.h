#ifndef _TIMER_H
#define _TIMER_H
#include "stm32f0xx.h"

void TIMER_Config(void);
static void delay_ms(uint16_t time);
uint16_t search(uint16_t *a);
void TIMER2_Config(void);


#endif
