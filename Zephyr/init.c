/**********************    INCLUDE    ***********************/
#include "p33EP512MC806.h"
#include "global.h"
/************************************************************/


/************************************************************/
/*Function: set_clk()										*/
/*															*/
/*Output: None												*/
/*															*/
/*Overview: This function sets up the system clock			*/
/*															*/
/*Note: None												*/
/************************************************************/

void set_clk(void)
{					//datasheet section 7 p.21
_PLLPRE=0;
_PLLPOST=0;
_PLLDIV=(unsigned int) (4.0f*FOSC_MHZ/(7.37f))-1;
//OSCTUNbits.TUN-=3;
while(OSCCONbits.LOCK !=1);
}