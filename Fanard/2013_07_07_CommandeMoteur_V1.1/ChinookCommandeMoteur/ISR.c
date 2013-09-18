#include "p33EP512MC806.h"
#include "Setup_commande.h"

volatile extern can_time_out;
volatile extern can_envoie_auto;

void __attribute__((__interrupt__, no_auto_psv)) _T5Interrupt(void)
{

	can_envoie_auto++;
	Led1^=1;
	_T5IF = 0;// Clear Timer2 interrupt
//	TMR5 = 0;			//Reset the CAN bus timeout counter

}

void __attribute__((__interrupt__, no_auto_psv)) _T3Interrupt(void)
{
	can_time_out = 1;
	Led3^=1;
	IFS0bits.T3IF = 0; 						//Clear Timer3 interrupt flag
}
