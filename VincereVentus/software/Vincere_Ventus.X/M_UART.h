/*
Propriété du 
Club Chinook/ETS
*/
/******************************************************************
					M_UART.h
******************************************************************/

#ifndef MOTOR_UART
#define MOTOR_UART

#include "p33EP512MU810.h"
#include "Global.h"

/******************************************************************/
//    P3 connector on Driver
//    ____
//   | 1 |	- NC 			
//   | 2 |  - GND					
//   | 3 |  - TX			RP104/RF8		
//   | 4 |  - RX			RP98/RF2	
//   | 5 |  - 5V					
//   |_6_|  - NC			
//
//   Pin 1 is Not Connected
//	 Pin 2 is Gnd from board
//   Pin 3 is Tx of the dsPIC
//   Pin 4 is Rx of the dsPIC
//   Pin 5 is 5V to the board
//   Pin 6 is Not Connected
//
//
/*****************************************************************/
/*                      PUBLIC FUNCTIONS                         */
/*****************************************************************/
/*
Init_UART

	Initialise the Uart 1 module to communicate with a TTL-232R 
	converter. The function enable Rx and Tx interrupt which are
	used to process data

	INPUT 	: 
			- BaudRate
			= Type: unsigned int 
			= Value: 0 or Baudrate index to be transfer to U1BRG 
					(See S17_UART p.9 for calcul)

				
	OUTPUT 		:
				- None
				
	EFFECT 		:
				- Uart 1 module is started and interrupt enable
    
	SPEC		: 	
				-Rx and Tx IO are set outside the function.
				-If Baudrate ==0 then the transmitter must send 'U' to
				initialize transmission
				
	CALL Example:

	#define BAUDRATE	9600
	//FOSC is the frequency of the CPU clock
	_RP98R =	0b000001;									//Connect RP98  to U1TX
	Init_UART((unsigned int)(FOSC/BAUDRATE/32.0f)-1,104);	//Connect RP104 to U1RX
	
		-or-
	_RP98R =	0b000001;	//Connect RP98 to U1TX	
	Init_UART(0,104);	//Transmitter must send a 'U' before first transmission	
*/
void Init_UART(unsigned int BaudRate,unsigned int RX);

char CharToInt(char in_char,int * number);

void IntToChar(char tab[], int tab_l, int * number);

void DebugReg(unsigned int reg);
#endif

