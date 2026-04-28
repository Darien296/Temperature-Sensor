################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/adc_driver.c \
../Src/main.c \
../Src/pwm_driver.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/temp_control.c \
../Src/timer_driver.c \
../Src/uart_driver.c 

OBJS += \
./Src/adc_driver.o \
./Src/main.o \
./Src/pwm_driver.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/temp_control.o \
./Src/timer_driver.o \
./Src/uart_driver.o 

C_DEPS += \
./Src/adc_driver.d \
./Src/main.d \
./Src/pwm_driver.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/temp_control.d \
./Src/timer_driver.d \
./Src/uart_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/adc_driver.cyclo ./Src/adc_driver.d ./Src/adc_driver.o ./Src/adc_driver.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/pwm_driver.cyclo ./Src/pwm_driver.d ./Src/pwm_driver.o ./Src/pwm_driver.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/temp_control.cyclo ./Src/temp_control.d ./Src/temp_control.o ./Src/temp_control.su ./Src/timer_driver.cyclo ./Src/timer_driver.d ./Src/timer_driver.o ./Src/timer_driver.su ./Src/uart_driver.cyclo ./Src/uart_driver.d ./Src/uart_driver.o ./Src/uart_driver.su

.PHONY: clean-Src

