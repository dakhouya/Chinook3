#include "p33EP512MC806.h"
#include "Global.h"

//#define M_OCTSEL_TMR5

void OC_Change_Duty(unsigned int * OCx, float Duty)
{
	//OCx should be &OCxCON1
	//Duty is a value for 0 to 1
	//Duty=(
	//Duty=(Duty >=0.9999f)?0.9999f:Duty;
	Duty =(((Duty <=0.0001f)?0.0001f:Duty) >=0.9999f)?0.9999f:Duty;
	OCx[3] 		= (unsigned int)((float)OCx[2]*Duty);
}

void OC_PWM(unsigned int * OCx, float Freq_Hz, float Duty,char TMR5_SEL)
{
	//OCx should be &OCxCON1
	//Seting OCxOUT (RPOR) as Output compare output 
	//should be done outside this function, this one is general for all Output compare
	
	//#ifdef M_OCTSEL_TMR5
	if(TMR5_SEL)
	{
	//Set Clock input
		if(T5CONbits.TCKPS	== 0b00)
		{
			Freq_Hz=FOSC/(2.0f*Freq_Hz);
		}
		if(T5CONbits.TCKPS	== 0b01)
		{
			Freq_Hz=FOSC/(8.0f*2.0f*Freq_Hz);
		}
		if(T5CONbits.TCKPS	== 0b10)
		{
			Freq_Hz=FOSC/(64.0f*2.0f*Freq_Hz);
		}
		if(T5CONbits.TCKPS	== 0b11)
		{
			Freq_Hz=FOSC/(256.0f*2.0f*Freq_Hz);
		}	
	}
	else
	{
		//Set Clock input
		Freq_Hz=FOSC/(2.0f*Freq_Hz);
	}
	

	// Clear OCxCON1 and OCxCON2
	OCx[0] 		= 0;
	OCx[1] 		= 0;
	
#ifndef FP_DISABLE_OCX
	if(Freq_Hz>65535.0f)
	{
		//Error, Frequency too low, Change clock input and 
		return;
	}
#endif
	//Set OCsR  with the desire frequency
	OCx[2]		= (unsigned int)(Freq_Hz);	/* Determines the Period */
	
	//Set OCsRS with the desire initial duty-cycle
	OC_Change_Duty(OCx,Duty);

	//Set trigger source
	OCx[1]		|=0x1F;		/* No trigger or sync source is selected */
	
	//Set Output polarity
	OCx[1]		|=0x1000;	/* Inverted Output */
	if(TMR5_SEL)
	{
	//Set Clock input
	//#warning "Output Compare use TIMER5"
	OCx[0] 		|= 0x03 <<10; /* The peripheral clock is selected as the clock input to the OC module */
	}
	else
	{
	//Set Clock input
	OCx[0] 		|= 0x07 <<10; /* The peripheral clock is selected as the clock input to the OC module */
	}
	//Set PWM Mode
	OCx[0] 		|= 0b101;	/* This selects the Edge Aligned PWM mode*/

	//Enabling Interrupt should be done outside this function, this one is general for all Output compare

}

//Exemple d'interupt
void __attribute__((__interrupt__)) _OC1Interrupt(void)
{
	_OC1IF = 0; // clear TX interrupt flag
}
