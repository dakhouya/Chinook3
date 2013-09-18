/************************************************************/
/* global.c                                            		*/
/* Global functions used in the project (delays, timers...) */
/*															*/
/* MCU : dspic33EP512MC806									*/
/*                                                          */
/* Author : Mikael Ducharme                                 */
/* Date	  : June 2013                                     	*/
/************************************************************/

/**********************    INCLUDE    ***********************/
#include "global.h"
/************************************************************/


void delay300us(void){
	unsigned int j;
	for(j=0;j<=1300; j++){
	Nop();
	}
}


void delay600us(void){
	unsigned int j;
	for(j=0;j<=4000; j++){
	Nop();
	}
}