#ifndef _VCAN_Interrupt_H
#define _VCAN_Interrupt_H

#include "include.h"

#define  INPUT_VOLTAGE_AVERAGE 5  //取样 n 次求均值

extern int g_n1MSEventCount;
extern int g_nSpeedControlCount;
extern int g_nDirectionControlCount;
extern int g_nKeyCount;

void PIT_Interrupt(void);

#endif