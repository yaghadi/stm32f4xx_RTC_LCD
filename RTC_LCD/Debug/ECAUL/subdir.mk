################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ECAUL/LCD.c 

OBJS += \
./ECAUL/LCD.o 

C_DEPS += \
./ECAUL/LCD.d 


# Each subdirectory must supply rules for building sources it contributes
ECAUL/%.o ECAUL/%.su ECAUL/%.cyclo: ../ECAUL/%.c ECAUL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"C:/Users/PurplE/Documents/RTC_LCD/RTC_LCD/ECAUL" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-ECAUL

clean-ECAUL:
	-$(RM) ./ECAUL/LCD.cyclo ./ECAUL/LCD.d ./ECAUL/LCD.o ./ECAUL/LCD.su

.PHONY: clean-ECAUL

