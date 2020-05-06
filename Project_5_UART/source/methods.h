
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
	/* Application methods */
	update_char_count_f,
	get_report_f,
	calc_report_memory_required_f,

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
	log_disable_f,
	log_enable_f,
	log_level_f,
	log_status_f,
	format_time_f,

	/* Main methods */
	main_f,

	/*Queue Methods */
	circular_buff_init_f,
	circular_buff_free_f,
	circular_buff_reset_f,
	circular_buff_enqueue_f,
	circular_buff_dequeue_f,
	circular_buff_empty_f,
	circular_buff_full_f,
	circular_buff_size_f,
	circular_buff_initialized_f,
	circular_buff_valid_f,
	pointer_check_f,

	/* SysTick methods */
	SysTick_enable_interrupt_f,
	SysTick_disable_interrupt_f,
	SysTick_Handler_f,

	/* UART methods */
	Init_UART0_Poll_f,
	UART0_Transmit_Poll_f,
	PutChar_Poll_f,
	PrintChar_Poll_f,
	UART0_Receive_Poll_f,
	GetChar_Poll_f,
	ScanChar_Poll_f,
	Char_Poll_f,
	PrintStr_Poll_f,
	Init_UART0_INT_f,
	UART0_Transmit_INT_f,
	PutChar_INT_f,
	UART0_Receive_INT_f,
	GetChar_INT_f,
	UART0_Error_INT_f,
	ClearErrFlags_f,
	Char_INT_f,
	PrintStr_INT_f,

	MAX_FUNCTION_COUNT

} functions_e;


static char *functions[MAX_FUNCTION_COUNT] = {
		/* Application methods */
		"[update_char_count()]",
		"[get_report()]",
		"[calc_report_memory_required()]",

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
		"[log_disable()]",
		"[log_enable()]",
		"[log_level()]",
		"[log_status()]",
		"[format_time()]",

		/* Main methods */
		"[main()]",

		/*Queue Methods */
		"[circular_buff_init()]",
		"[circular_buff_free()]",
		"[circular_buff_reset()]",
		"[circular_buff_enqueue()]",
		"[circular_buff_dequeue()]",
		"[circular_buff_empty()]",
		"[circular_buff_full()]",
		"[circular_buff_size()]",
		"[circular_buff_initialized()]",
		"[circular_buff_valid()]",
		"[pointer_check()]",

		/* SysTick methods */
		"[SysTick_enable_interrupt()]",
		"[SysTick_disable_interrupt()]",
		"[SysTick_Handler()]"

		/* UART methods */
		"[Init_UART0_Poll()]",
		"[UART0_Transmit_Poll()]",
		"[PutChar_Poll()]",
		"[PrintChar_Poll()]",
		"[UART0_Receive_Poll()]",
		"[GetChar_Poll()]",
		"[ScanChar_Poll()]",
		"[Char_Poll()]",
		"[PrintStr_Poll()]",
		"[Init_UART0_INT()]",
		"[UART0_Transmit_INT()]",
		"[PutChar_INT()]",
		"[UART0_Receive_INT()]",
		"[GetChar_INT()]",
		"[UART0_Error_INT()]",
		"[ClearErrFlags()]",
		"[Char_INT()]",
		"[PrintStr_INT()]",
};

#endif /* METHODS_H_ */
