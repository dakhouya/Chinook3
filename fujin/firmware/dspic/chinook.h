/*
 * Chinook structures for Fujin board
 * Author: pastjean
 */

#ifndef CHINOOK_H
#define	CHINOOK_H

typedef struct{
    float i; // Current
    float v; // Voltage
} power_s;

typedef struct{
    int dir; // (deg) Relative direction to vehicule direction
    float speed; // (m/s)
} wind_s;

typedef struct{
    float speed; // (rad/s)
    float pitch; // (deg)
} eol_s;

typedef struct{
    power_s power;
    wind_s wind;
    eol_s eol;
} chinook_s;

typedef struct{
    float fTurbineRPM;
    float fTurbineDir;
    float fWheelRPM;
    float fTrust;
    float fPitch;
    float fWindDir;
    float fWindSpeed;
    uint8_t ubGear;
} logging_s;


#endif	/* CHINOOK_H */

