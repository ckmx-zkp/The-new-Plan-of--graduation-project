#ifndef _SMBUS_H
#define _SMBUS_H

#include<reg51.h>

//High and Low level of clock @ Fosc=11.0592MHz, Tcy=362ns
#define HIGHLEV  5
#define LOWLEV  5
//Delay constants @ Fosc=11.0592MHz, Tcy=362ns
#define TBUF 5

//--定义使用的IO口--//

sbit SMBus_SCL = P2^4;
sbit SMBus_SDA = P2^5;

void SMBus_Start(void);
void SMBus_Stop(void);
unsigned char SMBus_TX_Byte(unsigned char Tx_buffer);
unsigned char SMBus_RX_Byte(unsigned char ack_nack);

bit SMBus_Send_Byte(unsigned char dat);
unsigned char SMBus_Receive_Byte(bit ack);

#endif