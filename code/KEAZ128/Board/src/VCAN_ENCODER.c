#include "VCAN_ENCODER.h"

int16 speedl, speedr;
int32 leftMotorPulseSigma = 0, rightMotorPulseSigma = 0;

void Encoder_Init(void)
{
    //ftm�ļ������ſɲ鿴KEA128_port_cfg.h�ļ��ڵ�FTM0_COUNT_PIN��FTM1_COUNT_PIN�ĺ궨���֪
    //һ��ftmͬһʱ��ֻ��ʵ��һ�ֹ��ܣ�������ڲ��پͲ����������PWM
    ftm_pulse_init(FTM2, FTM_PS_1, TCLK0);   //��E0���������������м���    E0�ӱ�����LSB
    gpio_init(PTC5, GPI, 0);  //�����жϷ���                  C5�ӱ�����DIR
    port_pull(PTC5, ENABLE);         //IO����

    ftm_pulse_init(FTM2, FTM_PS_1, TCLK1);   //��E7���������������м���    E7�ӱ�����LSB
    gpio_init(PTH5, GPI, 0);  //�����жϷ���                  H5�ӱ�����DIR
    port_pull(PTH5, ENABLE);         //IO����
}

void GetMotorPulse(void)
{
    uint16 temp1, temp2;       //��ȡ�ٶ���Ϣ
    temp1 = ftm_pulse_get(FTM0) ; //����ֵ
    temp2 = ftm_pulse_get(FTM1);
    //����������
    ftm_pulse_clean(FTM0) ;
    ftm_pulse_clean(FTM1) ;
    //���ݷ����ź��ж����������跽���ź��Ǹߵ�ƽʱΪ��ת
    if (gpio_get(PTC5))    speedl = -((int16)(temp1)); //�ٶ�ȡ��
    else                speedl = temp1;
    if (gpio_get(PTH5))    speedr = -((int16)(temp2)); //�ٶ�ȡ��
    else                speedr = temp2;

    leftMotorPulseSigma +=  speedl;
    rightMotorPulseSigma +=  speedr;
}