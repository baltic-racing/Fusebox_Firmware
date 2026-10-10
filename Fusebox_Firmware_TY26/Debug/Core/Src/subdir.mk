################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/CAN_DATA.c \
../Core/Src/FRO.c \
../Core/Src/adc.c \
../Core/Src/cooling_control.c \
../Core/Src/current_sense.c \
../Core/Src/fdcan.c \
../Core/Src/gpio.c \
../Core/Src/main.c \
../Core/Src/sdc.c \
../Core/Src/stm32g4xx_hal_msp.c \
../Core/Src/stm32g4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32g4xx.c \
../Core/Src/tim.c \
../Core/Src/voltage_sense.c 

OBJS += \
./Core/Src/CAN_DATA.o \
./Core/Src/FRO.o \
./Core/Src/adc.o \
./Core/Src/cooling_control.o \
./Core/Src/current_sense.o \
./Core/Src/fdcan.o \
./Core/Src/gpio.o \
./Core/Src/main.o \
./Core/Src/sdc.o \
./Core/Src/stm32g4xx_hal_msp.o \
./Core/Src/stm32g4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32g4xx.o \
./Core/Src/tim.o \
./Core/Src/voltage_sense.o 

C_DEPS += \
./Core/Src/CAN_DATA.d \
./Core/Src/FRO.d \
./Core/Src/adc.d \
./Core/Src/cooling_control.d \
./Core/Src/current_sense.d \
./Core/Src/fdcan.d \
./Core/Src/gpio.d \
./Core/Src/main.d \
./Core/Src/sdc.d \
./Core/Src/stm32g4xx_hal_msp.d \
./Core/Src/stm32g4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32g4xx.d \
./Core/Src/tim.d \
./Core/Src/voltage_sense.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/CAN_DATA.cyclo ./Core/Src/CAN_DATA.d ./Core/Src/CAN_DATA.o ./Core/Src/CAN_DATA.su ./Core/Src/FRO.cyclo ./Core/Src/FRO.d ./Core/Src/FRO.o ./Core/Src/FRO.su ./Core/Src/adc.cyclo ./Core/Src/adc.d ./Core/Src/adc.o ./Core/Src/adc.su ./Core/Src/cooling_control.cyclo ./Core/Src/cooling_control.d ./Core/Src/cooling_control.o ./Core/Src/cooling_control.su ./Core/Src/current_sense.cyclo ./Core/Src/current_sense.d ./Core/Src/current_sense.o ./Core/Src/current_sense.su ./Core/Src/fdcan.cyclo ./Core/Src/fdcan.d ./Core/Src/fdcan.o ./Core/Src/fdcan.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/sdc.cyclo ./Core/Src/sdc.d ./Core/Src/sdc.o ./Core/Src/sdc.su ./Core/Src/stm32g4xx_hal_msp.cyclo ./Core/Src/stm32g4xx_hal_msp.d ./Core/Src/stm32g4xx_hal_msp.o ./Core/Src/stm32g4xx_hal_msp.su ./Core/Src/stm32g4xx_it.cyclo ./Core/Src/stm32g4xx_it.d ./Core/Src/stm32g4xx_it.o ./Core/Src/stm32g4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32g4xx.cyclo ./Core/Src/system_stm32g4xx.d ./Core/Src/system_stm32g4xx.o ./Core/Src/system_stm32g4xx.su ./Core/Src/tim.cyclo ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/tim.su ./Core/Src/voltage_sense.cyclo ./Core/Src/voltage_sense.d ./Core/Src/voltage_sense.o ./Core/Src/voltage_sense.su

.PHONY: clean-Core-2f-Src

