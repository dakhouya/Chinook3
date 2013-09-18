/* 
 * File:   utils.h
 * Author: pastjean
 *
 * Created on May 16, 2013, 12:29 PM
 */

#ifndef UTILS_H
#define	UTILS_H

#include "math.h"
#include "string.h"

void clear_buf(void* buf,size_t len){
    memset(buf,0,len);
}


#define PRECISE_PI (asin(1)*2.0)
#define PI 3.1415926536

static inline float deg2rad(float deg){return (deg*2.0*PRECISE_PI)/360;}
static inline float rad2deg(float rad){return (rad*180.0)/PRECISE_PI;}
#endif	/* UTILS_H */

