#include <mcs51/C8051F120.h>
#include "inc/foo.h"

#define SYSCLK 22118400

void PORT_Init(void);
void Timer3_Init(int counts);

void main(void) {
  SFRPAGE = CONFIG_PAGE;
  PORT_Init();
  SFRPAGE = TMR3_PAGE;
  Timer3_Init(SYSCLK/12/3 );
  EA = 1;
  SFRPAGE = LEGACY_PAGE;
  foo(1,3);
  while (1) {
  }
}

void PORT_Init(void) {
  XBR2 =40;
  P0MDOUT = 0x00;
  P7MDOUT=0xFF;
}

void Timer3_Init(int counts) {
  TMR3CN = 0x00;
  RCAP3 = -counts;
  TMR3 = 0xffff;
  EIE2 |= 0x01;
  TR3 = 1;
}

void Timer3_ISR() __interrupt(14) {
  TF3 = 0;
  P1 = ~P1;
}


