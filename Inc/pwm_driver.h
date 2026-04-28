#ifndef PWM_DRIVER_H
#define PWM_DRIVER_H

#include <stdint.h>

void PWM_TIM3_CH1_Init(void);
void PWM_SetDutyCycle(uint8_t duty_percent);

#endif
