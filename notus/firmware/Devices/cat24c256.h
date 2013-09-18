/************************************************************/
/* cat24c256.c                                              */
/* Library for the cat24c256 eeprom                         */
/*                                                          */
/* MCU : dspic33E                                           */
/*                                                          */
/* Author : David Khouya                                    */
/* Date	  :	30/06/2013                                  */
/*                                                          */
/* Note: This librairy needs an I2C librairy                */
/* The I2C module is define in cat24c256.h                  */
/* You must initialise the I2C module on your own	    */
/************************************************************/

#ifndef CAT24C256_H
#define	CAT24C256_H

/************************************************************/
/*                          INCLUDES                        */
/************************************************************/
#include "../globaldef.h"
#include "../Peripherals/i2c.h"
#include "../hardware_profile.h"
#include <string.h>
/************************************************************/
#define CAT24C256_ADDRESS   10100000

typedef struct
{
  /*Validation*/
  uint8_t ubInitialize;

  /*Config*/
  uint8_t ubPort;     //Used I2C port
  uint8_t ubAddress;  //Device address
}sCat24c256_t;

/************************************************************/
/*                     PUBLIC PROTOTYPES                    */
/************************************************************/
uint8_t Initcat24c256(sCat24c256_t*, uint8_t ubAddress, uint8_t ubI2Cport);
uint8_t WriteByte(sCat24c256_t* sCat24c256,uint16_t usAddress,uint8_t ubByte);
uint8_t WriteMultipleByte(sCat24c256_t* sCat24c256,uint16_t usAddress,uint8_t* ubByte, uint8_t ubDataLenght);
uint8_t ReadByte(sCat24c256_t* sCat24c256,uint16_t usAddress,uint8_t* ubByte);

#endif	/* _CAT24C256_H */

