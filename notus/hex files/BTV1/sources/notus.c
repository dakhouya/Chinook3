/************************************************************/
/* notus.c                                                  */
/* Application library for Notus Sensor board               */
/*                                                          */
/* MCU : dspic33E                                           */
/*                                                          */
/* Author : David Khouya                                    */
/* Date	  :	XX/01/2013                                  */
/* Version: 1.0                                             */
/************************************************************/

/************************************************************/
/*                          INCLUDES                        */
/************************************************************/
#include "notus.h"
/************************************************************/

/************************************************************/
/*		        PUBLIC VARIABLES                    */
/************************************************************/
volatile sSensorValues_t sSensorValues;
volatile sSensorRawFreq_t sSensorRawFreq;
/************************************************************/

/************************************************************/
/*                      PUBLIC FUNCTIONS                    */
/************************************************************/
/************************************************************/
/*
set_clk
	Set system clock with PLL

	INPUT 		:
				-None

	OUTPUT 		:
				-None


*/
/************************************************************/
void set_clk(void)
{
/*datasheet section 7 p.21*/
_PLLPRE=0;
_PLLPOST=0;
_PLLDIV=(unsigned int) (4.0f*FOSC_MHZ/(7.37f))-1;
while(OSCCONbits.LOCK !=1);
}

/************************************************************/
/*
NotusInitIOs
	Initialise all the IOs of the Sensor board

	INPUT 		: 
				-None
				
	OUTPUT 		:	
				-None				
				

*/
/************************************************************/
void NotusInitIOs(void)
{
	/*Initialise digital IOs*/
	CONF_LED_STAT0 = OUTPUT;
	CONF_LED_STAT1 = OUTPUT;
	CONF_LED_STAT2 = OUTPUT;
	CONF_LED_STAT3 = OUTPUT;
	
	CONF_CANRX = INPUT; 
	CONF_CANTX = OUTPUT; 
	
	CONF_U1RX = INPUT;
	CONF_U1TX = OUTPUT;
	CONF_U2RX = INPUT;
	CONF_U2TX = OUTPUT;
	CONF_U3RX = INPUT;
	CONF_U3TX = OUTPUT;
	
	CONF_SCL = OUTPUT;
	CONF_SCK = OUTPUT;
	CONF_SDI = INPUT;
	CONF_SDO = OUTPUT;
	
	CONF_EEPROM_WP = OUTPUT;
	CONF_SD_CARD_CS = OUTPUT; 
	CONF_RS232_RS485_SEL = OUTPUT;

	/*Activate the port B analog inputs*/
	ANSELB = 0x0000;

	/*+3V3_SENSE*/
	ANSELBbits.ANSB14 = 1;

	/*+5V_SENSE*/
	ANSELBbits.ANSB15 = 1;

	/*ADC-OPAMP*/
	ANSELBbits.ANSB2 = 1;
	ANSELBbits.ANSB3 = 1;
	ANSELBbits.ANSB4 = 1;
	ANSELBbits.ANSB5 = 1;

	/*Peripheral mapping*/
	/*UART1*/
	RPOR8bits.RP98R = 0x01;         //UART1TX : PIN RP98
	RPINR18bits.U1RXR = 99; 	//UART1RX : PIN RP99

	/*UART2*/
	RPOR7bits.RP97R = 0x03;         //UART2TX : PIN RP97
	RPINR19bits.U2RXR = 96; 	//UART2RX : PIN RP96

	/*CAN1*/
	RPOR3bits.RP70R = 0x0E;         //CANTX : PIN RP70
	RPINR26bits.C1RXR = 71;		//CANRX : PIN RP71

	/*DIGITAL Sensor(RPM)with associated pull-up*/
	CONF_SIGNAL_IN0 = INPUT;
	CNPUDbits.CNPUD0 = 1;
	CONF_SIGNAL_IN1 = INPUT;
	CNPUDbits.CNPUD1 = 1;
	CONF_SIGNAL_IN2 = INPUT;
	CNPUDbits.CNPUD2 = 1;
	CONF_SIGNAL_IN3 = INPUT;
	CNPUDbits.CNPUD3 = 1;

        /*Init the accelerometer*/
        //MMA8452Init();
}
/************************************************************/
/*
RPMInit
	Initialise the timers 6-7-8-9 in gated mode for 
	the acquisition of the RPM on SIGNAL_IN0, SINGNAL_IN1,
	SIGNAL_IN2 and SIGNAL_IN3

	INPUT 		: 
				-None
				
	OUTPUT 		:	
				-None				
				

*/
/************************************************************/
void RPMInit(void)
{
    Init_Timer6();
    Init_Timer7();
    Init_Timer8();
    Init_Timer9();
}

/************************************************************/
/*
ADCInit
	Initialise the ADC1 and ADC2 in interrupt mode
        ADC1 samples AN14 : SENSE_3V3 and AN15 : SENSE_5V0
        ADC2 samples AN2 to AN5 in simulatanious mode
	INPUT 		: 
				-None
				
	OUTPUT 		:	
				-None				
				

*/
/************************************************************/
void ADCInit(void)
{
    ADC1Init();
    ADC2Init();
}

