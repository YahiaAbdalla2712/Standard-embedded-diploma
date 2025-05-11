################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP.c \
../DC_motor.c \
../FlameSensor.c \
../LDR_sensor.c \
../PWM_TIMER0.c \
../adc.c \
../buzzer.c \
../gpio.c \
../lcd.c \
../leds.c \
../lm35_sensor.c 

OBJS += \
./APP.o \
./DC_motor.o \
./FlameSensor.o \
./LDR_sensor.o \
./PWM_TIMER0.o \
./adc.o \
./buzzer.o \
./gpio.o \
./lcd.o \
./leds.o \
./lm35_sensor.o 

C_DEPS += \
./APP.d \
./DC_motor.d \
./FlameSensor.d \
./LDR_sensor.d \
./PWM_TIMER0.d \
./adc.d \
./buzzer.d \
./gpio.d \
./lcd.d \
./leds.d \
./lm35_sensor.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


