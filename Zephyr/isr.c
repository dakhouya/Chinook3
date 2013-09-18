/************************************************************/
/* isr.c                                                    */
/* Library that contain interrupt routines for              */
/* Zephyr Sensor board                                      */
/*                                                          */
/* MCU : dspic33E                                           */
/*                                                          */
/* Author : Mikael Ducharme                                 */
/* Date	  :	16/06/2013                                  */
/************************************************************/

/************************************************************/
/*                          INCLUDES                        */
/************************************************************/
#include "p33EP512MC806.h"
#include "global.h"
/************************************************************/



/************************************************************/
/*					PUBLIC VARIABLES               			*/
/************************************************************/
/*Timeout variable used with timer3*/
volatile unsigned char CANTimeout = 0U;

/*Display variable used with timer5*/
volatile unsigned char print = 0U;

/*Display variable used with timer7*/
volatile int config = 0;
/************************************************************/

/************************************************************/
/*                     INTERRUPT FUNCTIONS                  */
/************************************************************/
void __attribute__((interrupt, auto_psv)) _T3Interrupt(void)
{
    CANTimeout = 1U;
    _T3IF=0;
}

void __attribute__((interrupt, auto_psv)) _T5Interrupt(void)
{
    /*Timer used for display at 10 Hz*/
    if(!print) print = 1U;
    _T5IF=0;
}

void __attribute__((interrupt, auto_psv)) _T7Interrupt(void)
{
    /*Timer used for display at 1 Hz*/
    config++; 
    _T7IF=0;
}
/************************************************************/







