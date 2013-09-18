/************************************************************/
/* adc.c                                                    */
/* Library for the ADC module of dspic33E                   */
/*                                                          */
/* MCU : dspic33E                                           */
/*                                                          */
/* Author : David Khouya                                    */
/* Date	  :	XX/03/2012                                  */
/* Version: 1.0                                             */
/************************************************************/

/************************************************************/
/*                         INCLUDES                         */
/************************************************************/
#include "adc.h"
/************************************************************/


/************************************************************/
/*                      PUBLIC FUNCTIONS                    */
/************************************************************/
/*
ADC1Init
	Initialise the ADC1 module for internal voltage
        sensing (3V3 : AN14 and 5V : AN15)
        ADC is in alternate mode(scan channel A, scan channel B) and interrupt
        are activeted
	INPUT 		: 
				-None
				
	OUTPUT 		:	
				-None				
				

*/
/************************************************************/
void ADC1Init(void)
{

	/* Initialization of registers */
	AD1CON1 = 0x0000;
	AD1CON2 = 0x0000;
	AD1CON3 = 0x0000;
	AD1CON4 = 0x0000;
	AD2CON4 = 0x0000;
	AD1CHS123 = 0x0000;
	AD1CSSH = 0x0000;
	AD1CSSL = 0x0000;

	/* AD1CON1 */
	AD1CON1bits.FORM = 0b00;	// Ouput format : Integer
	AD1CON1bits.AD12B = 0;		// 10 bits ADC
	AD1CON1bits.SSRC = 0b111;	// auto-convert
	AD1CON1bits.SSRCG = 0;
	AD1CON1bits.SIMSAM = 0;         // Sample multiple channel individually iin sequence
	AD1CON1bits.ASAM = 1;           // Auto-start

	/* AD1CON2 */
	AD1CON2bits.CHPS = 0b00;        // Convert CH0
	AD1CON2bits.VCFG = 0b000;	// VREFH = AVDD AND VREFL = AVSS
	AD1CON2bits.ALTS = 1;           // MUXA & MUXB
	AD1CON2bits.BUFM = 0;           // Start filling the buffer from start address
	AD1CON2bits.SMPI = 0b00001;     //ADC Interrupt on 1st sample
	AD1CON2bits.CSCNA = 0;          // Input scan disabled

	/* AD1CON3*/
	AD1CON3bits.SAMC = 0b000011;     // 2 * TAD = 198.4 us
	AD1CON3bits.ADCS = 0xFF;        // TAD = 256 * TCY = 256 * (1/40e6) = ?
	AD1CON3bits.ADRC = 0;           // Clock Derived from System Clock : Fcy=FOSC/2 (40Mhz)

	/* AD1CON4 */
	AD1CON4bits.ADDMAEN = 0;        // DMA disabled

	/* Assign CH0 for MUXA */
	//AD1CHS0bits.CH0SA = 14;         //Select ANS14

        AD1CHS0bits.CH0SA = 5;         //Select ANS14
	AD1CHS0bits.CH0NA = 0;

	/* Assign CH0 for MUXB  */
	AD1CHS0bits.CH0SB = 15;         //Select ANS15
	AD1CHS0bits.CH0NB = 0;

	/* Assign CH1, CH2 and CH3 for MUXA */
	AD1CHS123bits.CH123SA = 0;
	AD1CHS123bits.CH123NA = 0;

	/* Assign CH1, CH2 and CH3 for MUXB */
	AD1CHS123bits.CH123SB = 0;  
	AD1CHS123bits.CH123NB = 0;

	_AD1IE = 1;
	_AD1IP = 1;
	_AD1IF = 0;

	AD1CON1bits.ADON = 1;
}
/************************************************************/
/*
ADC2Init
	Initialise the ADC2 module for sensor input(Weidmuller connector)
        ADC_SENSOR_2 : AN2
        ADC_SENSOR_3 : AN3
        ADC_SENSOR_4 : AN4
        ADC_SENSOR_5 : AN5
        The sampling is done simulataneously

	INPUT 		:
				-None

	OUTPUT 		:
				-None


*/
/************************************************************/
void ADC2Init(void)
{

	/* Initialization of registers */
	AD2CON1 = 0x0000;
	AD2CON2 = 0x0000;
	AD2CON3 = 0x0000;
	AD2CON4 = 0x0000;
	AD2CON4 = 0x0000;
	AD2CHS123 = 0x0000;
	AD2CSSL = 0x0000;

	/* AD1CON1 */
	AD2CON1bits.FORM = 0b00;	// Ouput format : Integer
	AD2CON1bits.SSRC = 0b111;	// auto-convert
	AD2CON1bits.SSRCG = 0;
	AD2CON1bits.SIMSAM = 1;         // Samples CH0, CH1, CH2, CH3 simultaneouly
	AD2CON1bits.ASAM = 1;           // Auto-start

	/* AD1CON2 */
	AD2CON2bits.CHPS = 0b11;        // Convert CH0, CH1, CH2, CH3
	AD2CON2bits.VCFG = 0b000;	// VREFH = AVDD AND VREFL = AVSS
	AD2CON2bits.ALTS = 0;           // Only MUXA
	AD2CON2bits.BUFM = 0;           // Start filling the buffer from start address
	AD2CON2bits.SMPI = 0b00011;     //ADC Interrupt on 1st sample
	AD2CON2bits.CSCNA = 0;          // Input scan disabled

	/* AD1CON3*/
	AD2CON3bits.SAMC = 0b11111;    // 256 * TAD = 198.4 us
	AD2CON3bits.ADCS = 0xFF;        // TAD = 256 * TCY = 256 * (1/40e6) = ?
	AD2CON3bits.ADRC = 0;           // Clock Derived from System Clock : Fcy=FOSC/2 (40Mhz)

	/* AD1CON4 */
	AD2CON4bits.ADDMAEN = 0;        // DMA disabled

	/* Assign CH0 for MUXA */
	AD2CHS0bits.CH0SA = 2;         //Select ANS2
	AD2CHS0bits.CH0NA = 0;

	/* Assign CH1, CH2 and CH3 for MUXA */
	AD2CHS123bits.CH123SA = 1;     //CH1 : AN3, CH2 : AN4, CH3 : AN5
	AD2CHS123bits.CH123NA = 0;

	_AD2IE = 1;
	_AD2IP = 3;
	_AD2IF = 0;

	AD2CON1bits.ADON = 1;
}
/************************************************************/


