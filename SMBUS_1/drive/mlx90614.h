#ifndef _MLX90614_H
#define _MLX90614_H

//command mode
#define RamAccess	0x00
#define EepomAccess	0x20
#define	Mode		0x60
#define ExitMode	0x61
#define	ReadFlag	0xf0
#define EnterSleep	0xff

//ram address	read only
#define AbmientTempAddr		0x03	//周围温度
#define	IR1Addr				0x04
#define	IR2Addr				0x05
#define LineAbmientTempAddr	0x06  	//环境温度
/*0x0000	0x4074	 16500 	0.01/单元
     -40	   125*/
#define LineObj1TempAddr	0x07	//目标温度,红外温度
/*0x27ad-0x7fff	 0x3559 22610	0.02/单元
  -70.01-382.19  0.01   452.2*/
#define	LineObj2TempAddr	0x08

//eepom address
#define TObjMaxAddr		0x00
#define TObjMinAddr		0x01
#define PWMCtrlAddr		0x02
#define TaRangeAddr		0x03
#define KeAddr			0x04
#define ConfigAddr		0x05
#define SMbusAddr		0x0e
#define Reserverd1Addr	0x0f
#define Reserverd2Addr	0x19
#define ID1Addr			0x1c
#define ID2Addr			0x1d
#define ID3Addr			0x1e
#define ID4Addr			0x1f


unsigned int MLX90614Read(unsigned char addr, unsigned char Command);
void SendTOorTA(u8 sw);

#endif
