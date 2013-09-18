#ifndef __lib_SPI_H
#define __lib_SPI_H

/**********************    INCLUDE    ***********************/
#include "p33EP512MC806.h"
#include "global.h"
/************************************************************/


/************************************************************/
/************************************************************/
/*					spi_init_as1107_u1						*/
/*	param: 	none											*/
/*	desc:	SPI2 initialization sequence for serial 	  	*/
/*			communication with U1 AS1107 IC. See spi.c for	*/
/*			detailed configuration of the SPI registers		*/
void spi_init_as1107_u1(void); 
/************************************************************/


/************************************************************/
/************************************************************/
/*					spi_init_as1107_u2						*/
/*	param: 	none											*/
/*	desc:	SPI3 initialization sequence for serial 	  	*/
/*			communication with U2 AS1107 IC. See spi.c for	*/
/*			detailed configuration of the SPI registers		*/	
void spi_init_as1107_u2(void);
/************************************************************/


/************************************************************/
/************************************************************/
/*					spi_init_lcd							*/
/*	param: 	none											*/
/*	desc:	SPI1 initialization sequence for serial 	  	*/
/*			communication with NHD-0420D3Z-NSW-BBW-V3. See 	*/
/*			spi.c for detailed configuration of the SPI		*/
/*			registers										*/		
void spi_init_lcd(void);		
/************************************************************/

#endif