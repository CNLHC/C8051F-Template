#ifndef IIC_H
#define IIC_H
extern unsigned char ack;
void Start_I2c();
void Stop_I2c();
void Ack_I2c(unsigned char a);
void  SendByte(unsigned char  c);
unsigned char ISendStr(unsigned char sla,unsigned char suba,unsigned char *s,unsigned char no) ;
unsigned char ISendStrExt(unsigned char sla,unsigned char *s,unsigned char no);
unsigned char RcvByte();
#endif
            
