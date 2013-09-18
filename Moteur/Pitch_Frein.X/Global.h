/*
Propriété du 
Club Chinook/ETS
*/
/******************************************************************
					Global.h
******************************************************************/

#ifndef MOTOR_GLOBAL
#define MOTOR_GLOBAL
/******************************************************************
						Select module
******************************************************************/

/******************************************************************
						Timing define
******************************************************************/
#define FOSC_MHZ 		100.0f  		//F en MHz (pas plus haut que 120Mhz)
#define FOSC			FOSC_MHZ*1000000.0f
#define BAUDRATE 		115200.0f  		//Baudrate of UART

#define FREQ_STEPPER            10000.0f			//Refresh rate of alim control loop

/******************Memory*************/
#define NUM_OF_ECAN_BUFFERS 32
/******************************************************************
                    	IO
******************************************************************/
#define AIN1        _LATB11
#define PWMA        _LATB10
#define AIN2        _LATB9
#define STDBY       _LATB8
#define FB24        _RB5
#define PITCH_NEG        1
#define PITCH_POS        8

#endif

