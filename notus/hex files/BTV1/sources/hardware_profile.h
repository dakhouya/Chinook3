/************************************************************/
/* hardware_profile.h										*/
/* Define pins and Gobal definitions of the sensor board	*/
/*															*/
/* MCU : DSPIC33EP512MC806									*/
/*															*/
/* Author : David Khouya, Chinook 3							*/
/* Date	  :	03/12/2012										*/
/* Version: 1.0												*/
/************************************************************/

/************************************************************/
#ifndef HARDWARE_PROFILE_MODULE
#define HARDWARE_PROFILE_MODULE
/************************************************************/

/************************************************************/
/*						   INCLUDES			 				*/
/************************************************************/
#include "p33EP512MC806.h"
/************************************************************/
/****Global definitions***/
#define CPU_CLOCK 	80000000.0f
#define FOSC_MHZ	80
#define FOSC		80000000			//External Xtal 20MHz(HS) | Internal FRC 7.37MHZ
#define UART1_SPEED	9600.0f				//UART baud rate
#define UART2_SPEED	9600.0f				//UART baud rate
#define UART3_SPEED	9600.0f				//UART baud rate
#define I2C_SPEED	100000.0f			//I2C Clock Speed -> 389KHz
#define SPI_SPEED	100000.0f
#define CAN_SPEED	100000.0f
#define TIMER5_FREQ     10.0f
/*************************/

/*******Config pins*******/
/*Pin mode: 1=input, 0=output*/
#define CONF_LED_STAT0 TRISDbits.TRISD8
#define CONF_LED_STAT1 TRISDbits.TRISD9
#define CONF_LED_STAT2 TRISDbits.TRISD10
#define CONF_LED_STAT3 TRISDbits.TRISD11

#define CONF_CANRX TRISDbits.TRISD7
#define CONF_CANTX TRISDbits.TRISD6

#define CONF_U1RX TRISFbits.TRISF2
#define CONF_U1TX TRISFbits.TRISF3
#define CONF_U2RX TRISFbits.TRISF0
#define CONF_U2TX TRISFbits.TRISF1
#define CONF_U3RX TRISDbits.TRISD5
#define CONF_U3TX TRISDbits.TRISD4

#define CONF_SCL TRISGbits.TRISG2
#define CONF_SDA TRISGbits.TRISG3
#define CONF_SCK TRISGbits.TRISG6
#define CONF_SDI TRISGbits.TRISG7
#define CONF_SDO TRISGbits.TRISG8

#define CONF_EEPROM_WP TRISFbits.TRISF6
#define CONF_SD_CARD_CS TRISFbits.TRISF5
#define CONF_RS232_RS485_SEL TRISFbits.TRISF4

#define CONF_OSCIN TRISCbits.TRISC12
#define CONF_OSCOUT TRISCbits.TRISC15
#define CONF_SOSCIN TRISCbits.TRISC13
#define CONF_SOSCOUT TRISCbits.TRISC14

#define CONF_SIGNAL_IN0 TRISDbits.TRISD0
#define CONF_SIGNAL_IN1 TRISDbits.TRISD1
#define CONF_SIGNAL_IN2 TRISDbits.TRISD2
#define CONF_SIGNAL_IN3 TRISDbits.TRISD3
/*************************/

/**********Pins***********/
#define LED_STAT0 PORTDbits.RD8
#define LED_STAT1 PORTDbits.RD9
#define LED_STAT2 PORTDbits.RD10
#define LED_STAT3 PORTDbits.RD11

#define CANRX PORTDbits.RD7
#define CANTX PORTDbits.RD6

#define U1RX PORTFbits.RF2
#define U1TX PORTFbits.RF3
#define U2RX PORTFbits.RF0
#define U2TX PORTFbits.RF1
#define U3RX PORTDits.RD5
#define U3TX PORTDbits.RD4

#define SCL PORTGbits.RG2
#define SDA PORTGbits.RG3
#define SCK PORTGbits.RG6
#define SDI PORTGbits.RG7
#define SDO PORTGbits.RG8

#define EEPROM_WP PORTFbits.RF6
#define SD_CARD_CS PORTFbits.RF5
#define RS232_RS485_SEL PORTFbits.RF4

#define OSCIN PORTCbits.RC12
#define OSCOUT PORTCbits.RC15
#define SOSCIN PORTCbits.RC13
#define SOSCOUT PORTCbits.RC14

#define SIGNAL_IN0 PORTDbits.RD0
#define SIGNAL_IN1 PORTDbits.RD1
#define SIGNAL_IN2 PORTDbits.RD2
#define SIGNAL_IN3 PORTDbits.RD3
/*************************/

/************************************************************/
#endif
/************************************************************/
