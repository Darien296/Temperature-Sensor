#include "stm32f407xx.h"
#include "timer_driver.h"

void TIM2_Interrupt_Init_1Hz(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    // Assuming 16 MHz system clock:
    // 16 MHz / 16000 = 1000 Hz
    // 1000 Hz / 1000 = 1 Hz interrupt
    TIM2->PSC = 16000 - 1;
    TIM2->ARR = 1000 - 1;

    TIM2->DIER |= TIM_DIER_UIE;

    NVIC_EnableIRQ(TIM2_IRQn);

    TIM2->CR1 |= TIM_CR1_CEN;
}
