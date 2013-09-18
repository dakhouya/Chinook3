/************************************************************/
/* MMA8452.h												*/
/* Library for the MMA8452 accelerometer			 		*/
/*															*/
/* MCU : dspic33E											*/
/*															*/
/* Author : David Khouya									*/
/* Date	  :	26/01/2013										*/
/* Version: 1.0												*/
/*															*/
/* Note: This librairy needs an I2C librairy       			*/
/* The I2C module is define in MMA8452.h			        */
/* You must initialise the I2C module on your own	        */
/************************************************************/

/************************************************************/
/*						   INCLUDES			 				*/
/************************************************************/
#include "MMA8452.h"
/************************************************************/


/************************************************************/
/*			         PRIVATE VARIABLES			 			*/
/************************************************************/
static uint16_t	usDividerG=0;	/*Use to calculate the number of Gs.*/
static uint8_t	ubScaleG=0;		/*Scale of the number of Gs*/

/************************************************************/




/************************************************************/
/*				     PUBLIC FUNCTIONS			 			*/
/************************************************************/
/************************************************************/
/*
MMA8452Init
	Initialise the MMA8452 in full scale mode : 8G
	

	INPUT 		: 
				-None
				
	OUTPUT 		:	
				-None				
				

*/
/************************************************************/
void MMA8452Init(void)
{
	/*Must be in standby mode to change registers*/
	MMA8452Activate(DISABLE);
	MMA8452SetScale(SCALE_8G);
	MMA8452Activate(ENABLE);
}

