#include "common.h"

static void SMBus_Delay(unsigned int us)
{
	int i;
	char a, b;
	for(b=1; b>0; b--)
	{
		for(a=1; a>0; a--);
	}
	return;	
	for(i = 0; i < us; i++)
	{  
		//_nop_();  
	}
}
void SMBus_Start(void)
{
//	SMBus_SCL = 0;
//	SMBus_Delay(100000);

   SMBus_SDA = 1;
   SMBus_Delay(TBUF);
   SMBus_SCL = 1;
   SMBus_Delay(TBUF);

   SMBus_SDA = 0;
   SMBus_Delay(TBUF);
   SMBus_SCL = 0;
   SMBus_Delay(TBUF);
}
void SMBus_Stop(void)
{
   SMBus_SCL = 0;
   SMBus_Delay(TBUF);
   SMBus_SDA = 0;
   SMBus_Delay(TBUF);

   SMBus_SCL = 1;
   SMBus_Delay(TBUF);
   SMBus_SDA = 1;
   SMBus_Delay(TBUF);
}
bit SMBus_Send_Byte(unsigned char dat)
{
	int i;
	bit ack;
	for (i = 0; i < 8; i++)
	{
		SMBus_SDA = dat >> 7;	

		dat = dat << 1;

		SMBus_Delay(TBUF);

		SMBus_SCL = 1;
		SMBus_Delay(HIGHLEV);
		SMBus_SCL = 0;
		SMBus_Delay(LOWLEV);
	}
	SMBus_SDA = 1;
	SMBus_Delay(HIGHLEV);
	SMBus_SCL = 1;
	SMBus_Delay(HIGHLEV);
	ack = SMBus_SDA;
	SMBus_SCL = 0; 

	return ack;
}
unsigned char SMBus_Receive_Byte(bit ack)
{
	unsigned char dat = 0x00;
	int i;
	SMBus_SDA = 1;
	SMBus_Delay(HIGHLEV);
	for(i = 0; i <8; i++)
	{
		SMBus_SCL = 1;
		SMBus_Delay(HIGHLEV);
		dat <<= 1;
		dat |= SMBus_SDA;
		SMBus_Delay(LOWLEV);
		SMBus_SCL = 0;
		SMBus_Delay(LOWLEV);
	}	
	SMBus_SDA = ack;
	SMBus_Delay(TBUF);
	SMBus_SCL = 1;
	SMBus_Delay(HIGHLEV);
	SMBus_SCL = 0;
	SMBus_Delay(LOWLEV);   
	return dat;
}