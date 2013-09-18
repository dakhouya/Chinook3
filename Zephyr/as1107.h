#ifndef __lib_AS1107_H
#define __lib_AS1107_H

/**********************    INCLUDE    ***********************/
#include "spi.h"
#include "p33EP512MC806.h"
#include "global.h"
#include "M_TMR.h"

/************************************************************/


/***********************    DEFINE    ***********************/
#define load _RG9			//load pin for SPI2
#define load3 _RE3			//load pin for SPI3

#define noop		0x00	//AS1107: noop register 
#define dig0		0x01	//AS1107: dig0 register
#define dig1		0x02	//AS1107: dig1 register
#define dig2		0x03	//AS1107: dig2 register
#define dig3		0x04	//AS1107: dig3 register
#define	dig4		0x05	//AS1107: dig4 register
#define dig5		0x06	//AS1107: dig5 register
#define dig6		0x07	//AS1107: dig6 register
#define dig7		0x08	//AS1107: dig7 register
#define decodemode  0x09	//AS1107: decode mode register
#define intensity   0x0A	//AS1107: intensity register
#define scanlimit   0x0B	//AS1107: scanlimit register
#define shutdown    0x0C	//AS1107: shutdown register
#define feature     0x0E	//AS1107: feature register
#define disptest    0x0F	//AS1107: display test register
/************************************************************/


void resetGrammant(void);

void as1107_reset(void);

/************************************************************/
/************************************************************/
/*					as1107_decode_speed						*/
/*	param: 	Speed in float	(0.0f <= speed <= 999.9f)		*/
/*	desc:	Rounds speed to the tenth. Display on dig0-dig3	*/
/*			controlled by U1. dig3 is always the tenth		*/
void as1107_decode_speed(float speed);
/************************************************************/

/************************************************************/
/************************************************************/
/*					as1107_decode_rpm						*/
/*	param: 	rpm in float (0 <= rpm < 4000)				*/
/*	desc:	Displays wind turbine RPM on dig0-dig3 			*/
/*			controlled by U2								*/		
void as1107_decode_rpm(float rpm);
/************************************************************/

/************************************************************/
/************************************************************/
/*					as1107_decode_gear						*/
/*	param: 	gear number in integer (0 < gear <= 14)			*/
/*	desc:	Displays on dig4-dig5 controlled by U1			*/		
void as1107_decode_gear(int gear);
/************************************************************/

/************************************************************/
/************************************************************/
/*					as1107_decode_speed_count				*/
/*	param: 	none											*/
/*	desc:	Displays counter on dig0-dig3 controlled by U1	*/
/*			Counts from 000.0 to 999.9 and starts again		*/
void as1107_decode_speed_count(void);		 
/************************************************************/

/************************************************************/
/************************************************************/
/*					as1107_init								*/
/*	param: 	none											*/
/*	desc:	Initialization sequence for U1 and U2 AS1107 IC	*/		
void as1107_init(void);						
/************************************************************/

/************************************************************/
/************************************************************/
/*					as1107_write_u1							*/
/*	param: 	name of register, integer data to be sent.	 	*/
/*	desc:	Sends the register and the data to the U1		*/
/*			AS1107 IC via SPI in 16bit mode. Registers are	*/
/*			defined in as1107.h								*/	
void as1107_write_u1(int reg,int data);		
/************************************************************/

/************************************************************/
/************************************************************/
/*					as1107_write_u2							*/
/*	param: 	name of register, integer data to be sent.	 	*/
/*	desc:	Sends the register and the data to the U2		*/
/*			AS1107 IC via SPI in 16bit mode. Registers are	*/
/*			defined in as1107.h								*/
void as1107_write_u2(int reg,int data);
/************************************************************/

#endif