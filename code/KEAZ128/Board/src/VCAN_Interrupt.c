#include "VCAN_Interrupt.h"

int g_n1MSEventCount = 0;
int g_nSpeedControlCount = 0;
int g_nDirectionControlCount = 0;

void PIT_Interrupt(void)
{
    int i;

    g_n1MSEventCount++;
    g_nSpeedControlPeriod ++;
    SpeedControlOutput();

    g_nDirectionControlPeriod ++;
    DirectionControlOutput();

    if (g_n1MSEventCount >= 5)
    {
        g_n1MSEventCount = 0;
        GetMotorPulse();      //读取两个电极脉冲计数值
    }

    else if (g_n1MSEventCount == 1)
    {
        for (i = 0; i < INPUT_VOLTAGE_AVERAGE; i ++)   SampleInputVoltage(); //AD采集，平均滤波
    }

    else if (g_n1MSEventCount == 2)
    {
        GetInputVoltageAverage();
        Angle_Calculate();
        Angle_Control();
        MotorOutput();
    }

    else if (g_n1MSEventCount == 3)
    {
        g_nSpeedControlCount ++;
        if (g_nSpeedControlCount >= 20)
        {
            Speed_Control();
            g_nSpeedControlCount = 0;
            g_nSpeedControlPeriod = 0;
        }
    }

    else if (g_n1MSEventCount == 4)
    {
        g_nDirectionControlCount ++;
        DirectionVoltageSigma();
        if (g_nDirectionControlCount >= 2)
        {
            Direction_Control();
            g_nDirectionControlCount = 0;
            g_nDirectionControlPeriod = 0;
        }
    }
}

