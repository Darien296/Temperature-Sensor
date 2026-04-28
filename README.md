# STM32 Real-Time Temperature Control System

## Overview
This project implements a real-time temperature monitoring and control system on the STM32F407 Discovery board. The system samples an analog temperature sensor at fixed intervals, processes the data using a state machine with hysteresis, and dynamically adjusts a PWM output to simulate temperature-based control behavior.

## Features
- ADC-based temperature sensing (LM35 analog sensor)
- Hardware timer interrupt for deterministic 1 Hz sampling
- PWM output control using TIM3
- State machine with hysteresis to prevent unstable switching
- UART logging for real-time monitoring and debugging
- Register-level implementation (no HAL)

## System Architecture
ADC → Timer Interrupt → State Machine → PWM Output → UART Logging

## Peripherals Used
- ADC1 (Analog input)
- TIM2 (Periodic interrupt for sampling)
- TIM3 (PWM generation)
- USART2 (Serial communication)

## How It Works
1. TIM2 generates an interrupt every 1 second
2. The interrupt sets a flag for sampling
3. The main loop reads the ADC value and converts it to temperature
4. A state machine determines system behavior:
   - NORMAL
   - WARNING
   - CRITICAL
5. Hysteresis is used to prevent rapid switching near thresholds
6. PWM duty cycle is adjusted based on the current state
7. System status is printed over UART

## Example Output
Temp: 27.5 C | State: NORMAL | PWM: 20%
Temp: 31.2 C | State: WARNING | PWM: 60%
Temp: 36.8 C | State: CRITICAL | PWM: 100%

Used a heat gun to get varying outputs

## Hardware Setup
- STM32F407 Discovery Board
- LM35 Temperature Sensor
- Sensor Output → PA1 (ADC1_IN1)
- UART TX → PA2
- PWM Output → PA6 (TIM3_CH1)

## Key Concepts Demonstrated
- Real-time embedded system design
- Interrupt-driven scheduling
- ADC signal acquisition and conversion
- PWM-based control systems
- Hysteresis for system stability
- Driver-based code architecture

## Challenges & Solutions
- **Unstable output near thresholds**
  - Solved using hysteresis to stabilize state transitions
- **Ensuring consistent sampling**
  - Solved using hardware timer interrupts instead of delay loops

## Future Improvements
- DMA-based ADC sampling
- Moving average or digital filtering
- RTOS-based task scheduling
- Support for digital sensors (I2C/SPI)

## Author
Darien Woods
Computer Engineering Student | Embedded Systems Focus
