################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../usr/xCRC16/crc16.c 

OBJS += \
./usr/xCRC16/crc16.o 

C_DEPS += \
./usr/xCRC16/crc16.d 


# Each subdirectory must supply rules for building sources it contributes
usr/xCRC16/%.o usr/xCRC16/%.su: ../usr/xCRC16/%.c usr/xCRC16/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -DUSE_HAL_DRIVER -DSTM32G031xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I"F:/project/ESL/ESL Project/Aplental_QT/FW FOR APLENTAL QT/APLENTAL QT CONSOLE/usr/board" -I"F:/project/ESL/ESL Project/Aplental_QT/FW FOR APLENTAL QT/APLENTAL QT CONSOLE/usr/xCRC16" -I"F:/project/ESL/ESL Project/Aplental_QT/FW FOR APLENTAL QT/APLENTAL QT CONSOLE/usr/xRingBuffer" -I"F:/project/ESL/ESL Project/Aplental_QT/FW FOR APLENTAL QT/APLENTAL QT CONSOLE/usr/xRs485Dev" -I"F:/project/ESL/ESL Project/Aplental_QT/FW FOR APLENTAL QT/APLENTAL QT CONSOLE/usr/xTask" -I"F:/project/ESL/ESL Project/Aplental_QT/FW FOR APLENTAL QT/APLENTAL QT CONSOLE/usr/xUartDev" -I"F:/project/ESL/ESL Project/Aplental_QT/FW FOR APLENTAL QT/APLENTAL QT CONSOLE/usr/xIIC_IO" -I"F:/project/ESL/ESL Project/Aplental_QT/FW FOR APLENTAL QT/APLENTAL QT CONSOLE/usr/xAt24Cxx" -I"F:/project/ESL/ESL Project/Aplental_QT/FW FOR APLENTAL QT/APLENTAL QT CONSOLE/usr/promise" -I"F:/project/ESL/ESL Project/Aplental_QT/FW FOR APLENTAL QT/APLENTAL QT CONSOLE/usr/xMisc" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-usr-2f-xCRC16

clean-usr-2f-xCRC16:
	-$(RM) ./usr/xCRC16/crc16.d ./usr/xCRC16/crc16.o ./usr/xCRC16/crc16.su

.PHONY: clean-usr-2f-xCRC16

