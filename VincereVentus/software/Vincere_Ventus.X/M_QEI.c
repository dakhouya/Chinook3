#include "p33EP512MU810.h"
#include "Global.h"
#include "M_TMR.h"
#include "CMD.h"


volatile unsigned int limit_mat=0;

void InitQEI(void)
{
	//Connector P1 __ 3.3V IO, NOT 5V TOLERANT!!!
	//_RPI36	QEA1
	//_RPI37	QEB1
	//_RPI38	INDX1 -> NOT USED
	//_RPI39 	Home1 -> Magnetic sensor?

	//Module is used as speed feedback and position
	
	QEI1CON=0x0000;

	//Digital Inpurs
	ANSELBbits.ANSB0 = 0;
	ANSELBbits.ANSB1 = 0;

	//Peripheral Remap
	_QEA1R = 46;	// Input RPI42
	_QEB1R = 47;	// Input RPI43

	//Position Counter Initialization Mode Select bits
	QEI1CONbits.PIMOD =	0b000;//Resets the position counter when the position counter equals QEIxGEC register
	//Index Match Value bits
	QEI1CONbits.IMV   =	0b00;	 //Index input event does not affect position counter
	//Timer Input Clock Prescale Select bits
	QEI1CONbits.INTDIV=	0b000; //1:1 prescale value
	// External Count Gate Enable bit
	QEI1CONbits.GATEN = 0; // External gate signal disabled
	//Counter Control Mode Selection bits
	QEI1CONbits.CCM	  =	0b00; // Quadrature encoder mode
	
	QEI1IOC = 0x0000;
	//Position Counter Input Capture Enable bit
	QEI1IOCbits.QCAPEN = 0 ; // HOMEx input event (positive edge) does not trigger a position capture event
	//QEA/QEB/INDX/HOMEx Digital Filter Enable bit
	QEI1IOCbits.FLTREN = 0;  // Input Pin Digital filter is enabled
	//QEA/QEB/INDX/HOMEx Digital Input Filter Clock Divide Select bits
	QEI1IOCbits.QFDIV = 0; //1:1 clock divide
	
	QEI1STAT =	0x0000;
	QEI1STATbits.PCHEQIEN = 1;		//More than equal counter event interrupt
	QEI1STATbits.PCLEQIEN = 1;		//Less than equal counter event interrupt
	
	POS1CNTH = 0x0000;
	POS1CNTL = 0x0000;
	VEL1CNT = 0x0000;
	
	QEI1GECH = 0x0000;
	QEI1GECL = MAT_COUNT_MAX;
	
	QEI1LECH = 0xFFFF;
	QEI1LECL = 0xFFFF-MAT_COUNT_MAX;
	
	_QEI1IF=0;
	_QEI1IP=1;
	_QEI1IE=1;
	QEI1CONbits.QEIEN=1;

	Init_Timer1(FREQ_QEI);
}

void __attribute__((interrupt, auto_psv)) _QEI1Interrupt(void)
{
	limit_mat=1;
	_QEI1IF = 0;
}

