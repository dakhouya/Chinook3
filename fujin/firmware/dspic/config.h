/* 
 * Configuration options to enable and disable features. Quite usefull
 */

#ifndef CONFIG_H
#define	CONFIG_H

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define DEBUG FALSE

#define ENABLE_UART TRUE
#define ENABLE_XBEE TRUE
#define ENABLE_USBSERIAL TRUE

#define ENABLE_I2C TRUE
#define ENABLE_RTC FALSE
#define ENABLE_EEPROM FALSE
#define ENABLE_VMON FALSE


#define ENABLE_SPI FALSE
#define ENABLE_CAN TRUE


#endif	/* CONFIG_H */

