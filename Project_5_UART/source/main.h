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
 * @brief An abstraction for executing the Project 5 main code.
 *
 * This header file provides an abstraction for executing the Project 5 main code
 * for parsing a list of commands and executing their associated Unit testcases.
 *
 * @author Disha Modi and Alexandra Paquin
 * @date April 2020
 * @version 1.0
 *
 */
//@ref: https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code/Chapter_8/Serial-Demo/
//@ref: https://embeddedartistry.com/blog/2017/05/17/creating-a-circular-buffer-in-c-and-c/

#ifndef MAIN_H_
#define MAIN_H_

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "UART.h"
#include "queue.h"
#include "led_control.h"
#include "SysTick.h"
#include "Logger.h"
#include "uCUnit_testsuit.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define START_CRITICAL() DisableGlobalIRQ()
#define END_CRITICAL(intMask) EnableGlobalIRQ(intMask)

#define USE_UART_INTERRUPTS 1
#define USE_ECHO_MODE 1
#define USE_TEST_MODE 0
#define APPLICATION 1


#endif /* MAIN_H_ */

