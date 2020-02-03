#ifndef _VCAN_FUN_h
#define _VCAN_FUN_h

#include "include.h"


int   myabs(int dat);
void  my_delay(long t);
float limit(float x, uint16 y);
int16 limit_ab(int16 x, uint16 a, uint16 b);
float power(float n);

#endif
