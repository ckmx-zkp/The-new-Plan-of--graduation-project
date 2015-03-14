#include "common.h"

u16 MLX90614Convert(u8 DL, u8 DH)
{
	u32 dat = (DH*256 | DL) * 2;
	if(dat >= 27315)
	{
		dat = dat - 27315;
	}
	else
	{
		dat = 27315 - dat;
	}

	return (u16)dat;
}

u16 MLX90614Read(unsigned char addr, unsigned char Command)
{
	unsigned char PEC, dl, dh;
	bit ack;
	SMBus_Start();
	ack = SMBus_Send_Byte(0x00 << 1); //����д������ַ
	//SendOneByte(ack);
	ack = SMBus_Send_Byte(addr + Command); //����Ҫ��ȡ�ĵ�ַ
	//SendOneByte(ack);

	SMBus_Start();
	ack = SMBus_Send_Byte((0x00 << 1) + 0x01); //���Ͷ�������ַ
	//SendOneByte(ack);
	dl = SMBus_Receive_Byte(1); //��ȡ����L
	dh = SMBus_Receive_Byte(1); //��ȡ����H
	PEC = SMBus_Receive_Byte(0); //��ȡ����
	SMBus_Stop();
	return MLX90614Convert(dl, dh);	
}
void SendTOorTA(u8 sw)
{
	u16 dat;
	u8 str[10] = "@x2@000.00"; 
	switch(sw)
	{
		case 0:
		{
			dat = MLX90614Read(LineObj1TempAddr,RamAccess);
			str[1] = 'A';
		}break;
		case 1:
		{
			dat = MLX90614Read(LineAbmientTempAddr,RamAccess);
			str[1] = 'B';
		}break;
	}
	str[4] = dat/10000%10 + '0';
	str[5] = dat/1000%10 + '0';
	str[6] = dat/100%10 + '0';
	str[7] = '.';
	str[8] = dat/10%10 + '0';
	str[9] = dat%10 + '0';
	//SendUartStr(str);
	SendWifiStr(str);
}




