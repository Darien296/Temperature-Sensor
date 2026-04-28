#include "stm32f407xx.h"
#include "pwm_driver.h"

void PWM_TIM3_CH1_Init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    // PA6 = TIM3_CH1
    GPIOA->MODER &= ~(3U << (6 * 2));
    GPIOA->MODER |=  (2U << (6 * 2));

    // AF2 for TIM3
    GPIOA->AFR[0] &= ~(0xFU << (6 * 4));
    GPIOA->AFR[0] |=  (2U << (6 * 4));

    // 100 Hz PWM assuming 16 MHz clock
    TIM3->PSC = 160 - 1;
    TIM3->ARR = 1000 - 1;

    // PWM mode 1 on channel 1
    TIM3->CCMR1 &= ~TIM_CCMR1_OC1M;
    TIM3->CCMR1 |=  (6U << 4);

    TIM3->CCMR1 |= TIM_CCMR1_OC1PE;
    TIM3->CCER  |= TIM_CCER_CC1E;

    TIM3->CCR1 = 0;

    TIM3->CR1 |= TIM_CR1_ARPE;
    TIM3->CR1 |= TIM_CR1_CEN;
}

void PWM_SetDutyCycle(uint8_t duty_percent)
{
    if (duty_percent > 100)
    {
        duty_percent = 100;
    }

    TIM3->CCR1 = (duty_percent * 1000) / 100;
}
