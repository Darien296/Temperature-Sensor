#include "stm32f407xx.h"
#include "adc_driver.h"

static uint8_t adc_channel;

void ADC1_Init(ADC_Config_t *config)
{
    adc_channel = config->channel;

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    GPIOA->MODER &= ~(3U << (adc_channel * 2));
    GPIOA->MODER |=  (3U << (adc_channel * 2));

    ADC1->SQR3 = adc_channel;

    ADC1->CR2 |= ADC_CR2_ADON;
}

uint16_t ADC1_Read(void)
{
    ADC1->CR2 |= ADC_CR2_SWSTART;

    while (!(ADC1->SR & ADC_SR_EOC));

    return (uint16_t)ADC1->DR;
}
