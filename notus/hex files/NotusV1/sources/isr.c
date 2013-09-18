/************************************************************/
/* isr.c                                                    */
/* Library that contain interrupt routines for              */
/* Notus Sensor board                                       */
/*                                                          */
/* MCU : dspic33E                                           */
/*                                                          */
/* Author : David Khouya                                    */
/* Date	  :	25/02/2013                                  */
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
//const float Gain0Timer = 1.0f/(FOSC>>8); //Clock freq with 1:64 prescaller
//const float Gain1Timer = 1.0f/(FOSC>>10); //Clock freq with 1:64 prescaller
const float Gain0Timer = 1.0f/(FOSC/256.0f); //Clock freq with 1:64 prescaller
const float Gain1Timer = 1.0f/(FOSC/1024.0f); //Clock freq with 1:64 prescaller
/************************************************************/


/************************************************************/
/*			PUBLIC VARIABLES                    */
/************************************************************/
/*Timeout variables used with timer4*/
volatile uint8_t ubEepromWrite = 0U;
volatile uint8_t print = 0U;
volatile float fTimeStamp = 0U;

extern volatile sSensorValues_t* sSensorValues; //From notus.h
extern volatile sSensorRawFreq_t sSensorRawFreq;//From notus.h
extern volatile sSystemFlags_t sSystemFlags;    //From notus.h
/************************************************************/


/************************************************************/
/*			PRIVATE VARIABLES                   */
/************************************************************/

/************************************************************/

/************************************************************/
/*                     INTERRUPT FUNCTIONS                  */
/************************************************************/
void __attribute__((interrupt, auto_psv)) _T3Interrupt(void)
{
    sSystemFlags.CanTimeout = 1;
    _T3IF=0;
}
void __attribute__((interrupt, auto_psv)) _T5Interrupt(void)
{
    /*Timer used for display at 10 Hz*/
    if(!print) print = 1U;
    fTimeStamp += (1.0f/TIMER5_FREQ);
    LED_STAT3^=1;
    _T5IF=0;
}
void __attribute__((interrupt, auto_psv)) _T2Interrupt(void)
{
    /*Timer used at 1 Hz*/
    if(!ubEepromWrite) ubEepromWrite = 1U;
    _T2IF=0;
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





