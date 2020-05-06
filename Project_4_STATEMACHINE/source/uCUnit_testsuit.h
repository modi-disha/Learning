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
 * @file uCUnit_testsuit..h
 * @brief An abstraction for unit test cases for the memory test methods.
 *
 * This header file provides an abstraction for unit test cases for the
 * Accelerometer and touch Slider test methods.
 *
 * @author Disha Modi and Alexandra Paquin
 * @date March 2020
 * @version 1.0
 *
 */

#ifndef UCUNIT_TESTSUIT_H_
#define UCUNIT_TESTSUIT_H_

#include "uCUnit.h"
#include "fsl_debug_console.h"
#include "main.h"

/*
 * @brief: Unit test Function to test Accelerometers power on self test functionality.
 *
 * @param void
 *
 * @return void
 */
void Test_AccSelftest(void);

/*
 * @brief: Unit test Function to check functionality of Touch Slider, in case there is no touch readings
 *
 * @param void
 *
 * @return void
 */
void Test_SliderTimeout(void);

/*
 * @brief: Unit test Function to check functionality of Touch Slider, in case there is touch on left side of the slider
 *
 * @param void
 *
 * @return void
 */
void Test_SliderLefttouch(void);

/*
 * @brief: Unit test Function to check functionality of Touch Slider, in case there is touch on right side of the slider
 *
 * @param void
 *
 * @return void
 */
void Test_SliderRighttouch(void);

/*
 * @brief: Unit test Function to check functionality of Accelerometer X readings positive value
 *
 * @param void
 *
 * @return void
 */
void Test_AccPositiveX(void);

/*
 * @brief: Unit test Function to check functionality of Accelerometer Y readings positive value
 *
 * @param void
 *
 * @return void
 */
void Test_AccPositiveY(void);

/*
 * @brief: Unit test Function to check functionality of Accelerometer Z readings positive value
 *
 * @param void
 *
 * @return void
 */
void Test_AccPositiveZ(void);

/*
 * @brief: Unit test Function to check functionality of Accelerometer X readings negative value
 *
 * @param void
 *
 * @return void
 */
void Test_AccNegativeX(void);

/*
 * @brief: Unit test Function to check functionality of Accelerometer Y readings negative value
 *
 * @param void
 *
 * @return void
 */
void Test_AccNegativeY(void);

/*
 * @brief: Unit test Function to check functionality of Accelerometer Z readings negative value
 *
 * @param void
 *
 * @return void
 */
void Test_AccNegativeZ(void);

/*
 * @brief: LED Blinks Red in case of errors, LED Blinks Green in case of Success
 *
 * @param void
 *
 * @return void
 */
void LED_Blink(void);

/*
 * @brief: Function called into main function and acts as wrapper for all the test case functions.
 *
 * @param void
 *
 * @return void
 */
extern void Run_Testcases(void);
/*
 * @brief: Function acts as wrapper for all the test case functions.
 *
 * @param void
 *
 * @return void
 */
void Testsuite_RunTests(void);

#endif /* UCUNIT_TESTSUIT_H_ */
