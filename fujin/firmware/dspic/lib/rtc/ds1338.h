#ifndef __DS1338_H
#define	__DS1338_H

#include "../../globaldef.h"
#include "../../hardware_profile.h"

typedef struct{
    uint8_t port;
}ds1338_s;

void ds1338_init(ds1338_s* ds1338,int i2c_port);
void ds1338_setDate(ds1338_s ds1338, uint8_t year,
                                     uint8_t month,
                                     uint8_t day);
void ds1338_setClock(ds1338_s ds1338, uint8_t hours,
                                      uint8_t minutes,
                                      uint8_t seconds);
#endif // __LTC4151_H
