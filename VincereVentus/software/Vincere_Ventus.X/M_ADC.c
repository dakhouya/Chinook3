/*
Propriété du 
Club Chinook/ETS
*/
/******************************************************************
					M_ADC.c
******************************************************************/

#include "M_ADC.h"
#include "p33EP512MU810.h"
#include "Global.h"
#include "M_UART.h"
#include "M_TMR.h"

void Init_ADC(void)
{
	/*Sample*/
	//ADC1BUF0 : AN0	(IBAT)
	//ADC1BUF1 : AN1	(Unused)
	//ADC1BUF2 : AN2	(DC MOTOR CURRENT)
	//ADC1BUF3 : AN3	(FB24V)

	/* Initialisation ADC*/	
	ANSELB=0x0000;
	ANSELBbits.ANSB0 = 1;	// IBAT
	ANSELBbits.ANSB1 = 1;	// Unused
	ANSELBbits.ANSB2 = 1;	// DC MOTOR CURRENT
	ANSELBbits.ANSB3 = 1;	// FB VOLTAGE BAT

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
	AD1CON1bits.SSRC = 0b111;       //PWM TRIG1 event
	AD1CON1bits.SSRCG = 0;
	AD1CON1bits.SIMSAM = 0; // Simultaneous sampling
	AD1CON1bits.ASAM = 1; // Auto-sample

	/* AD1CON2 */

	AD1CON2bits.CHPS = 0b00; // Convert CH0, CH1, CH2, CH3
	AD1CON2bits.VCFG = 0b000;	// VREFH = VREF+ AND VREFL = AVSS
	AD1CON2bits.ALTS = 0; // MUXA only
	AD1CON2bits.BUFM = 0; // Use 16 buffers
	AD1CON2bits.SMPI = 7; //ADC Interrupt on 8th sample
	AD1CON2bits.CSCNA = 0; // Input scan disabled
	
	/* AD1CON3*/
	AD1CON3bits.SAMC = 0b00011; // 2 * TAD = 10.24 us
	AD1CON3bits.ADCS = 0xFF; // TAD = 1 * TCY = 1 * (1/50e6) = ?
	AD1CON3bits.ADRC = 0; // Clock Derived from System Clock : Fcy=FOSC/2 (50Mhz)
	
	/* AD1CON4 */
	AD1CON4bits.ADDMAEN = 0; // DMA disabled
	
	/* Assign CH0 for MUXA */
	AD1CHS0bits.CH0SA = 0;
	AD1CHS0bits.CH0NA = 0; 
	
	/* Assign CH0 for MUXB */
	AD1CHS0bits.CH0SB = 0;
	AD1CHS0bits.CH0NB = 0; 
	
	/* Assign CH1, CH2 and CH3 for MUXA */
	AD1CHS123bits.CH123SA = 0;
	AD1CHS123bits.CH123NA = 0; 
	
	/* Assign CH1, CH2 and CH3 for MUXB */
	AD1CHS123bits.CH123SB = 0;  
	AD1CHS123bits.CH123NB = 0; 

        _AD1IP = 1;
	_AD1IF = 0;
	_AD1IE = 1;
        
	AD1CON1bits.ADON = 1;
}


