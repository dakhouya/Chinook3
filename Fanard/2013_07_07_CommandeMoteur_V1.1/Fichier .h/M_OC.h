#ifndef MOTOR_OC
#define MOTOR_OC

/*****************************************************************/
/*                      PUBLIC FUNCTIONS                         */
/*****************************************************************/
/*
OC_PWM

	Initialise all the io of the uC

	INPUT 	: 
			- OCx
				- Type: unsigned int 
				- Value: Adress of the corresponding Output Compare
				
			- Freq_Hz
				-Type: float
				-Value: Any frequency that dont overflow OCxRS
				
	OUTPUT 		:
				- None
    
	SPEC		: 	
				-OC must be the address of any OCxCON1 or else
				the result will be unpredictable.
				
	CALL Example:

	_RP100R=0b010000;			//Set remappable IO as OC1 Output
	OC_PWM(&OC1CON1, 200e3,0.01f,0);	//Set OC1 with a freq of 1KHz	
*/
void OC_PWM(unsigned int * OCx, float Freq_Hz, float Duty,char TMR5_SEL);




/*
OC_Change_Duty

	Change the duty-cycle of any output compare module 
	set as edge aligne PWM

	INPUT 	: 
			- OCx
				- Type: unsigned int 
				- Value: Adress of the corresponding Output Compare
				
			- Duty
				-Type: float
				-Value: from 0.0f to 1.0f
				
	OUTPUT 		:
				- None
    
	SPEC		: 	
				-OC must be the address of any OCxCON1 or else
					the result will be unpredictable.
				-OC_PWM(...) must be called before
				
	CALL Example:

	OC_Change_Duty(&OC1CON1, 0.75f);	//Set OC1 with a freq of 1KHz	
*/
void OC_Change_Duty(unsigned int * OCx, float Duty);


#endif
