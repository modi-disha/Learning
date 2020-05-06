################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/allocate_mem.c \
../source/command_parser.c \
../source/compare_pattern.c \
../source/display_mem.c \
../source/free_mem.c \
../source/invert_mem.c \
../source/logger.c \
../source/main.c \
../source/miscellaneous.c \
../source/mtb.c \
../source/prng.c \
../source/semihost_hardfault.c \
../source/uCUnit_testsuit.c \
../source/verify_mem.c \
../source/write_mem.c \
../source/write_pattern.c 

OBJS += \
./source/allocate_mem.o \
./source/command_parser.o \
./source/compare_pattern.o \
./source/display_mem.o \
./source/free_mem.o \
./source/invert_mem.o \
./source/logger.o \
./source/main.o \
./source/miscellaneous.o \
./source/mtb.o \
./source/prng.o \
./source/semihost_hardfault.o \
./source/uCUnit_testsuit.o \
./source/verify_mem.o \
./source/write_mem.o \
./source/write_pattern.o 

C_DEPS += \
./source/allocate_mem.d \
./source/command_parser.d \
./source/compare_pattern.d \
./source/display_mem.d \
./source/free_mem.d \
./source/invert_mem.d \
./source/logger.d \
./source/main.d \
./source/miscellaneous.d \
./source/mtb.d \
./source/prng.d \
./source/semihost_hardfault.d \
./source/uCUnit_testsuit.d \
./source/verify_mem.d \
./source/write_mem.d \
./source/write_pattern.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4_cm0plus -DCPU_MKL25Z128VLK4 -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\disha\Documents\MCUXpressoIDE_11.1.0_3209\PES_Project_3\Project_3\board" -I"C:\Users\disha\Documents\MCUXpressoIDE_11.1.0_3209\PES_Project_3\Project_3\source" -I"C:\Users\disha\Documents\MCUXpressoIDE_11.1.0_3209\PES_Project_3\Project_3" -I"C:\Users\disha\Documents\MCUXpressoIDE_11.1.0_3209\PES_Project_3\Project_3\drivers" -I"C:\Users\disha\Documents\MCUXpressoIDE_11.1.0_3209\PES_Project_3\Project_3\CMSIS" -I"C:\Users\disha\Documents\MCUXpressoIDE_11.1.0_3209\PES_Project_3\Project_3\utilities" -I"C:\Users\disha\Documents\MCUXpressoIDE_11.1.0_3209\PES_Project_3\Project_3\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


