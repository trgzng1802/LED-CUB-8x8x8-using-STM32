################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32f042f6px.s 

OBJS += \
./Core/Startup/startup_stm32f042f6px.o 

S_DEPS += \
./Core/Startup/startup_stm32f042f6px.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m0 -g3 -DDEBUG -c -I"D:/LED CUBE 8x8x8/LED CUBE 8x8x8 STM32/code ledcube/Libs" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32f042f6px.d ./Core/Startup/startup_stm32f042f6px.o

.PHONY: clean-Core-2f-Startup

