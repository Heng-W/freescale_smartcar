#ifndef _VCAN_KEY_H
#define _VCAN_KEY_H

#include "include.h"



//----宏定义KEY引脚----
#define  KEY_1_PIN  PTG0
#define  KEY_2_PIN  PTG1
#define  KEY_3_PIN  PTG2
#define  SW_1_PIN   PTG5
#define  SW_2_PIN   PTG6
#define  SW_3_PIN   PTG7


//下面是定义按键的时间，单位为 ： 10ms（中断时间）
#define KEY_DOWN_TIME           1       //消抖确认按下时间
#define KEY_HOLD_TIME           50      //长按hold确认时间，最多253，否则需要修改 keytime 的类型
//如果按键一直按下去，则每隔 KEY_HOLD_TIME - KEY_DOWN_TIME 时间会发送一个 KEY_HOLD 消息

//定义按键消息FIFO大小
#define KEY_MSG_FIFO_SIZE       20      //最多 255，否则需要修改key_msg_front/key_msg_rear类型

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


//按键消息结构体
typedef struct
{
    KEY_e           key;        //按键编号
    KEY_STATUS_e    status;     //按键状态
} KEY_MSG_t;

extern int out1;
extern int out2;

void  key_init(void);
KEY_STATUS_e key_check(KEY_e key);
void key_dispose(void);
void key_scan(void);

#endif