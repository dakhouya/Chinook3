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

#define FREQ_STEPPER            1500.0f			//Refresh rate of alim control loop
#define FREQ_PWM                702.0f
#define FREQ_PWM_DC_DRV         20000.0f
#define	FREQ_QEI		10.0f

/******************Memory*************/
#define NUM_OF_ECAN_BUFFERS 32
/******************************************************************
							IO
******************************************************************/
#define LED0		_LATF8
#define LED1		_LATA2
#define ENALIM		_LATC4
#define RST_STEP	_LATG1
#define STEP            _LATC1
#define EN_STEP         _LATA6
#define DIR             _LATG0
#define USM0            _LATF0
#define USM1            _LATF1
#define HOME_STEP       _LATA7

#define UP             1
#define DOWN           0

#define BOUTON_SHIFT    _RB10
#define BOUTON_DIR      _RB11

#define RST_DRV         _LATE4


/**************************************************************
					Calculus Constant
***************************************************************/
//All const float are define in main
//Const should be define as extern

#define	MAT_COUNT_MAX 24100

extern float Mat_Pos_Ref;
extern float Mat_Pos;

extern const float GM5;
#endif

