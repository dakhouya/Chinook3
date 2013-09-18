#ifndef __lib_LCD_H
#define __lib_LCD_H

/**********************    INCLUDE    ***********************/
#include "spi.h"
#include "p33EP512MC806.h"
#include "global.h"
/************************************************************/

/***********************    DEFINE    ***********************/
#define CS _LATD1		//Chip select pin for SP1

typedef struct{
	float pitch;
	float rpm;
} target_s;

/*	DEFINE for first display line	*/
#define line1char1		0x00	
#define line1char2		0x01
#define line1char3		0x02
#define line1char4		0x03
#define line1char5		0x04
#define line1char6		0x05	
#define line1char7		0x06
#define line1char8		0x07	
#define line1char9		0x08	
#define line1char10		0x09
#define line1char11		0x0A
#define line1char12		0x0B
#define line1char13		0x0C
#define line1char14		0x0D	
#define line1char15		0x0E	
#define line1char16		0x0F
#define line1char17		0x10	
#define line1char18		0x11	
#define line1char19		0x12	
#define line1char20		0x13

/*	DEFINE for second display line	*/
#define line2char1		0x40	
#define line2char2		0x41	
#define line2char3		0x42
#define line2char4		0x43
#define line2char5		0x44
#define line2char6		0x45
#define line2char7		0x46
#define line2char8		0x47	
#define line2char9		0x48
#define line2char10		0x49	
#define line2char11		0x4A
#define line2char12		0x4B
#define line2char13		0x4C
#define line2char14		0x4D
#define line2char15		0x4E
#define line2char16		0x4F
#define line2char17		0x50
#define line2char18		0x51
#define line2char19		0x52	
#define line2char20		0x53

/*	DEFINE for third display line	*/
#define line3char1		0x14	
#define line3char2		0x15	
#define line3char3		0x16	
#define line3char4		0x17	
#define line3char5		0x18	
#define line3char6		0x19	
#define line3char7		0x1A
#define line3char8		0x1B
#define line3char9		0x1C
#define line3char10		0x1D
#define line3char11		0x1E
#define line3char12		0x1F
#define line3char13		0x20	
#define line3char14		0x21
#define line3char15		0x22
#define line3char16		0x23
#define line3char17		0x24
#define line3char18		0x25
#define line3char19		0x26
#define line3char20		0x27

/*	DEFINE for fourth display line	*/
#define line4char1		0x54
#define line4char2		0x55
#define line4char3		0x56
#define line4char4		0x57
#define line4char5		0x58
#define line4char6		0x59
#define line4char7		0x5A
#define line4char8		0x5B
#define line4char9		0x5C
#define line4char10		0x5D
#define line4char11		0x5E
#define line4char12		0x5F
#define line4char13		0x60
#define line4char14		0x61	
#define line4char15		0x62
#define line4char16		0x63
#define line4char17		0x64
#define line4char18		0x65
#define line4char19		0x66
#define line4char20		0x67
/************************************************************/

void LCD_displayWindSpeed(float wsr);

float calcul_PercentToDegree(float percent);

target_s calcTarget(float windSpeed);

void LCD_displayTargetPitch(float wind);

void LCD_displayTargetRPM(float spd);

void LCD_displayRPM(float spd);

void LCD_displayGear(int spd);

void LCD_displaySpeedKMH(float spd);

float calcul_TSR(float windspeed, float turbineRPM);

float calcul_vitesseEff(float wheelRPM, float windspeed);

float calcul_RPMratio(int gear, float wheelRPM, float turbineRPM);

void LCD_displayWindSpeedRatio(float wsr);

void LCD_displayRPMRatio(float rpm);

void LCD_displayTipSpeedRatio(float tsr);

void LCD_displayRelWindDir(float rlwd);

void LCD_displayPitch(float pitch);

/************************************************************/
/************************************************************/
/*						LCD_init							*/
/*	param: 	backlight integer, contrast integer				*/
/*	desc:	Initialization sequence for the LCD screen, 	*/
/*			Backlight value must be between 1 and 8			*/
/*				-> recommended value : 8					*/
/*			Contrast value must be between 1 and 50			*/
/*				-> recommended value : 40					*/
void LCD_init(int backlight, int contrast);
/************************************************************/


/************************************************************/
/************************************************************/
/*						LCD_writeString						*/
/*	param: 	char array, length of array in integer			*/
/*	desc:	Writes string on the display				  	*/
void LCD_writeString(char string[], int stringLength);
/************************************************************/


/************************************************************/
/************************************************************/
/*						LCD_displaySetup					*/
/*	param: 	none											*/
/*	desc:	Sets up the LCD screen to display the following	*/
/*					____________________					*/
/*				   |TGR:0000 RWD:+000.0°|					*/
/*				   |PCH+00.0 TIPSP:00.00|					*/	
/*				   |TGP+00.0 WND:00.0m/s|					*/	
/*				   |WSR:00.0 00.00  0000|					*/
/*					¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯					*/
/*				    										*/
void LCD_displaySetup(void);
/************************************************************/


/************************************************************/
/************************************************************/
/*						LCD_write							*/
/*	param: 	1 byte word										*/
/*	desc:	writes data1 to LCD via SPI						*/
void LCD_write(int data1);
/************************************************************/


/************************************************************/
/************************************************************/
/*						LCD_displayON						*/
/*	param:	none											*/
/*	desc:	Turns on display								*/
void LCD_displayON(void);
/************************************************************/


/************************************************************/
/************************************************************/
/*						LCD_displayOFF						*/
/*	param:	none											*/
/*	desc:	Turns off display								*/
void LCD_displayOFF(void);
/************************************************************/


/************************************************************/
/************************************************************/
/*						LCD_setCursor						*/
/*	param:	1 byte word										*/
/*	desc:	Moves cursor to position						*/
void LCD_setCursor(int position);
/************************************************************/


/************************************************************/
/************************************************************/
/*						LCD_cursorHome						*/
/*	param:	none											*/
/*	desc:	Moves cursor to home position					*/
void LCD_cursorHome(void);
/************************************************************/


/************************************************************/
/************************************************************/
/*						LCD_cursorLeft						*/
/*	param:	none											*/
/*	desc:	Moves cursor one char left						*/
void LCD_cursorLeft(void);
/************************************************************/


/************************************************************/
/************************************************************/
/*						LCD_cursorRight						*/
/*	param: 	none											*/
/*	desc:	Moves cursor one char right						*/
void LCD_cursorRight(void);
/************************************************************/


/************************************************************/
/************************************************************/
/*						LCD_backspace						*/
/*	param:	none											*/
/*	desc:	Move cursor back one space,delete last character*/
void LCD_backspace(void);
/************************************************************/


/************************************************************/
/************************************************************/
/*						LCD_clearScreen						*/
/*	param:	none											*/
/*	desc:	Screen is cleared of chars						*/
void LCD_clearScreen(void);
/************************************************************/


/************************************************************/
/************************************************************/
/*						LCD_setContrast						*/
/*	param:	1 byte word (between 1 and 50)					*/
/*	desc:	Adjusts contrast, default value is 40			*/
void LCD_setContrast(int contrast);
/************************************************************/


/************************************************************/
/************************************************************/
/*						LCD_setBacklight					*/
/*	param:	1 byte word (between 1 and 8)					*/
/*	desc:	Adjusts backlight, default value is 8			*/
void LCD_setBacklight(int backlight);
/************************************************************/

#endif























