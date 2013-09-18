#include "p33EP512MU810.h"
#include "Global.h"
#include "CMD.h"
#include "M_UART.h"
#include "M_TMR.h"
#include "math.h"
#include <stdio.h>

/******************************************************************
					UART ISR
******************************************************************/
unsigned int input=0;
char InCom;
void __attribute__((interrupt, auto_psv)) _U1RXInterrupt(void)
{
	
	InCom=CharToInt(U1RXREG,&input);
	 
	 U1TXREG = InCom;		 
	 //ecan1MsgBuf[0][4] = InCom;
	_U1RXIF = 0; // clear RX interrupt flag	
}

void __attribute__((interrupt, auto_psv)) _U1TXInterrupt(void)
{
	_U1TXIF = 0; // clear TX interrupt flag
}
