#include "p33EP512MU810.h"
#include "Global.h"
#include "M_TMR.h"

void Init_PWM(void)
{

	/*Transmission*/
	STCON = 0x0000;
	STCON2bits.PCLKDIV = 0b011;
	STPER = (unsigned int)((FOSC/8.0f)/FREQ_PWM);	//1310khz
	PDC5 = STPER>>1;    //50% duty cycle

	PWMCON5 =0x0000;
	PWMCON5bits.MDCS =0;	//USE PDC5 as duty-cycle
        PWMCON5bits.MTBS = 1;	//USE STPER as Time Base
	IOCON5 =0x0000;
	IOCON5bits.PENL =0;
	IOCON5bits.PMOD =0b00;	//Complementary Output mode
	IOCON5bits.SWAP =0;

        /*Active low reset of stepper*/
	RST_STEP = 1;

        /*Full Step when USM0 = 0 and USM1 = 0*/
        USM0 = 1;
        USM1 = 1;

        /*LEFT when DIR = 1*/
        DIR = DOWN;

        /*Enable Stepper : Active Low*/
        EN_STEP = 1;
        /*Timer3 for Stepper speed control*/
        Init_Timer3(9.0f);



	/*Mât*/
        PTCON = 0x0000;
        PTCON2bits.PCLKDIV = 0b011;
	PTPER = (unsigned int)((FOSC/8.0f)/FREQ_PWM_DC_DRV);	//80khz
	PDC1 = PTPER>>1;

	PWMCON1 =0x0000;
	PWMCON1bits.MDCS =0;	//USE PDC1 as duty-cycle
        PWMCON1bits.MTBS = 0;	//USE PTPER as Time Base
	IOCON1bits.PENH =1;
	IOCON1bits.PENL =1;
	IOCON1bits.PMOD =0b00;	//Complementary Output mode
	IOCON1bits.SWAP =0;

        /*PWM trigger to ADC1*/
        TRIG1 = PTPER>>3; /* Point at which the ADC module is to be triggered by primary PWM */
        TRGCON1bits.TRGDIV = 0b1111; /* Trigger output divider set to trigger ADC on every trigger match event */
        TRGCON1bits.TRGSTRT = 4; /* First ADC trigger event occurs after four trigger match events */
        PWMCON1bits.TRGIEN = 1; /* Trigger event generates an interrupt request */
        while (PWMCON1bits.TRGSTAT = 1); /* Wait for ADC interrupt status change */

        /*Active low reset of DC motor drive*/
        RST_DRV = 1;
        
        _PWM1IF=0;
        _PWM1IP=1;
        _PWM1IE=1;

	PTCONbits.PTEN =1;
}

void __attribute__((interrupt, auto_psv)) _PWM1Interrupt(void)
{

	_PWM1IF=0;
}

void Motor_PWM_two_Level(unsigned int * PWMx, float Duty)
{
	/*
		Two Level motor drive. Duty from -1.0f to 1.0f
		Motor voltage waveform below
+VCC  _		_____      __        _____   
	0 _	   |     |    |  |      |     |     |
-VCC  _	___|     |____|  |______|     |_____|
		                     
	Register Map                        
	PWMx[0] = PWMCONx
	PWMx[1] = IOCONx
	PWMx[2] = FCLCONx
	PWMx[3] = PDCx
	PWMx[4] = PHASEx
	PWMx[5] = SDCx
	etc...
	*/
	Duty = 0.5f*Duty+0.5f;
		
	PWMx[3] = (unsigned int)((float)PTPER*Duty);
		
}
/*
	Call exemple
	Motor_PWM_three_Level(& PWMCON1, -0.5f)
*/
void Motor_PWM_three_Level(unsigned int * PWMx, float Duty)
{
	/*
		Three Level motor drive. Duty from -1.0f to 1.0f
		Motor voltage waveform below
		|---Forward PWM----|
+VCC  _		_____      __           
	0 _	___|     |____|  |___    _____       ____
-VCC  _	                     |__|     |_____|
		                     
	                        |-----Backward PWM---|
	Register Map                        
	PWMx[0] = PWMCONx
	PWMx[1] = IOCONx
	PWMx[2] = FCLCONx
	PWMx[3] = PDCx
	PWMx[4] = PHASEx
	etc...
	
	*/
	
	//PWM in redundant mode
	//OVRDAT<1:0>: = 0b00
	if(Duty < 0.0f)
	{
		//High output active
		//Overide Low output with low state
		Duty *= -1.0f;
		PWMx[1] &= ~0x0100;		//Clear bit 8 OVRENL: PWM generator provides data for PWMxL pin
		PWMx[1] |= 0x0200;		//Set bit 9 OVRENH: Override Enable for PWMxH Pin bit
		PWMx[3] = (unsigned int)((float)PTPER*Duty);
	}
	else
	{
		//High output active
		//Overide Low output with low state
		PWMx[1] &= ~0x0200;		//Clear bit 9 OVRENH: PWM generator provides data for PWMxH pin
		PWMx[1] |= 0x0100;		//Set bit 8 OVRENL: Override Enable for PWMxL Pin bit
		PWMx[3] = (unsigned int)((float)PTPER*Duty);
	}	
}