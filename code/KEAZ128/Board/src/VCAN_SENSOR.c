#include "VCAN_SENSOR.h"

uint16 AD_Get[6] = {0};
int beep_flag = 0;
int start_flag = 0, allow_flag = 0, stop_flag = 0;
int rcount = 0, start_time_count = 0, rstatus;
int count = 0;
uint16 voltage_left, voltage_right;

void sensor_init(void)
{
    adc_init(Induc_1);
    adc_init(Induc_2);
    adc_init(Induc_3);
    adc_init(Induc_4);
    adc_init(Induc_5);
    adc_init(Induc_6);
}

/**********电感数据采集*********/
void sensor_get(void)
{
    AD_Get[0] = adc_once(Induc_1, ADC_8bit);
    AD_Get[1] = adc_once(Induc_2, ADC_8bit);
    AD_Get[2] = adc_once(Induc_3, ADC_8bit);
    AD_Get[3] = adc_once(Induc_4, ADC_8bit);
    AD_Get[4] = adc_once(Induc_5, ADC_8bit);
    AD_Get[5] = adc_once(Induc_6, ADC_8bit);
}

void AD_GetValue(void)
{
    voltage_left = (AD_Get[0] + AD_Get[1] + AD_Get[2]) / 3;
    voltage_right = (AD_Get[3] + AD_Get[4] + AD_Get[5]) / 3;
}

void reedswitch_init(void)
{
    gpio_init(PTB1, GPI, 1);
    port_pull(PTB1, ENABLE);

    gpio_init(PTB2, GPI, 1);
    port_pull(PTB2, ENABLE);
}

void reedswitch_deal(void)
{
    uint8 left_reedstatus = gpio_get(PTB1);
    uint8 right_reedstatus = gpio_get(PTB2);
    if (!left_reedstatus && !right_reedstatus)
        start_flag = 1;
    if (start_flag)
        start_time_count++;
    if (start_time_count > 2000)
    {
        if (!left_reedstatus && !right_reedstatus)
            stop_flag = 1;
    }
}

void beep_init(void)
{
    gpio_init(PTD4, GPO, 0);
}

void beep_work(void)
{
    if (beep_flag == 1)
        gpio_set(PTD4, 1);
}

/*uint16 ad_ave(ADCn adcn,ADC_Ch ch,ADC_nbit bit,u8 N) //均值滤波
{    u32 tmp = 0;  u8  i;
    for(i = 0; i < N; i++)
        tmp += ad_once(adcn,ch,bit);
    tmp = tmp / N;
    return (u16)tmp;*/