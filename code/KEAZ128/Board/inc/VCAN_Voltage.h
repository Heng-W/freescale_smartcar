#ifndef _VCAN_VOLTAGE_H
#define _VCAN_VOLTAGE_H

#include "include.h"

#define DIR_LEFT_OFFSET 12
#define DIR_RIGHT_OFFSET 0

extern int g_nInputVoltageCount ;
extern uint32 g_lnInputVoltageSigma[6];
extern uint16 g_nInputVoltage[6];

void SampleInputVoltage(void);
void GetInputVoltageAverage(void);
void DirectionVoltageSigma(void);

#endif