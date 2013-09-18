/************************************************************/
/* notus.c                                                  */
/* Application library for Notus Sensor board               */
/*                                                          */
/* MCU : dspic33E                                           */
/*                                                          */
/* Author : David Khouya                                    */
/* Date	  :	11/06/2013                                  */
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
volatile sSystemFlags_t sSystemFlags;
/*Reset counter values*/
uint8_t ubResetWDWindSpeed = 0;
uint8_t ubResetWDTurbineSpeed = 0;
uint8_t ubResetWDWheelSpeed = 0;
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

        Nop();
	CONF_CANRX = INPUT;
        Nop();
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
        ANSELC = 0x0000;
        ANSELD = 0x0000;
        ANSELE = 0x0000;


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
	/*CAN1*/
	RPINR26bits.C1RXR = 71;         //CANRX : PIN RP71
	RPOR3bits.RP70R = 0b001110;     //CANTX : PIN RP70



	/*UART1*/
	RPOR8bits.RP98R = 0x01;         //UART1TX : PIN RP98
	RPINR18bits.U1RXR = 99; 	//UART1RX : PIN RP99


	/*UART2*/
	RPOR7bits.RP97R = 0x03;         //UART2TX : PIN RP97
	RPINR19bits.U2RXR = 96; 	//UART2RX : PIN RP96

	/*DIGITAL Sensor(RPM)with associated pull-up*/
	CONF_SIGNAL_IN0 = INPUT;
	CNPUDbits.CNPUD0 = 1;
	CONF_SIGNAL_IN1 = INPUT;
	CNPUDbits.CNPUD1 = 1;
	CONF_SIGNAL_IN2 = INPUT;
	CNPUDbits.CNPUD2 = 1;
	CONF_SIGNAL_IN3 = INPUT;
	CNPUDbits.CNPUD3 = 1;
}

/************************************************************/
/*
NotusInitPeripherals
        Initialize all Notus Peripherals
        - Timers    6-7-8-9
        - ADC       1-2
        - I2C       1
        - UART      1 
        -CAN        1

	INPUT 		: 
				-None
				
	OUTPUT 		:	
				-None				
				

*/
/************************************************************/
void NotusInitPeripherals(void)
{
    /*UART Variables*/
    sUartParam sParam = {BRGH_HIGH_SPEED,0,UART_8BITS_NOPARITY,UART_1STOP_BIT,UART1_SPEED};

    /*Uart*/
    UartInit(UART_1,&sParam);
    UartInitPortStruc(UART_1, NULL,NULL);
    UartTxEnable(UART_1, ENABLE);
    UartInterruptTxEnable(UART_1, CHAR_N_BUFFER_EMPTY,2,ENABLE);
    UartInterruptRxEnable(UART_1, CHAR_RECEIVE,3,ENABLE);
    UartTxFrame(UART_1, "\n\rNotus initialization \n\r", 25);
    UartTxFrame(UART_1, "UART 1 Started \n\r", 17);

    /*Timers*/
    RPMInit();
    Init_Timer5(TIMER5_FREQ);/*Display timer and reset values*/
    Init_Timer3(TIMER3_FREQ);/*CAN timeout timer*/
    Init_Timer2(TIMER2_FREQ);/*Write in eeprom*/
    UartTxFrame(UART_1, "TIMER 1, 3 & 5 Started \n\r", 22);

    /*ADC*/
    ADCInit();
    UartTxFrame(UART_1, "ADC 1 & 2 Started \n\r", 20);

    /*I2C*/
    I2C_InterruptEnable(I2C_1,5,DISABLE);
    I2C_Init(I2C_1,I2C_SPEED);
    UartTxFrame(UART_1, "I2C 1 Started \n\r", 16);

    /*CAN*/
    init_CAN(CAN_NORMAL, 8, 0, 1, 5);
    UartTxFrame(UART_1, "CAN 1 Started \n\r", 16);
}

