/*
Propriété du 
Club Chinook/ETS
*/
/******************************************************************
					M_TMR.c
******************************************************************/
#include <p33EP512MC806.h>
#include "../../../hardware_profile.h"
/**********************CANbus Variables***************************/
extern unsigned char CanTimeout;
/*****************************************************************/

/******************************************************************
					TMR1
******************************************************************/
void Init_Timer1(void)
{
	//Init Timer 1
	TMR1 = 0x0000;
	T1CONbits.TCKPS	= 0b11;
	T1CONbits.TGATE = 1;	//Gated input
	PR1 = 0xFFFF;
	_T1IF = 0;// Clear Timer3 interrupt
	_T1IP = 7;
	_T1IE = 1;// Disable Timer3 interrupt
	T1CONbits.TON = 1;// Start Timer3
}
/******************************************************************
					TMR2
******************************************************************/
void Init_Timer2(float freq)
{
	float div=2.0f;
	//Init Timer 2
	T2CONbits.TON = 0;
	TMR2 = 0x0000;
	
	//Calibrate prescaller with given freq
	if(FOSC/(256.0f*2.0f*freq)>2.0f)
	{
		div=2.0f*256.0f;	
		T2CONbits.TCKPS	= 0b11;
	}
	else if(FOSC/(64.0f*2.0f*freq)>2.0f)
	{
		div=2.0f*64.0f;
		T2CONbits.TCKPS	= 0b10;
	}
	else if(FOSC/(8.0f*2.0f*freq)>2.0f)
	{
		div=2.0f*8.0f;
		T2CONbits.TCKPS	= 0b01;
	}
	else
	{
		T2CONbits.TCKPS	= 0b00;
	}
	
	PR2 = (unsigned int)(FOSC/(div*freq));	
	_T2IP = 7;
	_T2IF = 0;// Clear Timer2 interrupt
	_T2IE = 1;// Enable Timer2 interrupt
}
/*****************************************************************/

/******************************************************************
					TMR3
******************************************************************/
void Init_Timer3(float freq)
{
	float div=2.0f;
	//Init Timer 3
	TMR3 = 0x0000;
	
	//Calibrate prescaller with given freq
	if(FOSC/(256.0f*2.0f*freq)>2.0f)
	{
		div=2.0f*256.0f;	
		T3CONbits.TCKPS	= 0b11;
	}
	else if(FOSC/(64.0f*2.0f*freq)>2.0f)
	{
		div=2.0f*64.0f;
		T3CONbits.TCKPS	= 0b10;
	}
	else if(FOSC/(8.0f*2.0f*freq)>2.0f)
	{
		div=2.0f*8.0f;
		T3CONbits.TCKPS	= 0b01;
	}
	else
	{
		T3CONbits.TCKPS	= 0b00;
	}
	
	PR3 = (unsigned int)(FOSC/(div*freq));	
	div=1.0f/div;	
	_T3IF = 0;// Clear Timer3 interrupt
	_T3IP = 7;
	_T3IE = 1;// Disable Timer3 interrupt
}
/******************************************************************
					TMR4
******************************************************************/
void Init_Timer4(float freq)
{
	float div=2.0f;
	//Init Timer 4
	TMR4 = 0x0000;

	//Calibrate prescaller with given freq
	if(FOSC/(256.0f*2.0f*freq)>2.0f)
	{
		div=2.0f*256.0f;
		T4CONbits.TCKPS	= 0b11;
	}
	else if(FOSC/(64.0f*2.0f*freq)>2.0f)
	{
		div=2.0f*64.0f;
		T4CONbits.TCKPS	= 0b10;
	}
	else if(FOSC/(8.0f*2.0f*freq)>2.0f)
	{
		div=2.0f*8.0f;
		T4CONbits.TCKPS	= 0b01;
	}
	else
	{
		T4CONbits.TCKPS	= 0b00;
	}

	PR4 = (unsigned int)(FOSC/(div*freq));
	div=1.0f/div;
	_T4IF = 0;// Clear Timer4 interrupt
	_T4IP = 2;
	_T4IE = 1;// Enable Timer4 interrupt
	T4CONbits.TON = 0;// Don't Start Timer4
}