/************************************************************/
/*
MMA8452InitStruct
	Initialise the MMA8452 structure to 0s on all values
        Return -1 when there's an error
 
	INPUT 		: 
				-sAxis_t (Accelerometer values)
				
	OUTPUT 		:	
				-int8_t (Error)				
				

*/
/************************************************************/
int8_t MMA8452InitStruct(sAxis_t * sAcclerometerValues)
{
    int8_t bError = 0;

    /*Validity Check*/
    if(sAcclerometerValues == NULL)
    {
        bError = -1;
    }

    /*Clear Structure*/
    else
    {
     	sAcclerometerValues->sRawAxisX = 0x0000;
	sAcclerometerValues->sRawAxisY = 0x0000;
	sAcclerometerValues->sRawAxisZ = 0x0000;
	sAcclerometerValues->fGx = 0.0f;
	sAcclerometerValues->fGy = 0.0f;
	sAcclerometerValues->fGz = 0.0f;
    }

    return bError;
}
/************************************************************/
/*
MMA8452Activate
	Set the device active or in standby mode
	
	INPUT 		: 
				bState : ENABLE or DISABLE
				
	OUTPUT 		:	
				-None				
				

*/
/************************************************************/
void MMA8452Activate(bool bState)
{
	uint8_t ubBuffer = 0;

	I2C_Receive(MMA8452_WRITE,MMA8452_READ,CTRL_REG1,&ubBuffer,USED_I2C);
	if(bState == ENABLE)
	{
		ubBuffer |= bState;
	}
	else
	{
		ubBuffer &= ~0x01;
	}
	I2C_Send(MMA8452_WRITE,CTRL_REG1,ubBuffer,USED_I2C);
}
/************************************************************/
/*
MMA8452SetScale
	Set the working scale of the accelerometer
	2G, 4G or 8G 

	INPUT 		: 
				ubScale : Number of Gs
				
	OUTPUT 		:	
				-None				
				

*/
/************************************************************/
void MMA8452SetScale(uint8_t ubScale)
{
	uint8_t ubBuffer = 0;

	/*Used for calculation*/
	switch(ubScale)
	{
		case SCALE_2G:
		usDividerG = 1024U;
		ubScaleG = 0x02;
		break;

		case SCALE_4G:
		usDividerG = 512U;
		ubScaleG = 0x04;
		break;

		case SCALE_8G:
		usDividerG = 256U;
		ubScaleG = 0x08;
		break;

		default:
		break;
	}

	I2C_Receive(MMA8452_WRITE,MMA8452_READ,XYZ_DATA_CFG,&ubBuffer,USED_I2C);
	/*Clear the last LSB and write the new value*/
	ubBuffer &=  0xFC;
	ubBuffer |= ubScale;
	I2C_Send(MMA8452_WRITE,XYZ_DATA_CFG,ubBuffer,USED_I2C);
}
/************************************************************/
/*
MMA8452SetHPFilter
	Set the Cut off frequency of the high pass filter

	INPUT 		: 
				usFrequency
				
	OUTPUT 		:	
				-None				
				

*/
/************************************************************/
void MMA8452SetHPFilter(uint16_t usFrequency)
{
}
/************************************************************/
/*
MMA8452GetAxis
	Get the acceleration data of the X, Y and Z axis
	The data that is received is received are 2's complement numbers

	INPUT 		: 
				sAxis : Structure that contains the Axis' data
				
	OUTPUT 		:	
				-None				
				

*/
/************************************************************/
void MMA8452GetAxis(sAxis_t* sAxis)
{
	uint8_t ubNegativeDetection=0;
	uint8_t ubAxisX=0;
	uint8_t ubAxisY=0;
	uint8_t ubAxisZ=0;

	/*Read X axis*/
	I2C_Receive(MMA8452_WRITE,MMA8452_READ,OUT_X_MSB,&ubAxisX,USED_I2C);
	sAxis->sRawAxisX = (int16_t)ubAxisX<<0x0008;
	/*Check if the number of Gs is negative*/
	if(ubAxisX>0x7F)
	{
		ubNegativeDetection=1;
	}
	I2C_Receive(MMA8452_WRITE,MMA8452_READ,OUT_X_LSB,&ubAxisX,USED_I2C);
	sAxis->sRawAxisX += (int16_t)ubAxisX;
	sAxis->sRawAxisX >>= 0x0004;

	if(ubNegativeDetection)
	{
		sAxis->sRawAxisX = ~sAxis->sRawAxisX+1;
		sAxis->sRawAxisX *= -1;
		ubNegativeDetection = 0;
	}
	/*Calculate number of Gs*/	
	sAxis->fGx = (float)sAxis->sRawAxisX/((float)usDividerG);


	/*Read Y axis*/
	I2C_Receive(MMA8452_WRITE,MMA8452_READ,OUT_Y_MSB,&ubAxisY,USED_I2C);
	sAxis->sRawAxisY = (int16_t)ubAxisY<<0x0008;
	/*Check if the number of Gs is negative*/
	if(ubAxisY>0x7F)
	{
		ubNegativeDetection=1;
	}
	I2C_Receive(MMA8452_WRITE,MMA8452_READ,OUT_Y_LSB,&ubAxisY,USED_I2C);
	sAxis->sRawAxisY += (int16_t)ubAxisY;
	sAxis->sRawAxisY >>= 0x0004;
	if(ubNegativeDetection)
	{
		sAxis->sRawAxisY = ~sAxis->sRawAxisY+1;
		sAxis->sRawAxisY *= -1;
		ubNegativeDetection = 0;
	}
	sAxis->fGy = (float)sAxis->sRawAxisY/((float)usDividerG);


	/*Read Z axis*/
	I2C_Receive(MMA8452_WRITE,MMA8452_READ,OUT_Z_MSB,&ubAxisZ,USED_I2C);
	sAxis->sRawAxisZ = (int16_t)ubAxisZ<<0x0008;
	/*Check if the number of Gs is negative*/
	if(ubAxisZ>0x7F)
	{
		ubNegativeDetection=1;
	}
	I2C_Receive(MMA8452_WRITE,MMA8452_READ,OUT_Z_LSB,&ubAxisZ,USED_I2C);
	sAxis->sRawAxisZ += (int16_t)ubAxisZ;
	sAxis->sRawAxisZ >>= 0x0004;
	if(ubNegativeDetection)
	{
		sAxis->sRawAxisZ = ~sAxis->sRawAxisZ+1.0f;
		sAxis->sRawAxisZ *= -1.0f;
		ubNegativeDetection = 0.0f;
	}
	sAxis->fGz = (float)sAxis->sRawAxisZ/((float)usDividerG);
}
/************************************************************/


/************************************************************/
/*				    PRIVATES FUNCTIONS			 			*/
/************************************************************/

/************************************************************/

