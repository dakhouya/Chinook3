#include "ds1338.h"
#include "../dspic/i2c/i2c.h"

// The i2c addresses
#define DS1338_READ  0xD1
#define DS1338_WRITE 0xD0

// The registers
#define DS1338_SECONDS_REG 0x00
#define DS1338_MINUTES_REG 0x01
#define DS1338_HOURS_REG   0x02
#define DS1338_DAYS_REG     0x03
#define DS1338_DATES_REG    0x04
#define DS1338_MONTHS_REG   0x05
#define DS1338_YEARS_REG    0x06
#define DS1338_CONTROLS_REG 0x07

typedef struct ds1338_seconds {
    union {
        struct {
            unsigned secondsl:4;
            unsigned secondsh:3;
            unsigned ch:1; // Clock Halt when set to 1 the oscillator is disabled
        };
        struct {
            unsigned seconds:7;
            unsigned :1;
        };
    };
} ds1338_seconds;

typedef struct ds1338_minutes {
    union {
        struct {
            unsigned minutesl:4;
            unsigned minutesh:3;
            unsigned :1;
        };
        struct {
            unsigned minutes:7;
            unsigned :1;
        };
    };
} ds1338_minutes;

typedef struct ds1338_hours {
    union {
        struct {
            unsigned hourl:4;
            unsigned hourh10:1;
            unsigned hourh20:1;
            unsigned clockMode:1;
            unsigned :1;
        };

        struct {
            unsigned hours24:6;
            unsigned :2;
        };
        struct {
            unsigned hours12:5;
            unsigned AMPM:1;
            unsigned :2;
        };
    };
} ds1338_hours;

typedef struct ds1338_day {
    unsigned day:3;
    unsigned :5;
} ds1338_day;

typedef struct ds1338_date {
    union {
        struct {
            unsigned datel:4;
            unsigned dateh:2;
            unsigned :2;
        };
        struct {
            unsigned date:6;
            unsigned :2;
        };
    };
} ds1338_date;

typedef struct ds1338_month {
    union {
        struct {
            unsigned monthl:4;
            unsigned monthh:1;
            unsigned :3;
        };
        struct {
            unsigned month:5;
            unsigned :3;
        };
    };
} ds1338_month;

typedef struct ds1338_year {
    union {
        struct {
            unsigned yearl:4;
            unsigned yearh:4;
        };
        struct {
            unsigned year:8;
        };
    };
} ds1338_year;

/*
 * Rate Select (RS1 and RS0): These bits control the frequency of the
 *   square-wave output when the square-wave output has been enabled.
 *
 *    -------------------------------------
 *   | OUT | RS1 | RS0 | SQW Output | SQWE |
 *    -------------------------------------
 *   |  X  |  0  |  0  |        1Hz |   1  |
 *   |  X  |  0  |  1  |   4.096kHz |   1  |
 *   |  X  |  1  |  0  |   8.192kHz |   1  |
 *   |  X  |  1  |  1  |  32.768kHz |   1  |
 *   |  0  |  X  |  X  |          0 |   0  |
 *   |  1  |  X  |  X  |          1 |   0  |
 *    -------------------------------------
 *
 * Square-Wave Enable (SQWE): When set to logic 1, this bit enables the
 *   oscillator output to operate with either VCC or VBAT applied.
 *
 * Oscillator Stop Flag (OSF): A logic 1 in this bit indicates that the 
 *   oscillator has stopped or was stopped for some time period and can be used
 *   to judge the validity of the clock and calendar data. 
 *  
 * Output Control (OUT): Controls the output level of the SQW/OUT pin when the
 *   square-wave output is disabled. If SQWE = 0, the logic level on the SQW/OUT
 *   pin is 1 if OUT = 1; it is 0 if OUT = 0.
 */

typedef struct ds1338_control {
    unsigned RS0 : 1;
    unsigned RS1 : 1;
    unsigned : 2;
    unsigned SQWE : 1;
    unsigned OSF : 1;
    unsigned : 1;
    unsigned OUT : 1; //
} ds1338_control;

void ds1338_init(ds1338_s* ds1338, int i2c_port) {
    ds1338->port = i2c_port;
}

void ds1338_setDate(ds1338_s ds1338, uint8_t year,
                                     uint8_t month,
                                     uint8_t date){
    ds1338_date d;
    ds1338_month m;
    ds1338_year y;

    d.date=date   & 0x3F;
    m.month=month & 0x1F;
    y.year=year   & 0xFF;

//    I2C_Send(DS1338_WRITE,DS1338_YEARS_REG, y, ds1338->port);
//    I2C_Send(DS1338_WRITE,DS1338_MONTHS_REG, m, ds1338->port);
//    I2C_Send(DS1338_WRITE,DS1338_DATES_REG, d, ds1338->port);
}
void ds1338_setClock(ds1338_s ds1338, uint8_t hours,
                                      uint8_t minutes,
                                      uint8_t seconds){
    ds1338_seconds s;
    ds1338_minutes m;
    ds1338_hours h;

    s.seconds=seconds;
    s.ch=0;

    m.minutes=minutes & 0x7F;

    h.hours24 = hours & 0x3F;
    h.clockMode = 1;
    
//    I2C_Send(DS1338_WRITE,DS1338_HOURS_REG ,h, ds1338->port);
//    I2C_Send(DS1338_WRITE,DS1338_MINUTES_REG ,m, ds1338->port);
//    I2C_Send(DS1338_WRITE,DS1338_SECONDS_REG ,s, ds1338->port);
}