#include "Setup_commande.h"

void Setup(void)
{

/* Initialisation de l'horloge Section 7.7 PLL (PHASE-LOCKED LOOP)*/
_PLLPRE=0;
_PLLPOST=0;
_PLLDIV=(unsigned int) (4.0f*FOSC_MHZ/(7.37f))-1;

while(OSCCONbits.LOCK !=1);		//boucle ok
/*****************************************************************/


/* Ports en Entrée 												 */
	TRISD=0xFFFF;
	TRISB=0xFFFF;
	TRISC=0xFFFF;	
/*****************************************************************/				
/* Ports en Sortie 												 */
	TRISF=0x0000;		
	TRISE=0x00F0;
/*****************************************************************/
/* Port c en digital 											 */
	ANSELC=0x0000;	
	ANSELE=0x0000;	
/*****************************************************************/
/* TRISx														 */		
	TRISFbits.TRISF2 = 1;                    //Input for CAN
	TRISFbits.TRISF3 = 0;                    //Output for CAN
/*****************************************************************/

 

init_ADC();
initialisation_UART();

/* Timer de type C (timer3) 									 */
T3CON = 0x0000; // Active le timer avec le boutton 1
T3CONbits.TSIDL = 0; 
T3CONbits.TCS = 0; // Select internal instruction cycle clock
T3CONbits.TGATE = 0; // Disable Gated Timer mode
T3CONbits.TCKPS = 0b11; // Select 1:256 Prescaler
TMR3 = 0x0000; // Clear timer register
//TMR3HLD = 0x0000; // Maintien de la valeur
PR3 = 100; // Load the period value
IPC2bits.T3IP = 7; // Set Timer 1 Interrupt Priority Level
IFS0bits.T3IF = 0; // Clear Timer 1 Interrupt Flag
IEC0bits.T3IE = 1; // Enable Timer1 interrupt
T3CONbits.TON = 1; // Active le timer
/*****************************************************************/
}
void initialisation_UART(void){

	/* Initialisation de l'UART, à mettre après l'initialisation du PIC  */
	//FOSC is the frequency of the CPU clock
	_RP85R =	0b000001;									//Connect RP85  to U1TX
	Init_UART((unsigned int)(FOSC/BAUDRATE/32.0f)-1,87);	//Connect RP87 to U1RX
}
void initialisation_CAN(void){

	/*IO settings*/
   	//Inputs (RPINxxbits.registre)
  	_C1RXR = 98;    //RP98 Pin 34
     	
   	//Outputs (RPORxxbits.registre)
  	_RP99R = 0b001110;  //RP99 Pin 33 

	init_CAN(CAN_NORMAL, 8, 2, 3, 7);

}
