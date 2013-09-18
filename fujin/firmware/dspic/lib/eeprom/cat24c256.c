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

/************************************************************/
/*                          INCLUDES                        */
/************************************************************/
#include "cat24c256.h"
/************************************************************/

/************************************************************/
/*                     PUBLIC FUNCTIONS                     */
/************************************************************/
/************************************************************/
/*
Initcat24c256
	Initialise the cat24c256 object


	INPUT 		:
				-sCat24c256 : device structure
                                -ubAddress  : device I2C address
                                -ubI2Cport  : device I2C Port

	OUTPUT 		:
				-Error(0 failed, 1 OK)


*/
/************************************************************/
uint8_t Initcat24c256(sCat24c256_t* sCat24c256, uint8_t ubAddress, uint8_t ubI2Cport)
{
  uint8_t ubValid = TRUE;

  /*Validity Check*/
  if(sCat24c256 == NULL)
  {
    ubValid = FALSE;
  }

  if(ubValid)
  {
    /*Set device informations*/
    sCat24c256->ubPort = ubI2Cport;    //Set I2C port
    sCat24c256->ubAddress = ubAddress; //Set device address

    /*I2C address can't be 0*/
    if(sCat24c256->ubAddress)
    {
      sCat24c256->ubInitialize = TRUE;
    }
  }

  return ubValid;
}
uint8_t WriteByte(sCat24c256_t* sCat24c256,uint16_t usAddress,uint8_t* data,uint8_t ubLenght)
{
    uint8_t ubValid = TRUE;
    uint8_t ubCounter;
    uint8_t ubBuffer[ubLenght+1];
    /*Formating for the 16bits address send*/
    ubBuffer[0] = (uint8_t)usAddress;
    memcpy(&ubBuffer[1],data,(uint16_t)ubLenght);

    if(sCat24c256 == NULL || sCat24c256->ubInitialize == FALSE)
    {
        ubValid = FALSE;
    }

    else
    {
        EEPROM_WP = 1;
        for(ubCounter = 0;ubCounter<ubLenght;ubCounter++)
        {
            ubValid = I2C_Send(sCat24c256->ubAddress,(uint8_t)(usAddress>>8),data[ubCounter],sCat24c256->ubPort);
        }
        EEPROM_WP = 0;
    }
    return ubValid;
}



