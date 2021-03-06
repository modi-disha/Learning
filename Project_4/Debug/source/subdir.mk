################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/Accelerometer.c \
../source/I2C.c \
../source/LIS331.c \
../source/main.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/slider.c 

OBJS += \
./source/Accelerometer.o \
./source/I2C.o \
./source/LIS331.o \
./source/main.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/slider.o 

C_DEPS += \
./source/Accelerometer.d \
./source/I2C.d \
./source/LIS331.d \
./source/main.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/slider.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MKL25Z128VLK4_cm0plus -DCPU_MKL25Z128VLK4 -DDEBUG -DPRINTF_FLOAT_ENABLE=0 -DSCANF_FLOAT_ENABLE=0 -DPRINTF_ADVANCED_ENABLE=0 -DSCANF_ADVANCED_ENABLE=0 -DFRDM_KL25Z -DFREEDOM -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -I"C:\Users\disha\Documents\MCUXpressoIDE_11.1.0_3209\PES_Project_3\Project_4\board" -I"C:\Users\disha\Documents\MCUXpressoIDE_11.1.0_3209\PES_Project_3\Project_4\source" -I"C:\Users\disha\Documents\MCUXpressoIDE_11.1.0_3209\PES_Project_3\Project_4" -I"C:\Users\disha\Documents\MCUXpressoIDE_11.1.0_3209\PES_Project_3\Project_4\drivers" -I"C:\Users\disha\Documents\MCUXpressoIDE_11.1.0_3209\PES_Project_3\Project_4\CMSIS" -I"C:\Users\disha\Documents\MCUXpressoIDE_11.1.0_3209\PES_Project_3\Project_4\utilities" -I"C:\Users\disha\Documents\MCUXpressoIDE_11.1.0_3209\PES_Project_3\Project_4\startup" -O0 -fno-common -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


