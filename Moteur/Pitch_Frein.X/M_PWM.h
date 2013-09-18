/*
Propriété du 
Club Chinook/ETS
*/
/******************************************************************
					M_PWM.h
******************************************************************/

#ifndef MOTOR_PWM
#define MOTOR_PWM

void Init_PWM(void);

void Motor_PWM_two_Level(unsigned int * PWMx, float Duty);

void Motor_PWM_three_Level(unsigned int * PWMx, float Duty);

#endif