/************************************************************/
/*
NotusInitDevices
        Initialize all Notus Devices
        - Accelerometer 1

	INPUT 		:
				-None

	OUTPUT 		:
				-None


*/
/************************************************************/
void NotusInitDevices(void)
{
    Initcat24c256(&(sSensorValues.sCat24c256), 0xA0, I2C_1);
    /*Init the accelerometer*/
    MMA8452Init();
    /*Init eeprom*/
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

        sSensorValues->ds1338.day = 0x00;
        sSensorValues->ds1338.month = 0x00;
        sSensorValues->ds1338.year = 0x00;
        sSensorValues->ds1338.hours = 0x00;
        sSensorValues->ds1338.minutes = 0x00;
        sSensorValues->ds1338.seconds = 0x00;
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
    sSensorValues->fSens3V3 = ADC1BUF0*2.0f/1023.0f*3.3f;
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
int8_t Get5V0Sensing(sSensorValues_t* sSensorValues)
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
int8_t GetTrust(sSensorValues_t* sSensorValues)
{
    int8_t bError = 0;
    /*Get trust value -> 4,4482216153N = 1Lbf*/
    sSensorValues->fTrust = (ADC2BUF5*300.0f/1023.0f);
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
int8_t GetWindDirection(sSensorValues_t* sSensorValues)
{
    int8_t bError = 0;
    /*Get the direction in degres*/
    /*     0    */
    /*-90  +  90*/
    /*  +-180   */
    sSensorValues->fWindDir = (ADC2BUF3*360.0f/1023.0f)-180.0f;
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
int8_t GetWindSpeed(sSensorValues_t* sSensorValues)
{
    int8_t bError = 0;
    static uint16_t usCounterWindSpeed = 0;
    static float fMeanWindSpeed = 0.0f;

    if(usCounterWindSpeed<200)
    {
        fMeanWindSpeed += (2.25/(1/sSensorRawFreq.fWindFreq))*0.44704;
        usCounterWindSpeed++;
    }
    else
    {
        /*From davis instrument spec : V(mph)=(2.25/T) and V(m/s) = V(mph)*0.44704*/
        sSensorValues->fWindSpeed = (fMeanWindSpeed/200)+1;
        fMeanWindSpeed = 0.0f;
        usCounterWindSpeed = 0;
    }
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
int8_t GetTurbineRPM(sSensorValues_t* sSensorValues)
{
    static float fMeanTurbineRPM = 0;
    static uint8_t ubCounter = 0;
    int8_t bError = 0;
    if(ubCounter<200)
    {
        fMeanTurbineRPM += (sSensorRawFreq.fTurbineFreq*60.0f)/GEARTOOTH_TURBINE;
        ubCounter++;
    }

    else
    {
        sSensorValues->fTurbineRPM = fMeanTurbineRPM/200;
        fMeanTurbineRPM = 0.0f;
        ubCounter = 0;
    }
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
int8_t GetWheelRPM(sSensorValues_t* sSensorValues)
{
    int8_t bError = 0;
    static float fMeanWheelRPM;
    static uint8_t ubWheelCounter = 0;
    
    if(ubWheelCounter < 200)
    {
        fMeanWheelRPM += (sSensorRawFreq.fWheelFreq*60.0f)/GEARTOOTH_WHEEL;
        ubWheelCounter++;
    }
    else
    {
        sSensorValues->fWheelRPM = fMeanWheelRPM/200;
        fMeanWheelRPM = 0.0f;
        ubWheelCounter = 0;
    }
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
PrintVoltageSensing

        Print on UART_1 3V3 and 5V sensing values
        Return -1 when there's an error
	INPUT 		:
				-sSensorValues_t* (Sensor data structure)

	OUTPUT 		:
				-int8_t (Error)

*/
/************************************************************/
void PrintNotusVersion(void)
{
    int8_t bString[100] = {0};
    sprintf(bString,"\n\rNotus firmware version : %s\n\r",(NOTUS_VERSION));
    UartTxFrame(UART_1,bString,sizeof(bString));
}

/************************************************************/
/*
PrintVoltageSensing

        Print on UART_1 3V3 and 5V sensing values
        Return -1 when there's an error
	INPUT 		:
				-sSensorValues_t* (Sensor data structure)

	OUTPUT 		:
				-int8_t (Error)

*/
/************************************************************/
uint8_t PrintVoltageSensing(sSensorValues_t* sSensorValues)
{
    uint8_t ubValid = TRUE;
    int8_t bString[100] = {0};

    if(sSensorValues == NULL)
    {
        ubValid = FALSE;
    }

    if(ubValid)
    {
        sprintf(bString, "\n\r3V3 Sense Voltage = %.2f V \n\r5V0 Sense Voltage = %.2f V\n\r", sSensorValues->fSens3V3, sSensorValues->fSens5V0);
        UartTxFrame(UART_1,bString,sizeof(bString));
    }
    return ubValid;
}

/************************************************************/
/*
PrintTrust

        Print on UART_1 the trust value
        Return -1 when there's an error
	INPUT 		:
				-sSensorValues_t* (Sensor data structure)

	OUTPUT 		:
				-int8_t (Error)

*/
/************************************************************/
uint8_t PrintTrust(sSensorValues_t* sSensorValues)
{
    uint8_t ubValid = TRUE;
    int8_t bString[100] = {0};

    if(sSensorValues == NULL)
    {
        ubValid = FALSE;
    }

    if(ubValid)
    {
        sprintf(bString, "\n\rTrust = %.2f Lbs \n\r", sSensorValues->fTrust);
        UartTxFrame(UART_1,bString,sizeof(bString));
    }
    return ubValid;
}

/************************************************************/
/*
PrintWindDirection

        Print on UART_1 the wind direction value
        Return -1 when there's an error
	INPUT 		:
				-sSensorValues_t* (Sensor data structure)

	OUTPUT 		:
				-int8_t (Error)

*/
/************************************************************/
uint8_t PrintWindDirection(sSensorValues_t* sSensorValues)
{
    uint8_t ubValid = TRUE;
    int8_t bString[100] = {0};

    if(sSensorValues == NULL)
    {
        ubValid = FALSE;
    }

    if(ubValid)
    {
        sprintf(bString, "\n\rWind Direction = %.2f Degres \n\r", sSensorValues->fWindDir);
        UartTxFrame(UART_1,bString,sizeof(bString));
    }
    return ubValid;
}

/************************************************************/
/*
PrintWindSpeed

        Print on UART_1 the wind speed value
        Return -1 when there's an error
	INPUT 		:
				-sSensorValues_t* (Sensor data structure)

	OUTPUT 		:
				-int8_t (Error)

*/
/************************************************************/
uint8_t PrintWindSpeed(sSensorValues_t* sSensorValues)
{
    uint8_t ubValid = TRUE;
    int8_t bString[100] = {0};

    if(sSensorValues == NULL)
    {
        ubValid = FALSE;
    }

    if(ubValid)
    {
        sprintf(bString, "\n\rWind Speed = %.2f m/s \n\r", sSensorValues->fWindSpeed);
        UartTxFrame(UART_1,bString,sizeof(bString));
    }
    return ubValid;
}

/************************************************************/
/*
PrintTurbineRPM

        Print on UART_1 the turbine RPM
        Return -1 when there's an error
	INPUT 		:
				-sSensorValues_t* (Sensor data structure)

	OUTPUT 		:
				-int8_t (Error)

*/
/************************************************************/
uint8_t PrintTurbineRPM(sSensorValues_t* sSensorValues)
{
    uint8_t ubValid = TRUE;
    int8_t bString[100] = {0};

    if(sSensorValues == NULL)
    {
        ubValid = FALSE;
    }

    if(ubValid)
    {
        sprintf(bString, "\n\rTurbine Speed = %.2f RPM\n\r", sSensorValues->fTurbineRPM);
        UartTxFrame(UART_1,bString,sizeof(bString));
    }
    return ubValid;
}

/************************************************************/
/*
PrintWheelRPM

        Print on UART_1 the wheels RPM
        Return -1 when there's an error
	INPUT 		:
				-sSensorValues_t* (Sensor data structure)

	OUTPUT 		:
				-int8_t (Error)

*/
/************************************************************/
uint8_t PrintWheelRPM(sSensorValues_t* sSensorValues)
{
    uint8_t ubValid = TRUE;
    int8_t bString[100] = {0};

    if(sSensorValues == NULL)
    {
        ubValid = FALSE;
    }

    if(ubValid)
    {
        sprintf(bString, "\n\rWheels Speed = %.2f RPM\n\r", sSensorValues->fWheelRPM);
        UartTxFrame(UART_1,bString,sizeof(bString));
    }
    return ubValid;
}

/************************************************************/
/*
PrintsAccelerometer0

        Print on UART_1 the X Y and Z acceleration
        of the onboard sensor(Accelerometer0)

        Return -1 when there's an error
	INPUT 		:
				-sSensorValues_t* (Sensor data structure)

	OUTPUT 		:
				-int8_t (Error)

*/
/************************************************************/
uint8_t PrintAccelerometer0(sSensorValues_t* sSensorValues)
{
    uint8_t ubValid = TRUE;
    int8_t bString[100] = {0};

    if(sSensorValues == NULL)
    {
        ubValid = FALSE;
    }

    if(ubValid)
    {
        sprintf(bString, "\n\rX axis = %.2f G\n\rY axis = %.2f G\n\rZ axis = %.2f G\n\r", sSensorValues->sAccelerometer0.fGx,sSensorValues->sAccelerometer0.fGy,sSensorValues->sAccelerometer0.fGz);
        UartTxFrame(UART_1,bString,sizeof(bString));
    }
    return ubValid;
}

/************************************************************/
/*
PrintTime

        Print time -> from ds1338 RTC

        Return -1 when there's an error
	INPUT 		:
				-sSensorValues_t* (Sensor data structure)

	OUTPUT 		:
				-int8_t (Error)

*/
/************************************************************/
uint8_t PrintTime(sSensorValues_t* sSensorValues)
{
    uint8_t ubValid = TRUE;
    int8_t bString[100] = {0};

    if(sSensorValues == NULL)
    {
        ubValid = FALSE;
    }

    if(ubValid)
    {
        sprintf(bString, "\n\r%u:%u:%u\n\r", sSensorValues->ds1338.hours,sSensorValues->ds1338.minutes,sSensorValues->ds1338.seconds);
        UartTxFrame(UART_1,bString,sizeof(bString));
    }
    return ubValid;
}

/************************************************************/
/*
PrintWheelFreq

        Print wheel frequency

	INPUT 		:
				-sSensorRawFreq (Sensor data structure)

	OUTPUT 		:
				-int8_t (Error)

*/
/************************************************************/
uint8_t PrintWheelFreq(sSensorRawFreq_t* sSensorRawFreq)
{
    uint8_t ubValid = TRUE;
    int8_t bString[100] = {0};

    if(sSensorRawFreq == NULL)
    {
        ubValid = FALSE;
    }

    if(ubValid)
    {
        sprintf(bString, "\n\rWheel Freq = %.2f Hz\n\r", sSensorRawFreq->fWheelFreq);
        UartTxFrame(UART_1,bString,sizeof(bString));
    }
    return ubValid;
}

/************************************************************/
/*
        Print turbine frequency

	INPUT 		:
				-sSensorRawFreq (Sensor data structure)

	OUTPUT 		:
				-int8_t (Error)

*/
/************************************************************/
uint8_t PrintTurbineFreq(sSensorRawFreq_t* sSensorRawFreq)
{
    uint8_t ubValid = TRUE;
    int8_t bString[100] = {0};

    if(sSensorRawFreq == NULL)
    {
        ubValid = FALSE;
    }

    if(ubValid)
    {
        sprintf(bString, "\n\rTurbine Freq = %.2f Hz\n\r", sSensorRawFreq->fTurbineFreq);
        UartTxFrame(UART_1,bString,sizeof(bString));
    }
    return ubValid;
}

/************************************************************/
/*
PrintWindFreq

        Print anemometer frequency

	INPUT 		:
				-sSensorRawFreq (Sensor data structure)

	OUTPUT 		:
				-int8_t (Error)

*/
/************************************************************/
uint8_t PrintWindFreq(sSensorRawFreq_t* sSensorRawFreq)
{
    uint8_t ubValid = TRUE;
    int8_t bString[100] = {0};

    if(sSensorRawFreq == NULL)
    {
        ubValid = FALSE;
    }

    if(ubValid)
    {
        sprintf(bString, "\n\rWind Freq = %.2f Hz\n\r", sSensorRawFreq->fWindFreq);
        UartTxFrame(UART_1,bString,sizeof(bString));
    }
    return ubValid;
}

/************************************************************/
/*
PrintEeprom

        Print anemometer frequency

	INPUT 		:
				-None

	OUTPUT 		:
				-int8_t (Error)

*/
/************************************************************/
void PrintEeprom(void)
{
    int8_t bString[100] = {0};
    float fPitch = ReadPitchEeprom();
    float fTurbineDir = ReadTurbineDirEeprom();
    uint8_t ubGear = ReadGearEeprom();
    sprintf(bString, "\n\rPitch = %2f\n\r", fPitch);
    UartTxFrame(UART_1,bString,54);
}

uint8_t WriteGearEeprom(uint8_t ubGear)
{
    uint8_t ubValid = TRUE;
    ubValid = WriteByte(&(sSensorValues.sCat24c256),EEPROM_GEAR_ADDRESS,ubGear);
    return ubValid;
}

uint8_t WriteTurbineDirEeprom(float fDir)
{
    uint8_t ubValid = TRUE;
    union { float f; uint8_t i[4]; } mem;
    mem.f = fDir;
    WriteMultipleByte(&(sSensorValues.sCat24c256),EEPROM_TURBINE_POSITION_ADDRESS0,mem.i, 4);
    return ubValid;
}

uint8_t WritePitchEeprom(float fPitch)
{
    uint8_t ubValid = TRUE;
    union { float f; uint8_t i[4]; } mem;
    mem.f = fPitch;
    WriteMultipleByte(&(sSensorValues.sCat24c256),EEPROM_PITCH_ADDRESS0,mem.i, 4);
    return ubValid;
}

uint8_t ReadGearEeprom(void)
{
    uint8_t ubGear = 0;
    ReadByte(&(sSensorValues.sCat24c256),EEPROM_GEAR_ADDRESS,&ubGear);
    return ubGear;
}

float ReadTurbineDirEeprom(void)
{
    union { float f; uint8_t i[4]; } mem;
    ReadByte(&(sSensorValues.sCat24c256),EEPROM_TURBINE_POSITION_ADDRESS0,&mem.i[0]);
    ReadByte(&(sSensorValues.sCat24c256),EEPROM_TURBINE_POSITION_ADDRESS1,&mem.i[1]);
    ReadByte(&(sSensorValues.sCat24c256),EEPROM_TURBINE_POSITION_ADDRESS2,&mem.i[2]);
    ReadByte(&(sSensorValues.sCat24c256),EEPROM_TURBINE_POSITION_ADDRESS3,&mem.i[3]);
    return mem.f;
}

float ReadPitchEeprom(void)
{
    union { float f; uint8_t i[4]; } mem;
    ReadByte(&(sSensorValues.sCat24c256),EEPROM_PITCH_ADDRESS0,&mem.i[0]);
    ReadByte(&(sSensorValues.sCat24c256),EEPROM_PITCH_ADDRESS1,&mem.i[1]);
    ReadByte(&(sSensorValues.sCat24c256),EEPROM_PITCH_ADDRESS2,&mem.i[2]);
    ReadByte(&(sSensorValues.sCat24c256),EEPROM_PITCH_ADDRESS3,&mem.i[3]);
    return mem.f;
}
