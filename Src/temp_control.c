#include "temp_control.h"
#include "adc_driver.h"
#include "uart_driver.h"
#include "pwm_driver.h"
#include <stdio.h>

#define ADC_MAX_VALUE       4095.0f
#define ADC_REF_VOLTAGE     3.3f

#define WARNING_ON_TEMP     30.0f
#define WARNING_OFF_TEMP    28.0f

#define CRITICAL_ON_TEMP    35.0f
#define CRITICAL_OFF_TEMP   33.0f

typedef enum
{
    TEMP_NORMAL,
    TEMP_WARNING,
    TEMP_CRITICAL
} TempState_t;

static TempState_t current_state;

static float ReadTemperatureCelsius(void);
static void UpdateState(float temp_c);
static uint8_t GetDutyCycleFromState(void);
static const char* StateToString(TempState_t state);

void TempControl_Init(void)
{
    current_state = TEMP_NORMAL;
    PWM_SetDutyCycle(20);
}

void TempControl_Update(void)
{
    char msg[120];

    float temp_c = ReadTemperatureCelsius();

    UpdateState(temp_c);

    uint8_t duty_cycle = GetDutyCycleFromState();
    PWM_SetDutyCycle(duty_cycle);

    sprintf(msg,
            "Temp: %.2f C | State: %s | PWM: %u%%\r\n",
            temp_c,
            StateToString(current_state),
            duty_cycle);

    UART2_WriteString(msg);
}

static float ReadTemperatureCelsius(void)
{
    uint16_t adc_value = ADC1_Read();

    float voltage = ((float)adc_value * ADC_REF_VOLTAGE) / ADC_MAX_VALUE;

    // LM35: 10mV per degree Celsius
    return voltage * 100.0f;
}

static void UpdateState(float temp_c)
{
    switch (current_state)
    {
        case TEMP_NORMAL:
            if (temp_c >= CRITICAL_ON_TEMP)
            {
                current_state = TEMP_CRITICAL;
            }
            else if (temp_c >= WARNING_ON_TEMP)
            {
                current_state = TEMP_WARNING;
            }
            break;

        case TEMP_WARNING:
            if (temp_c >= CRITICAL_ON_TEMP)
            {
                current_state = TEMP_CRITICAL;
            }
            else if (temp_c <= WARNING_OFF_TEMP)
            {
                current_state = TEMP_NORMAL;
            }
            break;

        case TEMP_CRITICAL:
            if (temp_c <= CRITICAL_OFF_TEMP)
            {
                current_state = TEMP_WARNING;
            }
            break;

        default:
            current_state = TEMP_NORMAL;
            break;
    }
}

static uint8_t GetDutyCycleFromState(void)
{
    switch (current_state)
    {
        case TEMP_NORMAL:
            return 20;

        case TEMP_WARNING:
            return 60;

        case TEMP_CRITICAL:
            return 100;

        default:
            return 0;
    }
}

static const char* StateToString(TempState_t state)
{
    switch (state)
    {
        case TEMP_NORMAL:
            return "NORMAL";

        case TEMP_WARNING:
            return "WARNING";

        case TEMP_CRITICAL:
            return "CRITICAL";

        default:
            return "UNKNOWN";
    }
}
