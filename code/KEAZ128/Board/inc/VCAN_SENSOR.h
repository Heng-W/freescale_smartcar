#ifndef _VCAN_SENSOR_H
#define _VCAN_SENSOR_H



#include "include.h"

/***********  ���ADC�ɼ�ͨ�� �궨�� *****************/


#define  Induc_1    ADC0_SE0
#define  Induc_2    ADC0_SE1
#define  Induc_3    ADC0_SE8
#define  Induc_4    ADC0_SE9
#define  Induc_5    ADC0_SE10
#define  Induc_6    ADC0_SE11



#define  BAT      ADC0_SE15        //��ص�ѹ���
#define  BAT_VAL  adc_once(ADC0_SE15,ADC_12bit)

extern uint16 voltage_left, voltage_right;
extern uint16 AD_Get[6];

void sensor_init(void); //ad��ʼ��
void sensor_get(void);  //ad����ֵ
void AD_GetValue(void);
void reedswitch_init(void);
void reedswitch_deal(void);
void beep_init(void);
void beep_work(void);

#endif
