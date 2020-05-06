################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/SysTick.c \
../source/System.c \
../source/UART.c \
../source/application.c \
../source/led_control.c \
../source/logger.c \
../source/main.c \
../source/mtb.c \
../source/queue.c \
../source/semihost_hardfault.c \
../source/uCUnit_testsuit.c 

OBJS += \
./source/SysTick.o \
./source/System.o \
./source/UART.o \
./source/application.o \
./source/led_control.o \
./source/logger.o \
./source/main.o \
./source/mtb.o \
./source/queue.o \
./source/semihost_hardfault.o \
./source/uCUnit_testsuit.o 

C_DEPS += \
./source/SysTick.d \
./source/System.d \
./source/UART.d \
./source/application.d \
./source/led_control.d \
./source/logger.d \
./source/main.d \
./source/mtb.d \
./source/queue.d \
./source/semihost_hardfault.d \
./source/uCUnit_testsuit.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4_cm0plus -DCPU_MKL25Z128VLK4 -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSDK_DEBUGCONSOLE=1 -I"C:\Users\disha\Documents\MCUXpressoIDE_11.1.0_3209\PES_Project_3\Project_5_UART\board" -I"C:\Users\disha\Documents\MCUXpressoIDE_11.1.0_3209\PES_Project_3\Project_5_UART\source" -I"C:\Users\disha\Documents\MCUXpressoIDE_11.1.0_3209\PES_Project_3\Project_5_UART" -I"C:\Users\disha\Documents\MCUXpressoIDE_11.1.0_3209\PES_Project_3\Project_5_UART\drivers" -I"C:\Users\disha\Documents\MCUXpressoIDE_11.1.0_3209\PES_Project_3\Project_5_UART\CMSIS" -I"C:\Users\disha\Documents\MCUXpressoIDE_11.1.0_3209\PES_Project_3\Project_5_UART\utilities" -I"C:\Users\disha\Documents\MCUXpressoIDE_11.1.0_3209\PES_Project_3\Project_5_UART\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


