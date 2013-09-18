#ifndef __FUJIN_H
#define	__FUJIN_H

#include "config.h"

#include <p33EP512MC806.h>
#include "hardware_profile.h"
#include "globaldef.h"
#include "can_chinook3.h"

// Peripheral includes
#include "lib/dspic/dspic.h"

// Device includes
#include "lib/currentmonitor/ltc4151.h"

#include "chinook.h"

// Command library
#include "lib/skadi/skadi.h"


#define FUJIN_OK                0
#define FUJIN_ERR               -1


typedef struct{

    // All Uart Feature & devices
    bool has_uart;
    bool has_xbee;
    bool has_usbserial;

    // All i2c Feature & devices
    bool has_i2c;
    bool has_rtc;
    bool has_eeprom;
    bool has_vmon;
    
    // Other Communication features
    bool has_spi;
    bool has_can;

    ltc4151_s ltc4151_state;

    //For dataloggin
    logging_s loggin;

    // Variable Chinook present STATE
    chinook_s chinook;
    Skadi skadi;

} Fujin_s;

extern Fujin_s fujin;

// Application State
void fujin_init_board();
void fujin_set_clk();
void fujin_init_io();
void fujin_init_uart();
void fujin_init_i2c();

void fujin_init_rtc();
void fujin_init_vmon();
void fujin_init_eeprom();

void fujin_init_can();
void fujin_init_spi();
#endif	// __FUJIN_H

