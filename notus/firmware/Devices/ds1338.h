#ifndef __DS1338_H
#define	__DS1338_H

#include "../globaldef.h"
#include "../hardware_profile.h"
#include "../Peripherals/i2c.h"

typedef struct{
    /*Time variables*/
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t day;
    uint8_t month;
    uint8_t year;

    /*Configuration*/
    uint8_t port;
}ds1338_s;

void ds1338_init(ds1338_s* ds1338,int i2c_port);
void ds1338_setDate(ds1338_s* ds1338, uint8_t year,
                                     uint8_t month,
                                     uint8_t day);
void ds1338_setClock(ds1338_s* ds1338, uint8_t hours,
                                      uint8_t minutes,
                                      uint8_t seconds);

void ds1338_GetClock(ds1338_s* ds1338);

void ds1338_GetDate(ds1338_s* ds1338);

#endif // __DS1338_H
