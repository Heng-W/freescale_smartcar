/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2017,ɽ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�ɽ����̳ http://www.vcan123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��Ƽ����У�δ������������������ҵ��;��
 *     �޸�����ʱ���뱣��ɽ��Ƽ��İ�Ȩ������
 *
 * @file       KEA128_it.c
 * @brief      ɽ��KEA ƽ̨������
 * @author     ɽ��Ƽ�
 * @version    v6.0
 * @date       2017-12-10
 */


#include "common.h"
#include "include.h"
#include  "MKEA128_it.h"



void pit0_irq(void)
{
    PIT_Flag_Clear(PIT0);       //���жϱ�־λ
    PIT_Interrupt();
}


void pit1_irq(void)
{
    PIT_Flag_Clear(PIT1);
    key_scan();
}