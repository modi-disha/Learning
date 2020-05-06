################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/Accelerometer.c \
../source/I2C.c \
../source/MMA8451Q.c \
../source/SPI.c \
../source/SysTick.c \
../source/System.c \
../source/led_control.c \
../source/logger.c \
../source/loopback.c \
../source/main.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/slider.c \
../source/uCUnit_testsuit.c 

OBJS += \
./source/Accelerometer.o \
./source/I2C.o \
./source/MMA8451Q.o \
./source/SPI.o \
./source/SysTick.o \
./source/System.o \
./source/led_control.o \
./source/logger.o \
./source/loopback.o \
./source/main.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/slider.o \
./source/uCUnit_testsuit.o 

C_DEPS += \
./source/Accelerometer.d \
./source/I2C.d \
./source/MMA8451Q.d \
./source/SPI.d \
./source/SysTick.d \
./source/System.d \
./source/led_control.d \
./source/logger.d \
./source/loopback.d \
./source/main.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/slider.d \
./source/uCUnit_testsuit.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4_cm0plus -DCPU_MKL25Z128VLK4 -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=1 -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\disha\Documents\MCUXpressoIDE_11.1.0_3209\PES_Project_3\Project_4_STATEMACHINE\board" -I"C:\Users\disha\Documents\MCUXpressoIDE_11.1.0_3209\PES_Project_3\Project_4_STATEMACHINE\source" -I"C:\Users\disha\Documents\MCUXpressoIDE_11.1.0_3209\PES_Project_3\Project_4_STATEMACHINE" -I"C:\Users\disha\Documents\MCUXpressoIDE_11.1.0_3209\PES_Project_3\Project_4_STATEMACHINE\drivers" -I"C:\Users\disha\Documents\MCUXpressoIDE_11.1.0_3209\PES_Project_3\Project_4_STATEMACHINE\CMSIS" -I"C:\Users\disha\Documents\MCUXpressoIDE_11.1.0_3209\PES_Project_3\Project_4_STATEMACHINE\utilities" -I"C:\Users\disha\Documents\MCUXpressoIDE_11.1.0_3209\PES_Project_3\Project_4_STATEMACHINE\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


