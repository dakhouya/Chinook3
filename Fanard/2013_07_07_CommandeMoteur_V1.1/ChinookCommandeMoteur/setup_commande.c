#include "Setup_commande.h"

void Setup(void)
{

/*****************************************************************/
/* Ports en Entrée 												 */
	TRISD=0xFFFF;
	TRISB=0xFFFF;
	TRISC=0xFFFF;
	TRISG=0xFFFF;	
/*****************************************************************/				
/* Ports en Sortie 												 */
	TRISF=0x0000;		
	TRISE=0x00F0;
/*****************************************************************/
/* Port c en digital 											 */
	ANSELC=0x0000;	
	ANSELE=0x0000;	
/*****************************************************************/
/* TRISx pour le can											 */		
	TRISFbits.TRISF2 = 1;                    //Input for CAN
	TRISFbits.TRISF3 = 0;                    //Output for CAN
/*****************************************************************/
/* TRISx pour le BUZZER											 */
	TRISBbits.TRISB1 = 0;                    //Input for CAN
/*****************************************************************/

/* Fonction d'initialisation du PIC */
initialisation_CLK();
init_ADC();
initialisation_UART();


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
void initialisation_CLK(void){
	/* Initialisation de l'horloge Section 7.7 PLL (PHASE-LOCKED LOOP)*/
	_PLLPRE=0;
	_PLLPOST=0;
	_PLLDIV=(unsigned int) (4.0f*FOSC_MHZ/(7.37f))-1;
	
	while(OSCCONbits.LOCK !=1);		//boucle ok
} 