/************************************************************/
/*
DataStructInit
	Initialise the datastructure to 0 on all values
        Return -1 when there's an error
	INPUT 		:
				-sSensorValues_t* (Sensor data structure)

	OUTPUT 		:
				-None


*/
/************************************************************/
int8_t DataStructInit(sSensorValues_t* sSensorValues)
{
    int8_t bError = 0;

    /*Validity Check*/
    if(sSensorValues == NULL)
    {
        bError = -1;
    }

    /*Clear data structure*/
    else
    {
        /*Onboard Sensing*/
        sSensorValues->fSens5V0 = 0.0f;
        sSensorValues->fSens3V3 = 0.0f;

        /*Free inputs*/
	sSensorValues->fRPM0 = 0.0f;
        sSensorValues->fAdc0 = 0.0f;
	sSensorValues->fAdc1 = 0.0f;

        /*Used inputs*/
        sSensorValues->fTrust = 0.0f;
	sSensorValues->fWheelRPM = 0.0f;
	sSensorValues->fTurbineRPM = 0.0f;
	sSensorValues->fWindSpeed = 0.0f;
        sSensorValues->fWindDir = 0.0f;

	bError = MMA8452InitStruct(&sSensorValues->sAccelerometer0);
	bError = MMA8452InitStruct(&sSensorValues->sAccelerometer1);
    }

    return bError;
}

/************************************************************/
/*
Get3V3Sensing
        Get the voltage value on the pin 3V3_SENSE : AN14
        AN14 is connected to 3V3 by a 1K-1K voltage divider
        Return -1 when there's an error
	INPUT 		: 
				-sSensorValues_t* (Sensor data structure)
				
	OUTPUT 		:	
				-float (voltage)				
				
*/
/************************************************************/
int8_t Get3V3Sensing(sSensorValues_t* sSensorValues)
{
    int8_t bError = 0;
    sSensorValues->fSens3V3 = (ADC1BUF0*2.0f)/1023.0f*3.3f;
    return bError;
}
/************************************************************/
/*
Get5V0Sensing
        Get the voltage value on the pin 5V0_SENSE : AN15
        AN15 is connected to 5V0 by a 1K-3K voltage divider
        Return -1 when there's an error
	INPUT 		:
				-sSensorValues_t* (Sensor data structure)

	OUTPUT 		:
				-int8_t (Error)

*/
/************************************************************/
int8_t Get5V0Voltage(sSensorValues_t* sSensorValues)
{
    int8_t bError = 0;
    sSensorValues->fSens5V0 = ADC1BUF1*4.0f/1023.0f*3.3f;
    return bError;
}

/************************************************************/
/*
GetTrust
        Get the trust value in Lb from AN5
        Return -1 when there's an error
	INPUT 		:
				-sSensorValues_t* (Sensor data structure)

	OUTPUT 		:
				-int8_t (Error)

*/
/************************************************************/
int8_t GetTrust(void)
{
    int8_t bError = 0;
    /*Get trust value -> 4,4482216153N = 1Lbf*/
    sSensorValues.fTrust = (ADC2BUF3*200.0f/1023.0f);
    return bError;
}

/************************************************************/
/*
GetWindDirection
        Get the wind direction in degres
                   180
                90  +  270
                  0/360
        The wind direction is sample on AN3 pin
        Return -1 when there's an error
	INPUT 		:
				-sSensorValues_t* (Sensor data structure)

	OUTPUT 		:
				-int8_t (Error)

*/
/************************************************************/
int8_t GetWindDirection(void)
{
    int8_t bError = 0;
    /*Get the direction from 0 to 360 degres*/
    sSensorValues.fWindDir = (ADC2BUF1*360.0f/1023.0f);
    return bError;
}

/************************************************************/
/*
GetWindSpeed

        Return -1 when there's an error
	INPUT 		:
				-sSensorValues_t* (Sensor data structure)

	OUTPUT 		:
				-int8_t (Error)

*/
/************************************************************/
int8_t GetWindSpeed(void)
{
    int8_t bError = 0;
    /*From davis instrument spec : V(mph)=(2.25/T) and V(m/s) = V(mph)*0.44704*/
    sSensorValues.fWindSpeed = (2.25/(1/sSensorRawFreq.fWindFreq))*0.44704;
    return bError;
}

/************************************************************/
/*
GetTurbineRPM

        Return -1 when there's an error
	INPUT 		:
				-sSensorValues_t* (Sensor data structure)

	OUTPUT 		:
				-int8_t (Error)

*/
/************************************************************/
int8_t GetTurbineRPM(void)
{
    int8_t bError = 0;
    sSensorValues.fTurbineRPM = (sSensorRawFreq.fTurbineFreq*60.0f)/GEARTOOTH;
    return bError;
}

/************************************************************/
/*
GetWheelRPM

        Return -1 when there's an error
	INPUT 		:
				-sSensorValues_t* (Sensor data structure)

	OUTPUT 		:
				-int8_t (Error)

*/
/************************************************************/
int8_t GetWheelRPM(void)
{
    int8_t bError = 0;
    sSensorValues.fTurbineRPM = (sSensorRawFreq.fWheelFreq*60.0f)/GEARTOOTH;
    return bError;
}

/************************************************************/
/*
GetsAccelerometer0
        Get the data from the onboard Accelerometer
        Return -1 when there's an error
	INPUT 		:
				-sSensorValues_t* (Sensor data structure)

	OUTPUT 		:
				-int8_t (Error)

*/
/************************************************************/
int8_t GetsAccelerometer0(sSensorValues_t* sSensorValues)
{
    int8_t bError = 0;
    MMA8452GetAxis(&sSensorValues->sAccelerometer0);
    return bError;
}

/************************************************************/
/*
GetsAccelerometer1

        Return -1 when there's an error
	INPUT 		:
				-sSensorValues_t* (Sensor data structure)

	OUTPUT 		:
				-int8_t (Error)

*/
/************************************************************/
int8_t GetsAccelerometer1(sSensorValues_t* sSensorValues)
{
    int8_t bError = 0;

    return bError;
}


