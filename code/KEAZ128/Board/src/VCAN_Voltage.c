#include "VCAN_Voltage.h"

int g_nInputVoltageCount = 0;
uint32 g_lnInputVoltageSigma[6] = {0};
uint16 g_nInputVoltage[6] = {0};


void SampleInputVoltage(void)
{
    uint16 nInputVoltage[6];
    int i;
    sensor_get();
    for (i = 0; i < 6; i++)
        nInputVoltage[i] = AD_Get[i];
    for (i = 0; i < 6; i++)
        g_lnInputVoltageSigma[i] += nInputVoltage[i];
    g_nInputVoltageCount ++;
}

void GetInputVoltageAverage(void)
{
    int i;

    if (g_nInputVoltageCount == 0)
    {
        for (i = 0; i < 6; i ++)
            g_lnInputVoltageSigma[i] = 0;
    }
    else
    {
        for (i = 0; i < 6; i ++)
        {
            g_nInputVoltage[i] = (int)(g_lnInputVoltageSigma[i] / g_nInputVoltageCount);
            g_lnInputVoltageSigma[i] = 0;
        }
        g_nInputVoltageCount = 0;
        for (i = 0; i < 6; i++)
            AD_Get[i] = g_nInputVoltage[i];
    }
}


void DirectionVoltageSigma(void)
{
    int Left1, Right1;
    AD_GetValue();
    if (voltage_left > DIR_LEFT_OFFSET)
        Left1 = voltage_left - DIR_LEFT_OFFSET;
    else Left1 = 0;
    if (voltage_right > DIR_RIGHT_OFFSET)
        Right1 = voltage_right - DIR_RIGHT_OFFSET;
    else Right1 = 0;

    g_fLeftVoltageSigma += Left1;
    g_fRightVoltageSigma += Right1;
}

