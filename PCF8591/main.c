

#include <mcs51/C8051F120.h>
#include "inc/I2C.h"

#define uchar unsigned char
#define PCF8591 0x90

unsigned char AD_CHANNEL;
unsigned long xdata LedOut[8];
unsigned int D[32];

#define P2_0  P2_0;
#define P2_1  P2_1;
#define P2_2  P2_2;
#define P2_3  P2_3;
#define bit unsigned char
unsigned char ack;


unsigned char date;

uchar code table[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82,
											0xf8, 0x80, 0x90};

void display();
void delay(uchar i);
bit DACconversion(unsigned char sla, unsigned char c, unsigned char Val);
bit ISendByte(unsigned char sla, unsigned char c);
unsigned char IRcvByte(unsigned char sla);
void Initial_com(void);

int main()
{
	Initial_com();
	while (1)
	{
		switch (AD_CHANNEL)
		{
		case 0:
			ISendByte(PCF8591, 0x41);
			D[0] = IRcvByte(PCF8591);
			break;

		case 1:
			ISendByte(PCF8591, 0x42);
			D[1] = IRcvByte(PCF8591);
			break;

		case 2:
			ISendByte(PCF8591, 0x43);
			D[2] = IRcvByte(PCF8591);
			break;

		case 3:
			ISendByte(PCF8591, 0x40);
			D[3] = IRcvByte(PCF8591);
			break;

		case 4:
			DACconversion(PCF8591, 0x40, D[4]);
			break;
		}

		D[4] = D[3];

		if (++AD_CHANNEL > 4)
			AD_CHANNEL = 0;

		delay(200);
		SBUF = D[0];
		delay(200);
		SBUF = D[1];
		delay(200);
		SBUF = D[2];
		delay(200);
		SBUF = D[3];
		delay(200);
		if (RI)
		{
			date = SBUF;
			SBUF = date;
			RI = 0;
		}
	}
}

void delay(uchar i)
{
	uchar j, k;
	for (j = i; j > 0; j--)
		for (k = 125; k > 0; k--)
			;
}

bit DACconversion(unsigned char sla, unsigned char c, unsigned char Val)
{
	Start_I2c();
	SendByte(sla);
	if (ack == 0)
		return (0);
	SendByte(c);
	if (ack == 0)
		return (0);
	SendByte(Val);
	if (ack == 0)
		return (0);
	Stop_I2c();
	return (1);
}

bit ISendByte(unsigned char sla, unsigned char c)
{
	Start_I2c();
	SendByte(sla);
	if (ack == 0)
		return (0);
	SendByte(c);
	if (ack == 0)
		return (0);
	Stop_I2c();
	return (1);
}

unsigned char IRcvByte(unsigned char sla)
{
	unsigned char c;

	Start_I2c();
	SendByte(sla + 1);
	if (ack == 0)
		return (0);
	c = RcvByte();

	Ack_I2c(1);
	Stop_I2c();
	return (c);
}

void Initial_com(void)
{
	EA = 1;
	ES = 1;
	ET1 = 1;
	TMOD = 0x20;
	PCON = 0x00;
	SCON = 0x50;
	TH1 = 0xfd;
	TL1 = 0xfd;
	TR1 = 1;
}
