#ifndef __LTC4151_H
#define	__LTC4151_H

#include "../../globaldef.h"
#include "../../hardware_profile.h"

typedef struct{
    uint8_t port;
}ltc4151_s;

float ltc4151_read_voltage(ltc4151_s*);
float ltc4151_read_current(ltc4151_s*);
void ltc4151_init(ltc4151_s*,int i2c_port);

#endif // __LTC4151_H
