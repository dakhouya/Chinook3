/************************************************************/
/* spi.c                                                   	*/
/* Functions related SPI serial communication protocol      */
/*															*/
/* MCU : dspic33EP512MC806									*/
/*                                                          */
/* Author : Mikael Ducharme                                 */
/* Date	  : June 2013                                     	*/
/************************************************************/


/**********************    INCLUDE    ***********************/
#include "spi.h"
/************************************************************/


void spi_init_as1107_u1(void){

//	INITIALISATION DES PINS
SPI2CON2 = 0;
SPI2CON1 = 0;
SPI2STAT = 0;
_TRISG9 = 0;
_RG9 = 0;

// SPI2CON1 Register Settings

SPI2CON1bits.DISSCK = 0; 	// Internal serial clock is enabled
SPI2CON1bits.DISSDO = 0; 	// SDOx pin is controlled by the module
SPI2CON1bits.MODE16 = 1;	// Communication is word-wide (16 bits)
SPI2CON1bits.SMP = 0; 		// Input data is sampled at the middle of data output time
SPI2CON1bits.CKE = 0;		// Serial output data changes on transition from
							// idle clock state to active clock state
SPI2CON1bits.CKP = 0; 		// Idle state for clock is a low-level;
							// active state is a high-level

SPI2CON1bits.MSTEN = 1; 	// Master mode enabled

SPI2CON1bits.PPRE = 0b00;	//Primary Prescale 64:1
SPI2CON1bits.SPRE = 0b110;	//Secondary Prescale 2:1

// SPI2STAT Register Settings

SPI2STATbits.SPIEN = 1;		// Enable SPI module
	
}

void spi_init_as1107_u2(void){

//	INITIALISATION DES PINS
SPI3CON2 = 0;
SPI3CON1 = 0;
SPI3STAT = 0;

_RP82R = 0b011111;			// Remap SDO3 to pin RP65
_RP84R = 0b100000;			// Remap SCK3 to pin RP65

_TRISE3 = 0;
_RE3 = 0;

// SPI3CON1 Register Settings

SPI3CON1bits.DISSCK = 0; 	// Internal serial clock is enabled
SPI3CON1bits.DISSDO = 0; 	// SDOx pin is controlled by the module
SPI3CON1bits.MODE16 = 1;	// Communication is word-wide (16 bits)
SPI3CON1bits.SMP = 0; 		// Input data is sampled at the middle of data output time
SPI3CON1bits.CKE = 0;		// Serial output data changes on transition from
							// idle clock state to active clock state
SPI3CON1bits.CKP = 0; 		// Idle state for clock is a low-level;
							// active state is a high-level

SPI3CON1bits.MSTEN = 1; 	// Master mode enabled

SPI3CON1bits.PPRE = 0b00;	//Primary Prescale 64:1
SPI3CON1bits.SPRE = 0b110;	//Secondary Prescale 2:1

// SPI3STAT Register Settings

SPI3STATbits.SPIEN = 1;		// Enable SPI module
	
}


void spi_init_lcd(void){

//	INITIALISATION DES PINS
_RP66R = 0b000110;			// Remap SCK1 to pin RP66
_RP67R = 0b000101;			// Remap SDO1 to pin RP67

ODCDbits.ODCD1 = 1; 		// SS is Open Drain
ODCDbits.ODCD2 = 1;			// SCK1 is Open Drain
ODCDbits.ODCD3 = 1;			// SDO1 is Open Drain

_TRISD1 = 0;				// Pin D4 output for CS

SPI1CON2 = 0;				// Init 0
SPI1CON1 = 0;				// Init 0
SPI1STAT = 0;				// Init 0

// SPI1CON1 Register Settings

SPI1CON1bits.DISSCK = 0; 	// Internal serial clock is enabled
SPI1CON1bits.DISSDO = 0; 	// SDOx pin is controlled by the module
SPI1CON1bits.MODE16 = 0;	// Communication is byte-wide (8 bits)
SPI1CON1bits.SMP = 0; 		// Input data is sampled at the middle of data output time
SPI1CON1bits.CKE = 0;		// Serial output data changes on transition from 
							// active clock state to Idle clock state
SPI1CON1bits.CKP = 1; 		// Idle state for clock is a high-level;
							// active state is a low-level

SPI1CON1bits.MSTEN = 1; 	// Master mode enabled

SPI1CON1bits.PPRE = 0b00;	//Primary Prescale 64:1
SPI1CON1bits.SPRE = 0b000;	//Secondary Prescale 8:1

// SPI1CON2 Register Settings

SPI1CON2bits.SPIBEN = 1;

// SPI1STAT Register Settings

SPI1STATbits.SPIEN = 1;		// Enable SPI module
}

