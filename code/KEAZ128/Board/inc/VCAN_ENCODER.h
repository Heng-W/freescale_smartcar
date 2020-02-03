#ifndef _VCAN_ENCODER_H
#define _VCAN_ENCODER_H

#include "include.h"

extern int32 leftMotorPulseSigma, rightMotorPulseSigma;

void Encoder_Init(void);
void GetMotorPulse(void);

#endif
