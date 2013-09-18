/*
Propriété du 
Club Chinook/ETS
*/
/******************************************************************
					M_UART.c
******************************************************************/

#include "M_UART.h"

//#include "CMD.h"

extern struct Stepper Stepper_1;

extern volatile float Vout=0.50f;

void Init_UART(unsigned int BaudRate,unsigned int RX)
{
	_U1RXR= RX;
	//******Set Uart and Baud***************************
	U1MODE=0;
	U1STA=0;
	U1MODEbits.URXINV = 0; //Inverser la polarite de Rx
	U1STAbits.UTXINV =0; //Inverser la polarite de Tx
	U1MODEbits.STSEL = 0; // 1-stop bit
	U1MODEbits.PDSEL = 0; // No Parity, 8-data bits
	U1MODEbits.BRGH = 0; // Low Speed mode4
	U1STAbits.UTXISEL0 = 0; // Interrupt after one Tx character is transmitted
	U1STAbits.UTXISEL1 = 0;
	
	U1MODEbits.UARTEN = 1; // Enable UART
	U1STAbits.UTXEN = 1; // Enable UART Tx
	
	//******Find BaudRate***************************
	U1BRG=BaudRate;
	if(U1BRG==0x0000 || U1BRG==0x0100)
	{
		U1MODEbits.ABAUD = 1; // Auto-Baud Enable
		while(U1MODEbits.ABAUD);
	}
	else
	{
		U1MODEbits.ABAUD = 0; // Auto-Baud Disable	
	}

	_U1RXIF=0;	   // Enable UART Rx interrupt
	_U1RXIP=7;	   // Enable UART Rx interrupt
	_U1RXIE=1;	   // Enable UART Rx interrupt 
	_U1TXIF = 0; 	// Enable UART Tx interrupt
	_U1TXIP = 5;
	_U1TXIE = 0; 	// Enable UART Tx interrupt

	DebugReg(RCON);
	RCON=0;
}

char CharToInt(char in_char,int * number)
{
	if(in_char>='0' && in_char <='9')
	{
		*number=*number *10+(in_char-'0');
		
	}
	return in_char;
}

void IntToChar(char tab[], int tab_l, int * number)
{
	unsigned int i;
	unsigned int j=1;
	for(i=0;i<tab_l;i++)
	{
		tab[tab_l-i-1]=((* number)%(j*10))/j+48;
		j*=10;
	}
}


void DebugReg(unsigned int reg)
{	
	unsigned int val;
	
	//Wait for buffer to be empty
	while(U1STAbits.TRMT == 0);
	
	val=(reg & 0xF000)>>12;
	val=(val>9)?'7'+val:val+'0';
	U1TXREG = val;
	
	val=(reg & 0x0F00)>>8;
	val=(val>9)?'7'+val:val+'0';
	U1TXREG = val;
	
	val=(reg & 0x00F0)>>4;
	val=(val>9)?'7'+val:val+'0';
	U1TXREG = val;
	
	val=(reg & 0x000F);
	val=(val>9)?'7'+val:val+'0';
	U1TXREG = val;
	U1TXREG = 13;
}