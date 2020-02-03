#include "VCAN_key.h"

int out1 = 0;
int out2 = 0;

PTXn_e KEY_PTxn[KEYALL] = {PTG0, PTG1, PTG2, PTG5, PTG6, PTG7};
int key1_count = 0, key1_flag = 0;
int key2_count = 0, key2_flag = 0;
int key3_count = 0, key3_flag = 0;


void key_init(void)
{
    for (int i = 0; i < KEYALL; i++)
    {
        gpio_init(KEY_PTxn[i], GPI, 1);
        port_pull(KEY_PTxn[i], ENABLE);
    }
}




/*!
 *  @brief      获取key状态（不带延时消抖）
 *  @param      KEY_e           KEY编号
 *  @return     KEY_STATUS_e    KEY状态（KEY_DOWN、KEY_DOWN）
 *  @since      v5.0
 *  Sample usage:
                    if(key_get(KEY_U) ==  KEY_DOWN)
                    {
                        printf("\n按键按下")
                    }
 */
KEY_STATUS_e key_get(KEY_e key)
{
    if (gpio_get(KEY_PTxn[key]) == KEY_DOWN)
    {
        return KEY_DOWN;
    }
    return KEY_UP;
}


/*!
 *  @brief      检测key状态（带延时消抖）
 *  @param      KEY_e           KEY编号
 *  @return     KEY_STATUS_e    KEY状态（KEY_DOWN、KEY_DOWN）
 *  @since      v5.0
 *  Sample usage:
                    if(key_check(KEY_U) ==  KEY_DOWN)
                    {
                        printf("\n按键按下")
                    }
 */
KEY_STATUS_e key_check(KEY_e key)
{
    if (key_get(key) == KEY_DOWN)
    {
        systick_delay_ms(10);
        if (key_get(key) == KEY_DOWN)
        {
            return KEY_DOWN;
        }
    }
    return KEY_UP;
}

void key_dispose(void)
{
    if (key1_flag == 1 && !gpio_get(PTG7))
    {
        key1_flag = 0;
        DIR_CONTROL_P += 0.2;
    }

    if (key1_flag == 1 && gpio_get(PTG7))
    {
        key1_flag = 0;
        DIR_CONTROL_P -= 0.2;
    }

    if (key2_flag == 1 && !gpio_get(PTG7))
    {
        key2_flag = 0;
        // SPEED_CONTROL_I+=0.002;
    }

    if (key2_flag == 1 && gpio_get(PTG7))
    {
        key2_flag = 0;
        //SPEED_CONTROL_I-=0.002;
    }

    if (key3_flag == 1 && gpio_get(PTG7))
    {
        key3_flag = 0;
        CAR_SPEED_SET -= 0.5; // SPEED_CONTROL_P-=0.02;

    }

    if (key3_flag == 1 && !gpio_get(PTG7))
    {
        key3_flag = 0;
        CAR_SPEED_SET += 0.5; //SPEED_CONTROL_P+=0.02;

    }


    if (key2_flag == 1 && !gpio_get(PTG7) && gpio_get(PTG6))
    {
        key2_flag = 0;
        Car_angle_D += 0.02;
    }

    if (key2_flag == 1 && gpio_get(PTG7) && gpio_get(PTG6))
    {
        key2_flag = 0;
        Car_angle_D -= 0.02;
    }

    if (key3_flag == 1 && gpio_get(PTG7) && gpio_get(PTG6))
    {
        key3_flag = 0;
        Car_angle_P -= 0.2;

    }

    if (key3_flag == 1 && !gpio_get(PTG7) && gpio_get(PTG6))
    {
        key3_flag = 0;
        Car_angle_P += 0.2;

    }
}

void key_scan(void)
{
    if (key_get(KEY1) == KEY_DOWN) key1_count++;
    else key1_count = 0;
    if (key1_count == 2)  key1_flag = 1;

    if (key_get(KEY2) == KEY_DOWN) key2_count++;
    else key2_count = 0;
    if (key2_count == 2)  key2_flag = 1;

    if (key_get(KEY3) == KEY_DOWN) key3_count++;
    else key3_count = 0;
    if (key3_count == 2)  key3_flag = 1;
}

