#ifndef _VCAN_PWM_H
#define _VCAN_PWM_H

#include "include.h"

#define MOTOR_OUT_DEAD_VAL_L 9
#define MOTOR_OUT_DEAD_VAL_R 3

void MotorOutput(void);
void MotorSpeedOut(void);
void SetMotorVoltage(float fLeftVoltage, float fRightVoltage);
void PWM_Init(void);

#endif