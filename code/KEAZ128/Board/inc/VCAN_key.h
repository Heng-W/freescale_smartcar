#ifndef _VCAN_KEY_H
#define _VCAN_KEY_H

#include "include.h"



//----�궨��KEY����----
#define  KEY_1_PIN  PTG0
#define  KEY_2_PIN  PTG1
#define  KEY_3_PIN  PTG2
#define  SW_1_PIN   PTG5
#define  SW_2_PIN   PTG6
#define  SW_3_PIN   PTG7


//�����Ƕ��尴����ʱ�䣬��λΪ �� 10ms���ж�ʱ�䣩
#define KEY_DOWN_TIME           1       //����ȷ�ϰ���ʱ��
#define KEY_HOLD_TIME           50      //����holdȷ��ʱ�䣬���253��������Ҫ�޸� keytime ������
//�������һֱ����ȥ����ÿ�� KEY_HOLD_TIME - KEY_DOWN_TIME ʱ��ᷢ��һ�� KEY_HOLD ��Ϣ

//���尴����ϢFIFO��С
#define KEY_MSG_FIFO_SIZE       20      //��� 255��������Ҫ�޸�key_msg_front/key_msg_rear����

typedef enum
{
    KEY1 = 0,
    KEY2 = 1,
    KEY3 = 2,
    SW1 = 3,
    SW2 = 4,
    SW3 = 5,
    KEYALL = 6
} KEY_e;


typedef enum
{

    KEY_DOWN = 0,
    KEY_UP = 1,
    KEYFAIL = 0xFF,
} KEY_STATUS_e;


//������Ϣ�ṹ��
typedef struct
{
    KEY_e           key;        //�������
    KEY_STATUS_e    status;     //����״̬
} KEY_MSG_t;

extern int out1;
extern int out2;

void  key_init(void);
KEY_STATUS_e key_check(KEY_e key);
void key_dispose(void);
void key_scan(void);

#endif