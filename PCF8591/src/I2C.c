#include "../inc/I2C.h"
#include <mcs51/C8051F120.h>

#define NOP() 
#define _Nop() NOP()

#define SDA P0_0
#define SCL P0_1
extern unsigned char ack;

void Start_I2c()
{
    SDA = 1;
    _Nop();
    SCL = 1;
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    SDA = 0;
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    SCL = 0;
    _Nop();
    _Nop();
}

void Stop_I2c()
{
    SDA = 0;
    _Nop();
    SCL = 1;
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    SDA = 1;
    _Nop();
    _Nop();
    _Nop();
    _Nop();
}

void SendByte(unsigned char c)
{
    unsigned char BitCnt;

    for (BitCnt = 0; BitCnt < 8; BitCnt++)
    {
        if ((c << BitCnt) & 0x80)
            SDA = 1;
        else
            SDA = 0;
        _Nop();
        SCL = 1;
        _Nop();
        _Nop();
        _Nop();
        _Nop();
        _Nop();
        SCL = 0;
    }

    _Nop();
    _Nop();
    SDA = 1;
    _Nop();
    _Nop();
    SCL = 1;
    _Nop();
    _Nop();
    _Nop();
    if (SDA == 1)
        ack = 0;
    else
        ack = 1; /*�ж��Ƿ���յ�Ӧ���ź�*/
    SCL = 0;
    _Nop();
    _Nop();
}

unsigned char RcvByte()
{
    unsigned char retc;
    unsigned char BitCnt;

    retc = 0;
    SDA = 1;
    for (BitCnt = 0; BitCnt < 8; BitCnt++)
    {
        _Nop();
        SCL = 0;
        _Nop();
        _Nop();
        _Nop();
        _Nop();
        _Nop();
        SCL = 1;
        _Nop();
        _Nop();
        retc = retc << 1;
        if (SDA == 1)
            retc = retc + 1;
        _Nop();
        _Nop();
    }
    SCL = 0;
    _Nop();
    _Nop();
    return (retc);
}

void Ack_I2c(unsigned char a)
{
    if (a == 0)
        SDA = 0;
    else
        SDA = 1;
    _Nop();
    _Nop();
    _Nop();
    SCL = 1;
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    _Nop();
    SCL = 0;
    _Nop();
    _Nop();
}
