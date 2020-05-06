################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_flash.c \
../drivers/fsl_gpio.c \
../drivers/fsl_lpsci.c \
../drivers/fsl_smc.c \
../drivers/fsl_uart.c 

OBJS += \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_flash.o \
./drivers/fsl_gpio.o \
./drivers/fsl_lpsci.o \
./drivers/fsl_smc.o \
./drivers/fsl_uart.o 

C_DEPS += \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_flash.d \
./drivers/fsl_gpio.d \
./drivers/fsl_lpsci.d \
./drivers/fsl_smc.d \
./drivers/fsl_uart.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MKL25Z128VLK4_cm0plus -DCPU_MKL25Z128VLK4 -DDEBUG -DPRINTF_FLOAT_ENABLE=0 -DSCANF_FLOAT_ENABLE=0 -DPRINTF_ADVANCED_ENABLE=0 -DSCANF_ADVANCED_ENABLE=0 -DFRDM_KL25Z -DFREEDOM -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -I"C:\Users\disha\Documents\MCUXpressoIDE_11.1.0_3209\PES_Project_3\Project_4\board" -I"C:\Users\disha\Documents\MCUXpressoIDE_11.1.0_3209\PES_Project_3\Project_4\source" -I"C:\Users\disha\Documents\MCUXpressoIDE_11.1.0_3209\PES_Project_3\Project_4" -I"C:\Users\disha\Documents\MCUXpressoIDE_11.1.0_3209\PES_Project_3\Project_4\drivers" -I"C:\Users\disha\Documents\MCUXpressoIDE_11.1.0_3209\PES_Project_3\Project_4\CMSIS" -I"C:\Users\disha\Documents\MCUXpressoIDE_11.1.0_3209\PES_Project_3\Project_4\utilities" -I"C:\Users\disha\Documents\MCUXpressoIDE_11.1.0_3209\PES_Project_3\Project_4\startup" -O0 -fno-common -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


