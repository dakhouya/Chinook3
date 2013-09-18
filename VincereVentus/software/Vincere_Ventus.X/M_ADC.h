/*
Propriété du 
Club Chinook/ETS
*/
/******************************************************************
					M_ADC.h
******************************************************************/

#ifndef MOTOR_ADC
#define MOTOR_ADC

#define	G_ADC	3.3f/1024.0f

void Init_ADC(void);
float update_current(void);

#endif