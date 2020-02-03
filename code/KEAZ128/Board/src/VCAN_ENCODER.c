#include "VCAN_ENCODER.h"

int16 speedl, speedr;
int32 leftMotorPulseSigma = 0, rightMotorPulseSigma = 0;

void Encoder_Init(void)
{
    //ftm的计数引脚可查看KEA128_port_cfg.h文件内的FTM0_COUNT_PIN与FTM1_COUNT_PIN的宏定义得知
    //一个ftm同一时间只能实现一种功能，如果用于测速就不能用于输出PWM
    ftm_pulse_init(FTM2, FTM_PS_1, TCLK0);   //对E0引脚输入的脉冲进行计数    E0接编码器LSB
    gpio_init(PTC5, GPI, 0);  //用于判断方向                  C5接编码器DIR
    port_pull(PTC5, ENABLE);         //IO上拉

    ftm_pulse_init(FTM2, FTM_PS_1, TCLK1);   //对E7引脚输入的脉冲进行计数    E7接编码器LSB
    gpio_init(PTH5, GPI, 0);  //用于判断方向                  H5接编码器DIR
    port_pull(PTH5, ENABLE);         //IO上拉
}

void GetMotorPulse(void)
{
    uint16 temp1, temp2;       //获取速度信息
    temp1 = ftm_pulse_get(FTM0) ; //计数值
    temp2 = ftm_pulse_get(FTM1);
    //计数器清零
    ftm_pulse_clean(FTM0) ;
    ftm_pulse_clean(FTM1) ;
    //根据方向信号判断正负，假设方向信号是高电平时为反转
    if (gpio_get(PTC5))    speedl = -((int16)(temp1)); //速度取负
    else                speedl = temp1;
    if (gpio_get(PTH5))    speedr = -((int16)(temp2)); //速度取负
    else                speedr = temp2;

    leftMotorPulseSigma +=  speedl;
    rightMotorPulseSigma +=  speedr;
}