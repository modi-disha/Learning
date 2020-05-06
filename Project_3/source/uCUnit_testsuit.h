/*
 * uCUnit_testsuit.h
 *
 *  Created on: Feb 23, 2020
 *      Author: Disha
 */

#ifndef UCUNIT_TESTSUIT_H_
#define UCUNIT_TESTSUIT_H_

#include "../uCUnit/uCUnit.h"
#include "fsl_debug_console.h"
#include "main.h"

/*
 * @brief: Function called into main function and acts as wrapper for all the test case functions.
 *
 * @param void
 *
 * @return void
 */
extern void Run_Testcases(void);
/*
 * @brief: Unit test Function to test heap memory allocation functionality.
 *
 * @param void
 *
 * @return void
 */
void Test_AllocateBytes(void);
/*
 * @brief: Unit test Function to check functionality of verify heap memory allocation.
 *
 * @param void
 *
 * @return void
 */
void Test_VerifyMemory(void);
/*
 * @brief: Unit test Function to check functionality of display dynamically allocated memory bytes.
 *
 * @param void
 *
 * @return void
 */
void Test_DisplayMemory_01(void);
/*
 * @brief: Unit test Function to check functionality of display dynamically allocated memory bytes.
 *
 * @param void
 *
 * @return void
 */
void Test_DisplayMemory_02(void);
/*
 * @brief: Unit test Function to check functionality of write data bytes into dynamically allocated memory.
 *
 * @param void
 *
 * @return void
 */
void Test_WriteMemory_01(void);
/*
 * @brief: Unit test Function to check functionality of write data bytes into dynamically allocated memory.
 *
 * @param void
 *
 * @return void
 */
void Test_WriteMemory_02(void);
/*
 * @brief: Unit test Function to check functionality of display dynamically allocated memory bytes.
 *
 * @param void
 *
 * @return void
 */
void Test_DisplayMemory_03(void);
/*
 * @brief: Unit test Function to check functionality of invert the data present on dynamically allocated memory.
 *
 * @param void
 *
 * @return void
 */
void Test_InvertBlock(void);
/*
 * @brief: Unit test Function to check functionality of write random pattern bytes into dynamically allocated memory.
 *
 * @param void
 *
 * @return void
 */
void Test_WritePattern(void);
/*
 * @brief: Unit test Function to check functionality of compare pattern written into dynamically allocated memory.
 *
 * @param void
 *
 * @return void
 */
void Test_ComparePattern(void);
/*
 * @brief: Unit test Function to check functionality of making dynamically allocated memory free.
 *
 * @param void
 *
 * @return void
 */
void Test_FreeAllocated(void);
/*
 * @brief: Function acts as wrapper for all the test case functions.
 *
 * @param void
 *
 * @return void
 */
void Testsuite_RunTests(void);

#endif /* UCUNIT_TESTSUIT_H_ */
