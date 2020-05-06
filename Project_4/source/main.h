/*
 * main.h
 * @ref: https://www.embedded.com/implementing-finite-state-machines-in-embedded-systems/
 *  Created on: Mar 15, 2020
 *      Author: Disha
 *  Laverage code: @see: https://www.embedded.com/implementing-finite-state-machines-in-embedded-systems/
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "LIS331.h"
#include "slider.h"
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "clock_config.h"
#include "pin_mux.h"
#include "MKL25Z4.h"
#include <stdio.h>
#include <string.h>

#define MAX_STATES 5
#define MAX_EVENTS 7

typedef enum
{
	Read_XYZ_Acc,
	Process_Acc,
	Poll_Slider,
	Acc_Disconnect,
	Error
} state_e;

typedef enum
{
	Pass,
	Fail,
	Complete,
	Disconnected,
	Timeout,
	Left_slider,
	Right_slider
} event_e;

event_e read_event(void);
state_e POST_Test_Handler(void);
state_e Read_XYZ_Acc_Handler(void);
state_e Process_Acc_Handler(void);
state_e Poll_Slider_Handler(void);
state_e Acc_Disconnect_Handler(void);
state_e POST_Test_Handler(void);
void end_state(void);
state_e Error_Handler(void);
uint8_t read_state1_count(void);
void reset_state1_count(void);
void change_state(void);

#endif /* MAIN_H_ */
