/************************************************************/
/* isr.c                                                    */
/* Library that contain interrupt routines for              */
/* Notus Sensor board                                       */
/*                                                          */
/* MCU : dspic33E                                           */
/*                                                          */
/* Author : David Khouya                                    */
/* Date	  :	25/02/2013                                  */
/* Version: 1.0                                             */
/************************************************************/

/************************************************************/
/*                          INCLUDES                        */
/************************************************************/
#include "p33EP512MC806.h"
#include "globaldef.h"
#include "hardware_profile.h"
#include "notus.h"
/************************************************************/

/************************************************************/
/*                      MACRO DEFINITIONS                   */
/************************************************************/
const float Gain0Timer = 1.0f/(FOSC>>8); //Clock freq with 1:64 prescaller
const float Gain1Timer = 1.0f/(FOSC>>10); //Clock freq with 1:64 prescaller
/************************************************************/


/************************************************************/
/*			PUBLIC VARIABLES                    */
/************************************************************/
volatile uint8_t print = 0U;
volatile float fTimeStamp = 0U;

extern volatile sSensorValues_t* sSensorValues;
extern volatile sSensorRawFreq_t sSensorRawFreq;
/************************************************************/


/************************************************************/
/*			PRIVATE VARIABLES                   */
/************************************************************/

/************************************************************/

/************************************************************/
/*                     INTERRUPT FUNCTIONS                  */
/************************************************************/
void __attribute__((interrupt, auto_psv)) _T5Interrupt(void)
{
    /*Timer used for display at 10 Hz*/
    if(!print) print = 1U;
    fTimeStamp += (1.0f/TIMER5_FREQ);
    LED_STAT3^=1;
    _T5IF=0;
}
/************************************************************/
void __attribute__((interrupt, auto_psv)) _T6Interrupt(void)
{
    sSensorRawFreq.fTurbineFreq = 1.0f/((TMR6+1.0f)*Gain0Timer);
    TMR6=0; //Clear timer register
    _T6IF=0;
}
/************************************************************/
void __attribute__((interrupt, auto_psv)) _T7Interrupt(void)
{
    sSensorRawFreq.fRPM0Freq = 1.0f/((TMR7+1.0f)*Gain0Timer);
    TMR7=0; //Clear timer register
    _T7IF=0;
}
/************************************************************/
void __attribute__((interrupt, auto_psv)) _T8Interrupt(void)
{

    sSensorRawFreq.fWindFreq = 1.0f/((TMR8+1.0f)*Gain1Timer);
    TMR8=0; //Clear timer register
    _T8IF=0;
}
/************************************************************/
void __attribute__((interrupt, auto_psv)) _T9Interrupt(void)
{
    sSensorRawFreq.fWheelFreq = 1.0f/((TMR9+1.0f)*Gain0Timer);
    TMR9=0; //Clear timer register
    _T9IF=0;
}
/************************************************************/
void __attribute__((interrupt, auto_psv)) _AD1Interrupt(void)
{
    _AD1IF = 0;
}
/************************************************************/
void __attribute__((interrupt, auto_psv)) _AD2Interrupt(void)
{
    _AD2IF = 0;
}
/************************************************************/


