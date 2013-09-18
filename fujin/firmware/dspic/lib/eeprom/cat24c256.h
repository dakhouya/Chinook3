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
#include "../../globaldef.h"
#include "../dspic/i2c/i2c.h"
#include "../../hardware_profile.h"
#include <string.h>
/************************************************************/
#define CAT24C256_ADDRESS   1010000

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
uint8_t WriteByte(sCat24c256_t*,uint16_t ubAddress,uint8_t* data,uint8_t ubLenght);

#endif	/* _CAT24C256_H */