/*****************************************************************/
void Reset_Timeout(void)
{
T3CONbits.TON = 0;// Stop Timer2
CanTimeout = 0;
TMR3 = 0;			//Reset the CAN bus timeout counter
}
/*****************************************************************/
/*****************************************************************/
void Set_Timeout(void)
{
T3CONbits.TON = 1;// Stop Timer2
}
/*****************************************************************/

/******************************************************************
					TMR5
******************************************************************/
void Init_Timer5(float freq)
{
	float div=2.0f;
	//Init Timer 5
	TMR5 = 0x0000;
	
	//Calibrate prescaller with given freq
	if(FOSC/(256.0f*2.0f*freq)>2.0f)
	{
		div=2.0f*256.0f;	
		T5CONbits.TCKPS	= 0b11;
	}
	else if(FOSC/(64.0f*2.0f*freq)>2.0f)
	{
		div=2.0f*64.0f;
		T5CONbits.TCKPS	= 0b10;
	}
	else if(FOSC/(8.0f*2.0f*freq)>2.0f)
	{
		div=2.0f*8.0f;
		T5CONbits.TCKPS	= 0b01;
	}
	else
	{
		T5CONbits.TCKPS	= 0b00;
	}
	
	PR5 = (unsigned int)(FOSC/(div*freq));	
	div=1.0f/div;	
	_T5IF = 0;// Clear Timer5 interrupt
	_T5IE = 1;// Enable Timer5 interrupt
	_T5IP = 4;
	T5CONbits.TON = 1;// Start Timer5
}





/************************************************************/
/*			        	Gated Timers				 		*/
/************************************************************/
void Init_Timer6(void)
{
	//Gate input
	_T6CKR = 67;	//SIGNAL_IN3
	T6CON			=0x0000;
	T6CONbits.TGATE =1;	//Gated mode-> count nbr of clock in Gate signal
	T6CONbits.TCKPS = 0b10; //1:64 prescaller
	PR6 = 0xFFFF;
	_T6IP=7;
	_T6IF=0;
	_T6IE=1;
	T6CONbits.TON	=1;
}
/**********************************************************/
void Init_Timer7(void)
{
	//Gate input
	_T7CKR = 66;	//SIGNAL_IN2
	//
	T7CON			=0;
	T7CONbits.TGATE =1;	//Gated mode-> count nbr of clock in Gate signal
	T7CONbits.TCKPS = 0b10; //1:64 prescaller
	PR7 = 0xFFFF;
	_T7IP=6;
	_T7IF=0;
	_T7IE=1;
	T7CONbits.TON	=1;
}
/**********************************************************/
void Init_Timer8(void)
{
	//Gate input
	_T8CKR = 65;		//SIGNAL_IN1
	T8CON			=0;
	T8CONbits.TGATE =1;	//Gated mode-> count nbr of clock in Gate signal
	T8CONbits.TCKPS = 0b11; //1:64 prescaller
	PR8 = 0xFFFF;
        _T8IP=6;
	_T8IF=0;
	_T8IE=1;
	T8CONbits.TON	=1;
}
/**********************************************************/
void Init_Timer9(void)
{
	//Gate input
	_T9CKR = 64;		//SIGNAL_IN0
	T9CON			=0;
	T9CONbits.TGATE =1;	//Gated mode-> count nbr of clock in Gate signal
	T9CONbits.TCKPS = 0b10; //1:64 prescaller
	PR9 = 0xFFFF;
        _T9IP=6;
	_T9IF=0;
	_T9IE=1;
	T9CONbits.TON	=1;
}
/**********************************************************/
