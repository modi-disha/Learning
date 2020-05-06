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
 * @file uCUnit_Testsuit.h
 * @brief An abstraction for unit void Test cases for the circular buffer Test methods.
 *
 * This header file provides an abstraction for unit Test cases for the circular buffer
 * Test methods.
 *
 * @author Disha Modi and Alexandra Paquin
 * @date April 2020
 * @version 1.0
 *
 */

#ifndef UCUNIT_TestSUIT_H_
#define UCUNIT_TestSUIT_H_

#include "uCUnit.h"
#include "fsl_debug_console.h"
#include "main.h"

/*
 * @brief: Unit test Function to test Create Buffer functionality.
 *
 * @param void
 *
 * @return void
 */
void Test_CreateBuffer(void);

/*
 * @brief: Unit test Function to check functionality of circular buffer enqueue and dequeue same length
 *
 * @param void
 *
 * @return void
 */
void Test_DataAccess(void);

/*
 * @brief: Unit test Function to check functionality of buffer counts by
 * enqueue 10 characters and then dequeue 5 characters
 *
 * @param void
 *
 * @return void
 */
void Test_BufferSize(void);

/*
 * @brief: Unit test Function to check functionality of that Tail wraps around
 * the edge boundary when a remove occurs at the boundary
 *
 * @param void
 *
 * @return void
 */
void Test_WrapRemove(void);

/*
 * @brief: Unit test Function to check functionality of Verify wrap add
 * test that the buffer can wrap around the edge boundary and add to the front
 *
 * @param void
 *
 * @return void
 */
void Test_WrapAdd(void);

/*
 * @brief: Unit test Function to check functionality of buffer full and new character overwrite the old data
 *
 * @param void
 *
 * @return void
 */
void Test_WrapAddData(void);

/*
 * @brief: Unit test Function to check functionality of Over-fill
 * (test that your buffer fails when too many items are added)
 *
 * @param void
 *
 * @return void
 */
void Test_Overfill(void);

/*
 * @brief: Unit test Function to check functionality of Over empty
 * (test that your buffer fails to remove an item when empty)
 *
 * @param void
 *
 * @return void
 */
void Test_Overempty(void);

/*
 * @brief: Unit test Function to check functionality of adding (or reallocate)
 * memory to resize a circular buffer in case of buffer overflow
 *
 * @param void
 *
 * @return void
 */
void Test_ExtendedBuffer(void);

/*
 * @brief: Unit test Function to check functionality of  Destroy the buffer
 *
 * @param void
 *
 * @return void
 */
void Test_DestroyBuffer(void);

/*
 * @brief: LED Blinks Red in case of errors, LED Blinks Green in case of Success
 *
 * @param void
 *
 * @return void
 */
void LED_Blink(void);

/*
 * @brief: Function called into main function and acts as wrapper for all the void Test case functions.
 *
 * @param void
 *
 * @return void
 */
extern void Run_Testcases(void);
/*
 * @brief: Function acts as wrapper for all the void Test case functions.
 *
 * @param void
 *
 * @return void
 */
void Testsuite_RunTests(void);

/*
 * @brief: Delay Routine
 *
 * @param void
 *
 * @return void
 */
void Delay(uint32_t dly);

#endif /* UCUNIT_TestSUIT_H_ */
