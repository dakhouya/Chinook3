/************************************************************/
/* notus.h                                                  */	
/* Application library for Notus Sensor board               */
/*                                                          */
/* MCU : dspic33E                                           */
/*                                                          */
/* Author : David Khouya                                    */
/* Date	  :	XX/03/2013                                  */
/* Version: 1.0                                             */
/************************************************************/

/************************************************************/
#ifndef _NOTUS_MODULE_
#define _NOTUS_MODULE_
/************************************************************/

/************************************************************/
/*			INCLUDES                            */
/************************************************************/
#include "hardware_profile.h"
#include "globaldef.h"
#include "p33EP512MC806.h"
#include "MMA8452.h"
#include "M_TMR.h"
#include "adc.h"
/************************************************************/


/************************************************************/
/*                  STRUCTURE DEFINITIONS                   */
/************************************************************/

/*General structure to stock sensor values*/
typedef struct Sensor
{
    /*Onboard Sensing*/
    float fSens5V0;
    float fSens3V3;
        
    /*Free inputs*/
    float fRPM0;
    float fAdc0;
    float fAdc1;
        
    /*Used inputs*/
    float fTrust;
    float fWheelRPM;
    float fTurbineRPM;
    float fWindSpeed;
    float fWindDir;
        
    sAxis_t sAccelerometer0;
    sAxis_t sAccelerometer1;
}sSensorValues_t;

typedef struct SensorRawFreq
{
    float fRPM0Freq;
    float fWheelFreq;
    float fTurbineFreq;
    float fWindFreq;
}sSensorRawFreq_t;
/************************************************************/

/************************************************************/
/*                      MACRO DEFINITIONS                   */
/************************************************************/
/*Number of tooth on the gear*/
#define GEARTOOTH   20.0f
/************************************************************/
/*                      PUBLIC PROTOTYPES                   */
/************************************************************/
void set_clk(void);
void NotusInitIOs(void);
void RPMInit(void);
void ADCInit(void);
int8_t DataStructInit(sSensorValues_t*);

int8_t Get3V3Voltage(sSensorValues_t*);
int8_t Get5V0Voltage(sSensorValues_t*);
int8_t GetTrust(void);
int8_t GetWindDirection(void);
int8_t GetWindSpeed(void);
int8_t GetTurbineRPM(void);
int8_t GetWheelRPM(void);
int8_t GetsAccelerometer0(sSensorValues_t*);
int8_t GetsAccelerometer1(sSensorValues_t*);
/************************************************************/


/************************************************************/
#endif
/************************************************************/
