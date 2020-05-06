
/*****************************************************************************
 * Copyright (C) 2020 by Disha Modi and Alexandra Paquin
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Disha Modi, Alexandra Paquin, and the University of Colorado are not
 * liable for any misuse of this material.
 *
******************************************************************************/
/**
 * @file methods.h
 * @brief An abstraction for all method enumeration for logging.
 *
 * This header file provides an abstraction for all method enumeration for logging.
 *
 * @author Disha Modi and Alexandra Paquin
 * @date March 2020
 * @version 1.0
 *
 */

#ifndef METHODS_H_
#define METHODS_H_

typedef enum {
	/* Accelerometer methods */
	Read_XYZ_Acc_Handler_f,
	Process_Acc_Handler_f,
	Poll_Slider_Handler_f,
	Acc_Disconnect_Handler_f,
	POST_Test_Handler_f,
	display_accel_f,
	read_event_f,

	/* I2C methods */
	I2C_init_f,
	i2c_start_f,
	i2c_read_setup_f,
	i2c_repeated_read_f,
	i2c_read_byte_f,
	i2c_write_byte_f,
	i2c_busy_f,
	i2c_wait_f,
	read_i2c_lock_f,
	Enable_irq_f,
	Disable_irq_f,

	/* LED methods */
	LED_init_f,
	LED_SetPinsOutput_f,
	LED_ClearPinsOutput_f,
	LED_PinInit_f,
	LED_SetAll_f,
	LED_ClearRed_f,
	LED_ClearGreen_f,
	LED_ClearBlue_f,

	/* Logger methods */
	log_level_f,
	log_status_f,

	/* Loopback methods */
	Loopback_f,
	Display_Loopback_Result_f,

	/* Main methods */
	main_f,
	end_state_f,
	read_state1_count_f,
	reset_state1_count_f,
	read_state2_count_f,
	reset_state2_count_f,
	read_state3_count_f,
	reset_state3_count_f,
	Error_Handler_f,
	change_state_f,
	read_state_f,

	/* MMA8451Q methods */
	ACC_init_f,
	accel_read_f,
	self_test_f,
	accel_return_f,
	Delay_f,

	/* Slider methods */
	TOUCH_init_f,
	TOUCH_Calibrate_f,

	/* SPI methods */
	SPI_init_f,

	/* SysTick methods */
	SysTick_enable_interrupt_f,
	SysTick_disable_interrupt_f,
	SysTick_Handler_f,

	MAX_FUNCTION_COUNT

} functions_e;


static char *functions[MAX_FUNCTION_COUNT] = {
		/* Accelerometer methods */
		"[Read_XYZ_Acc_Handler()]",
		"[Process_Acc_Handler()]",
		"[Poll_Slider_Handler()]",
		"[Acc_Disconnect_Handler()]",
		"[POST_Test_Handler()]",
		"[display_accel()]",
		"[read_event()]",

		/* I2C methods */
		"[I2C_init()]",
		"[i2c_start()]",
		"[i2c_read_setup()]",
		"[i2c_repeated_read()]",
		"[i2c_read_byte()]",
		"[i2c_write_byte()]",
		"[i2c_busy()]",
		"[i2c_wait()]",
		"[read_i2c_lock()]",
		"[Enable_irq()]",
		"[Disable_irq()]",

		/* LED methods */
		"[LED_init()]",
		"[LED_SetPinsOutput()]",
		"[LED_ClearPinsOutput()]",
		"[LED_PinInit()]",
		"[LED_SetAll()]",
		"[LED_ClearRed()]",
		"[LED_ClearGreen()]",
		"[LED_ClearBlue()]",

		/* Logger methods */
		"[log_level()]",
		"[log_status()]",

		/* Loopback methods */
		"[Loopback()]",
		"[Display_Loopback_Result()]",

		/* Main methods */
		"[main()]",
		"[end_state()]",
		"[read_state1_count()]",
		"[reset_state1_count()]",
		"[read_state2_count()]",
		"[reset_state2_count()]",
		"[read_state3_count()]",
		"[reset_state3_count()]",
		"[Error_Handler()]",
		"[change_state()]",
		"[read_state()]",

		/* MMA8451Q methods */
		"[ACC_init()]",
		"[accel_read()]",
		"[self_test()]",
		"[accel_return()]",
		"[Delay()]",

		/* Slider methods */
		"[TOUCH_init()]",
		"[TOUCH_Calibrate()]",

		/* SPI methods */
		"[SPI_init()]",

		/* SysTick methods */
		"[SysTick_enable_interrupt()]",
		"[SysTick_disable_interrupt()]",
		"[SysTick_Handler()]"
};

#endif /* METHODS_H_ */
