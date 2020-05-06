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
 * @file main.h
 * @brief An abstraction for executing the Project 4 main code.
 *
 * This header file provides an abstraction for executing the Project 4 main code
 * for parsing a list of commands and executing their associated Unit testcases.
 *
 * @author Disha Modi and Alexandra Paquin
 * @date March 2020
 * @version 1.0
 *
 */

#ifndef MAIN_H_
#define MAIN_H_

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "slider.h"
#include "led_control.h"
#include "logger.h"
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "clock_config.h"
#include "pin_mux.h"
#include "MKL25Z4.h"
#include "peripherals.h"

#include <MMA8451Q.h>
#include <stdio.h>
#include <string.h>

#define MAX_STATES 5
#define MAX_EVENTS 7

/*******************************************************************************
 * Enums and Structures
 ******************************************************************************/
typedef enum		///enum for all the states
{
	Read_XYZ_Acc,
	Process_Acc,
	Poll_Slider,
	Disconnect,
	SPI_Loopback,
	Process_Loopback,
	SPI_Disconnect,
	Error
} state_e;

typedef enum		///enum for all the events
{
	Pass,
	Fail,
	Complete,
	Disconnected,
	Timeout,
	Left_slider,
	Right_slider
} event_e;

typedef enum		///enum for flag states
{
	FLAG_LOW = 0,
	FLAG_HIGH = 1
}flag_e;

extern event_e event;

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/**
 * @brief POST (Power-On Startup Test)
 *
 * Tests that all three accels in accelerometer is working properly.
 *
 * @param Void
 *
 * @return state_e returns next state
 */
state_e POST_Test_Handler(void);

/**
 * @brief Reads the accelerometer readings
 *
 * @param void
 *
 * @return state_e returns next state
 */
state_e Read_XYZ_Acc_Handler(void);

/**
 * @brief Processes (Displays) accelerometer readings and other calculated values
 *
 * @param void
 *
 * @return state_e returns next state
 */
state_e Process_Acc_Handler(void);

/**
 * @brief Reads the slider calibration values
 *
 * @param void
 *
 * @return state_e returns next state
 */
state_e Poll_Slider_Handler(void);

/**
 * @brief Ends the program in case of sensor disconnect state
 *
 * @param void
 *
 * @return state_e returns next state
 */
state_e Acc_Disconnect_Handler(void);

/**
 * @brief SPI loopback function
 *
 * @param void
 *
 * @return state_e returns next state
 */
state_e Loopback(void);

/**
 * @brief Displays the SPI Loopback result
 *
 * @param void
 *
 * @return state_e returns next state
 */
state_e Display_Loopback_Result(void);

/**
 * @brief Ends the program in case of error
 *
 * @param void
 *
 * @return void
 */
void end_state(void);

/**
 * @brief Call the routine to End the program in case of error
 *
 * @param void
 *
 * @return state_e returns next state
 */
state_e Error_Handler(void);

/**
 * @brief Counts the entry of State machine 1
 *
 * @param void
 *
 * @return uint8_t returns the count
 */
uint8_t read_state1_count(void);

/**
 * @brief Reset the entry count of State machine 1
 *
 * @param void
 *
 * @return void
 */
void reset_state1_count(void);

/**
 * @brief Counts the entry of State machine 2
 *
 * @param void
 *
 * @return uint8_t returns the count
 */
uint8_t read_state2_count(void);

/**
 * @brief Reset the entry count of State machine 2
 *
 * @param void
 *
 * @return void
 */
void reset_state2_count(void);

/**
 * @brief Counts the entry of State machine 3
 *
 * @param void
 *
 * @return uint8_t returns the count
 */
uint8_t read_state3_count(void);

/**
 * @brief Reset the entry count of State machine 3
 *
 * @param void
 *
 * @return void
 */
void reset_state3_count(void);

/**
 * @brief Changes to the next state machine
 *
 * @param void
 *
 * @return void
 */
void change_state(void);

/**
 * @brief Reads the current state machine
 *
 * @param void
 *
 * @return uint8_t returns state machine number
 */
uint8_t read_state(void);

#endif /* MAIN_H_ */
