#include "VCAN_PWM.h"

float g_fLeftMotorOut = 0, g_fRightMotorOut = 0;

void MotorOutput(void)      //电机输出
{
    float fLeft, fRight;
    fLeft = g_fAngleControlOut - g_fSpeedControlOut -  g_fDirectionControlOut;
    fRight = g_fAngleControlOut - g_fSpeedControlOut +  g_fDirectionControlOut;

    g_fLeftMotorOut = fLeft;
    g_fRightMotorOut = fRight;
    MotorSpeedOut();
}

void MotorSpeedOut(void)     //电机 PWM 计算
{
    float fLeftVal, fRightVal;
    fLeftVal = g_fLeftMotorOut;
    fRightVal = g_fRightMotorOut;

    if (fLeftVal > 0)  fLeftVal += MOTOR_OUT_DEAD_VAL_L;
    else if (fLeftVal < 0)  fLeftVal -= MOTOR_OUT_DEAD_VAL_L;

    if (fRightVal > 0)  fRightVal += MOTOR_OUT_DEAD_VAL_R;
    else if (fRightVal < 0)  fRightVal -= MOTOR_OUT_DEAD_VAL_R;

    fLeftVal = limit(fLeftVal, 100);
    fRightVal = limit(fRightVal, 100);

    SetMotorVoltage(fLeftVal, fRightVal);
}

void SetMotorVoltage(float fLeftVoltage, float fRightVoltage) //PWM 输出设置
{
    float nOut;
    //Voltage > 0 : Move forward;
    if (fLeftVoltage > 0)
    {
        ftm_pwm_fduty(FTM2, FTM_CH3, 0);
        nOut = fLeftVoltage ;
        ftm_pwm_fduty(FTM2, FTM_CH2, nOut);
    }
    else
    {
        ftm_pwm_fduty(FTM2, FTM_CH2, 0);
        fLeftVoltage = -fLeftVoltage;
        nOut = fLeftVoltage ;
        ftm_pwm_fduty(FTM2, FTM_CH3, nOut);
    }

    if (fRightVoltage > 0)
    {
        ftm_pwm_fduty(FTM2, FTM_CH5, 0);
        nOut = fRightVoltage ;
        ftm_pwm_fduty(FTM2, FTM_CH4, nOut);
    }
    else
    {
        ftm_pwm_fduty(FTM2, FTM_CH4, 0);
        fRightVoltage = -fRightVoltage;
        nOut = fRightVoltage ;
        ftm_pwm_fduty(FTM2, FTM_CH5, nOut);
    }

}

void PWM_Init(void)
{
    ftm_pwm_finit(FTM2, FTM_CH2, 10000, 0);
    ftm_pwm_finit(FTM2, FTM_CH3, 10000, 0);
    ftm_pwm_finit(FTM2, FTM_CH4, 10000, 0);
    ftm_pwm_finit(FTM2, FTM_CH5, 10000, 0);

    gpio_init(PTF2, GPO, 1);
    gpio_init(PTF3, GPO, 1);
    port_pull(PTF2, ENABLE);
    port_pull(PTF3, ENABLE);

}
