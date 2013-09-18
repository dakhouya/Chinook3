/************************************************************/
/* notus.h                                                  */	
/* Application library for Notus Sensor board               */
/*                                                          */
/* MCU : dspic33E                                           */
/*                                                          */
/* Author : David Khouya                                    */
/* Date	  :	11/06/2013                                  */
/************************************************************/

/************************************************************/
#ifndef _NOTUS_MODULE_
#define _NOTUS_MODULE_
/************************************************************/

/************************************************************/
/*			INCLUDES                            */
/************************************************************/
/*Global definitions*/
#include "hardware_profile.h"
#include "globaldef.h"
#include "p33EP512MC806.h"
/*Peripherals*/
#include "Peripherals/M_TMR.h"
#include "Peripherals/adc.h"
#include "Peripherals/i2c.h"
#include "Peripherals/uart.h"
#include "Peripherals/can.h"
/*Devices*/
#include "Devices/MMA8452.h"
#include "Devices/ds1338.h"
#include "Devices/cat24c256.h"
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

    /*RTC*/
    ds1338_s ds1338;

    /*EEPROM*/
    sCat24c256_t sCat24c256;

}sSensorValues_t;

typedef struct SensorRawFreq
{
    float fRPM0Freq;
    float fWheelFreq;
    float fTurbineFreq;
    float fWindFreq;
}sSensorRawFreq_t;

typedef struct
{
    unsigned CanTimeout     :1;
    unsigned CanError       :1;
    unsigned TurbineTimeout :1;
    unsigned WheelTimeout   :1;
    unsigned WindTimeout    :1;
}sSystemFlags_t;
/************************************************************/

/************************************************************/
/*                      MACRO DEFINITIONS                   */
/************************************************************/
/*Firmware version*/
#define NOTUS_VERSION   "2013.08.21"

/*Number of tooth on the gear*/
#define GEARTOOTH_WHEEL   20.0f
#define GEARTOOTH_TURBINE   30.0f

/*EEPROM data address*/
#define EEPROM_GEAR_ADDRESS 0x1111
#define EEPROM_TURBINE_POSITION_ADDRESS0 0x0050
#define EEPROM_TURBINE_POSITION_ADDRESS1 0x0051
#define EEPROM_TURBINE_POSITION_ADDRESS2 0x0052
#define EEPROM_TURBINE_POSITION_ADDRESS3 0x0053
#define EEPROM_PITCH_ADDRESS0 0x2222
#define EEPROM_PITCH_ADDRESS1 0x2223
#define EEPROM_PITCH_ADDRESS2 0x2224
#define EEPROM_PITCH_ADDRESS3 0x2225
/************************************************************/
/*                      PUBLIC PROTOTYPES                   */
/************************************************************/
void set_clk(void);
void NotusInitIOs(void);
void NotusInitPeripherals(void);
void NotusInitDevices(void);
void RPMInit(void);
void ADCInit(void);
int8_t DataStructInit(sSensorValues_t* sSensorValues);

/*Get values*/
int8_t Get3V3Sensing(sSensorValues_t* sSensorValues);
int8_t Get5V0Sensing(sSensorValues_t* sSensorValues);
int8_t GetTrust(sSensorValues_t* sSensorValues);
int8_t GetWindDirection(sSensorValues_t* sSensorValues);
int8_t GetWindSpeed(sSensorValues_t* sSensorValues);
int8_t GetTurbineRPM(sSensorValues_t* sSensorValues);
int8_t GetWheelRPM(sSensorValues_t* sSensorValues);
int8_t GetsAccelerometer0(sSensorValues_t* sSensorValues);

/*Debug & Print functions*/
void PrintNotusVersion(void);
uint8_t PrintVoltageSensing(sSensorValues_t* sSensorValues);
uint8_t PrintTrust(sSensorValues_t* sSensorValues);
uint8_t PrintWindDirection(sSensorValues_t* sSensorValues);
uint8_t PrintWindSpeed(sSensorValues_t* sSensorValues);
uint8_t PrintTurbineRPM(sSensorValues_t* sSensorValues);
uint8_t PrintWheelRPM(sSensorValues_t* sSensorValues);
uint8_t PrintAccelerometer0(sSensorValues_t* sSensorValues);
uint8_t PrintTime(sSensorValues_t* sSensorValues);
uint8_t PrintTurbineFreq(sSensorRawFreq_t* sSensorRawFreq);
uint8_t PrintWheelFreq(sSensorRawFreq_t* sSensorRawFreq);
uint8_t PrintTurbineFreq(sSensorRawFreq_t* sSensorRawFreq);
uint8_t PrintWindFreq(sSensorRawFreq_t* sSensorRawFreq);
void PrintEeprom(void);

uint8_t WriteGearEeprom(uint8_t ubGear);
uint8_t WriteTurbineDirEeprom(float fDir);
uint8_t WritePitchEeprom(float fPitch);
uint8_t ReadGearEeprom(void);
float ReadTurbineDirEeprom(void);
float ReadPitchEeprom(void);
/************************************************************/


/************************************************************/
#endif
/************************************************************/
