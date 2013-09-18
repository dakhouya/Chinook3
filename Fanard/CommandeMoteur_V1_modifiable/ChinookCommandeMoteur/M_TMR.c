/*
Propriété du 
Club Chinook/ETS
*/
/******************************************************************
					M_TMR.c
******************************************************************/

/*#include "p33EP512MC806.h"
#include "Setup_commande.h"*/

/******************************************************************
					TMR3
******************************************************************/
/*void Init_Timer3(float freq)
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
	_T3IP = 6;
	_T3IE = 1;// Disable Timer3 interrupt
	T3CONbits.TON = 1;// Start Timer3
}*/