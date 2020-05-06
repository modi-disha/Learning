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
 * @file logger.h
 * @brief An abstraction for handling logging.
 *
 * This header file provides an abstraction for handling the enabling/disabling of logging, status of logging,
 * and logging of hex data, strings, and integers.
 *
 * @author Disha Modi and Alexandra Paquin
 * @date March 2020
 * @version 1.0
 *
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include "SysTick.h"
#include "UART.h"

#include "main.h"
#include <methods.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>


#define TIME_STR_SIZE	11

//Enumration for log on/off
typedef enum {
	log_off = 0,
	log_on
} log_e;

//Enumration for log test, Debug and Status mode
typedef enum {
	Test = 0,
	Debug = 1,
	Status = 2,

	MAX_LOG_LEVEL_COUNT

} log_level_e;




/**
 * @brief Sets the log levels
 *
 * Sets the log levels
 *
 * @param Void
 *
 * @return log_level
 */
void log_level(log_level_e log_level);

/**
 * @brief Enables the logger
 *
 * Begins printing log messages when called
 *
 * @param Void
 *
 * @return Void
 */
void log_enable(void);

/**
 * @brief Disables the logger
 *
 * Ignores any log messages until re-enabled
 *
 * @param Void
 *
 * @return Void
 */
void log_disable(void);

/**
 * @brief Check status of logger
 *
 * Returns a flag to indicate whether the logger is enabled or disabled
 *
 * @param Void
 *
 * @return Void
 */
void log_status(void);


/**
 * @brief Display a string
 *
 * Display a string
 *
 * @param *s pointer to a string
 *
 * @return Void
 */
void log_string(log_level_e log_level, functions_e func, char *s);

/**
 * @brief Display an integer
 *
 * Display an integer
 *
 * @param x integer to display
 *
 * @return Void
 */
void log_integer(log_level_e log_level, functions_e func, int x);


/**
 * @brief Method for formating the time counter into a string.
 *
 * Method for formating the time counter into a string (HH:MM:SS.n) where
 * HH is the hours, MM is the minutes, SS is the seconds, and n is the deciseconds.
 *
 * @param none
 *
 * @return void
 */
void format_time(void);

#endif /* LOGGER_H_ */
