#include "p33EP512MC806.h"
#include "Setup_commande.h"

/*void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void)
{

	
	IFS0bits.T1IF = 0; //Clear Timer1 interrupt flag
}*/
/*void __attribute__((__interrupt__, no_auto_psv)) _T3Interrupt(void)
{
	if(count<=100) count++;
	Led4^=1;
	IFS0bits.T3IF = 0; *///Clear Timer3 interrupt flag
//}
