/************************************************************/
/* MMA8452.h                                                */
/* Library for the MMA8452 accelerometer                    */
/*                                                          */
/* MCU : dspic33E                                           */
/*                                                          */
/* Author :     David Khouya                                */
/* Date	  :	26/01/2013                                  */
/************************************************************/

/************************************************************/
#ifndef _MMA8452_MODULE_
#define _MMA8452_MODULE_
/************************************************************/

/************************************************************/
/*                        INCLUDES                          */
/************************************************************/
#include "../globaldef.h"
#include "../Peripherals/i2c.h"
/************************************************************/


/************************************************************/
/*		       MACRO DEFINITIONS                    */
/************************************************************/
/*I2C module definition*/
#define USED_I2C 		I2C_1

/*MMA8452 addresses*/
#define MMA8452_WRITE           0x3A
#define MMA8452_READ            0x3B

/*MMA8452 registers*/
#define STATUS			0x00
#define OUT_X_MSB		0x01
#define OUT_X_LSB		0x02
#define OUT_Y_MSB		0x03
#define OUT_Y_LSB		0x04
#define OUT_Z_MSB		0x05
#define OUT_Z_LSB		0x06

#define XYZ_DATA_CFG            0x0E
#define CTRL_REG1		0x2A

/*HP filter values*/

/*Scale values*/
#define SCALE_2G		0x00
#define SCALE_4G		0x01
#define SCALE_8G		0x02
/************************************************************/


/************************************************************/
/*		     STRUCTURE DEFINITIONS                  */
/************************************************************/
typedef struct data
{
	int16_t sRawAxisX;
	int16_t sRawAxisY;
	int16_t sRawAxisZ;
	float fGx;
	float fGy;
	float fGz;
}sAxis_t;
/************************************************************/


/************************************************************/
/*                    PUBLIC PROTOTYPES                     */
/************************************************************/
void MMA8452Init(void);
int8_t MMA8452InitStruct(sAxis_t *);
void MMA8452Activate(bool bState);
void MMA8452SetScale(uint8_t ubScale);
void MMA8452SetHPFilter(uint16_t usFrequency);
void MMA8452GetAxis(sAxis_t* sAxis);
/************************************************************/


/************************************************************/
#endif
/************************************************************/
