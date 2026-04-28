#include "stm32f407xx.h"
#include "adc_driver.h"
#include "uart_driver.h"
#include "timer_driver.h"
#include "pwm_driver.h"
#include "temp_control.h"
#include <stdint.h>

volatile uint8_t sample_flag = 0;

int main(void)
{
    ADC_Config_t adc_config = {
        .channel = 1   // PA1 = ADC1_IN1
    };

    UART2_Init();
    ADC1_Init(&adc_config);
    PWM_TIM3_CH1_Init();
    TIM2_Interrupt_Init_1Hz();

    TempControl_Init();

    UART2_WriteString("STM32F407 Real-Time Temperature Control System Started\r\n");

    while (1)
    {
        if (sample_flag)
        {
            sample_flag = 0;
            TempControl_Update();
        }
    }
}

void TIM2_IRQHandler(void)
{
    if (TIM2->SR & TIM_SR_UIF)
    {
        TIM2->SR &= ~TIM_SR_UIF;
        sample_flag = 1;
    }
}
