#include <p33EP256MC502.h>
#include "Global.h"
#include "M_TMR.h"

void Init_PWM(void)
{

	/*Pitch*/
	PTCON = 0x0000;
	PTCON2bits.PCLKDIV = 0b011;
	PTPER = (unsigned int)((FOSC/8.0f)/FREQ_STEPPER);
	PDC1 = PTPER>>1;    //50% duty cycle
        PDC2 = PTPER>>1;    //50% duty cycle

	PWMCON1 =0x0000;
	PWMCON1bits.MDCS =0;	//USE PDC1 as duty-cycle
        PWMCON1bits.MTBS = 0;	//USE PTPER as Time Base
	IOCON1 =0x0000;
	IOCON1bits.PENL =1;
        IOCON1bits.PENH =1;
	IOCON1bits.PMOD =0b01;	//Complementary Output mode
	IOCON1bits.SWAP =0;

	PWMCON2 =0x0000;
	PWMCON2bits.MDCS =0;	//USE PDC2 as duty-cycle
        PWMCON2bits.MTBS = 0;	//USE PTPER as Time Base
	IOCON2 =0x0000;
	IOCON2bits.PENL =1;
        IOCON2bits.PENH =1;
	IOCON2bits.PMOD =0b01;	//Complementary Output mode
	IOCON2bits.SWAP =0;

        PWMCON3 =0x0000;
	PWMCON3bits.MDCS =0;	//USE PDC2 as duty-cycle
        PWMCON3bits.MTBS = 0;	//USE PTPER as Time Base
	IOCON3 =0x0000;
	IOCON3bits.PENL =0;
        IOCON3bits.PENH =0;
	IOCON3bits.PMOD =0b00;	//Complementary Output mode
	IOCON3bits.SWAP =0;

	PTCONbits.PTEN =1;
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