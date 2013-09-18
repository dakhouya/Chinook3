#ifndef __lib_SHIFT_H
#define __lib_SHIFT_H

/**********************    INCLUDE    ***********************/
#include "p33EP512MC806.h"
#include "global.h"
#include "can.h"
#include "can_chinook3.h"
/************************************************************/


/***********************    DEFINE    ***********************/
#define SHIFTUP		_RE7
#define SHIFTDWN	_RE6
/************************************************************/

//void modeConfig(void);
void init_shiftButtons(void);
void memButtons(void);

#endif