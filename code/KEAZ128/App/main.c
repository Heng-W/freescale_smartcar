#include "common.h"
#include "include.h"


void main(void)
{
    DisableInterrupts;

    sensor_init();
    Encoder_Init();
    OLED_Init();
    key_init();
    IIC_init();
    systick_delay_ms(50);
    InitMPU6050();

    pit_init_ms(PIT0, 1);
    pit_init_ms(PIT1, 10);
    //uart_init(uart0,9600);
    PWM_Init();
    systick_delay_ms(50);

    set_irq_priority(PIT_CH0_IRQn, 2);
    set_irq_priority(PIT_CH1_IRQn, 1);
    //set_irq_priority(UART0_IRQn,0);
    enable_irq(PIT_CH0_IRQn);
    enable_irq(PIT_CH1_IRQn);
    //uart_rx_irq_en(uart0);

    EnableInterrupts;

    while (1)
    {
        key_dispose();
    }
}
