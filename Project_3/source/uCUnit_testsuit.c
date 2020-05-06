/*
 * uCUnit_testsuit.c
 *
 *  Created on: Feb 23, 2020
 *      Author: Disha
 */


#include "uCUnit_testsuit.h"

/* Global variables to store dynamically allocated memory's address and size */
uint32_t *address = (uint32_t *)0x1ffff220;
uint16_t size = 0;


/**
 * Function called into main function and acts as wrapper for all the test case functions.
 */
void Run_Testcases()
{
	UCUNIT_Init();
	UCUNIT_WriteString("\n\r**************************************");
	UCUNIT_WriteString("\n\rName:     ");
	UCUNIT_WriteString("uCUnit Unit Test Cases");
	UCUNIT_WriteString("\n\rCompiled: ");
	UCUNIT_WriteString(__DATE__);
	UCUNIT_WriteString("\n\rTime:     ");
	UCUNIT_WriteString(__TIME__);
	UCUNIT_WriteString("\n\rVersion:  ");
	UCUNIT_WriteString(UCUNIT_VERSION);
	UCUNIT_WriteString("\n\r**************************************");
	Testsuite_RunTests();
	UCUNIT_Shutdown();
}

/**
 * Function acts as wrapper for all the test case functions.
 * Expected result: Success
 */
void Testsuite_RunTests()
{
    Test_AllocateBytes();
    Test_VerifyMemory();
    Test_DisplayMemory_01();
    Test_DisplayMemory_02();
    Test_WriteMemory_01();
    Test_WriteMemory_02();
    Test_DisplayMemory_03();
    Test_InvertBlock();
    Test_WritePattern();
    Test_ComparePattern();
    Test_FreeAllocated();
    UCUNIT_WriteSummary();
}

/**
 * Unit test Function to test heap memory allocation functionality. Testing allocation of 32 bytes of dynamic memory.
 * Expected result: Success
 */
void Test_AllocateBytes()
{
	arg_t test_var;

	test_var.n_bytes = 32;
	test_var.mem_address = address;
	test_var.mem_size = size;
    UCUNIT_TestcaseBegin("\n\rTEST:Test_AllocateBytes\n\r");

    allocate_bytes(&test_var);
	UCUNIT_CheckIsEqual(test_var.mem_size, 32 ); /* Pass*/
	UCUNIT_CheckIsEqual(test_var.error, SUCCESS);
	address = test_var.mem_address;
	size = test_var.mem_size;
    UCUNIT_TestcaseEnd(); /* Pass */
}

/**
 * Unit test Function to check functionality of verify heap memory allocation. Verifying 32 bytes of memory allocated.
 * Expected result: Success
 */
void Test_VerifyMemory()
{
	arg_t test_var;
	test_var.mem_address = address;
	test_var.mem_size = size;
    UCUNIT_TestcaseBegin("\n\rTEST:Test_VerifyMemory\n\r");

	verify_memory(&test_var);

	UCUNIT_CheckIsEqual(test_var.mem_allocated, true);
	UCUNIT_CheckIsEqual(test_var.error, SUCCESS);
    UCUNIT_TestcaseEnd(); /* Pass */
}

/**
 * Unit test Function to check negative functionality. Testing to display memory bytes more than allocated into the memory.
 * Functionality should fail with out of range error.
 */
void Test_DisplayMemory_01()
{
	arg_t test_var;
	test_var.mem_address = address;
	test_var.mem_size = size;
	test_var.n_bytes = 34;

    UCUNIT_TestcaseBegin("\n\rTEST:Test_DisplayMemory\n\r");

	display_memory(&test_var);

	UCUNIT_CheckIsEqual(test_var.error, OUT_OF_RANGE);
	UCUNIT_WriteString("ERROR: OUT OF RANGE!\n\r");

    UCUNIT_TestcaseEnd(); /* Pass */
}

/**
 * Unit test Function to check functionality of Display allocated memory data. Displaying 32 bytes of memory allocated.
 * Expected result: Success
 */
void Test_DisplayMemory_02()
{
	arg_t test_var;
	test_var.mem_address = address;
	test_var.mem_size = size;
	test_var.n_bytes = 32;

    UCUNIT_TestcaseBegin("\n\rTEST:Test_DisplayMemory\n\r");

	display_memory(&test_var);

	UCUNIT_CheckIsEqual(test_var.error, SUCCESS);

    UCUNIT_TestcaseEnd(); /* Pass */
}

/**
 * Unit test Function to check functionality of Write data bytes to allocated memory. Writing 2 bytes.
 * Expected result: Success
 */
void Test_WriteMemory_01()
{
	arg_t test_var;
	test_var.mem_address = address;
	test_var.mem_size = size;
	test_var.n_bytes = 2;
	test_var.m_offset = 12;
	uint8_t *dummy_mem = NULL;
	uint8_t *write = (uint8_t *)malloc(test_var.n_bytes * (sizeof(uint8_t)));
	*write = 0xEE;
	*(write + 1) = 0xFF;
	test_var.values = write;

    UCUNIT_TestcaseBegin("\n\rTEST:Test_WriteMemory_01\n\r");

	write_memory(&test_var);

	dummy_mem = (uint8_t *)test_var.mem_address;
	UCUNIT_CheckIsEqual(test_var.error, SUCCESS);
	UCUNIT_CheckIsEqual(*(dummy_mem + (test_var.m_offset - 1)), *write);
	UCUNIT_CheckIsEqual(*(dummy_mem + (test_var.m_offset)), *(write + 1));

    UCUNIT_TestcaseEnd(); /* Pass */
}

/**
 * Unit test Function to check negative functionality of Write to allocated memory. Writing 2 bytes outside memory allocated.
 * Expected result: Out of range
 */
void Test_WriteMemory_02()
{
	arg_t test_var;
	test_var.mem_address = address;
	test_var.mem_size = size;
	test_var.n_bytes = 2;
	test_var.m_offset = 32;

	uint8_t *write = (uint8_t *)malloc(test_var.n_bytes * (sizeof(uint8_t)));
	*write = 0xEE;
	*(write + 1) = 0xFF;
	test_var.values = write;

    UCUNIT_TestcaseBegin("\n\rTEST:Test_WriteMemory_02\n\r");

	write_memory(&test_var);

	UCUNIT_CheckIsEqual(test_var.error, OUT_OF_RANGE);
	UCUNIT_WriteString("ERROR: OUT OF RANGE!\n\r");

    UCUNIT_TestcaseEnd(); /* Pass */
}

/**
 * Unit test Function to check functionality of Display allocated memory data. Testing display 16 bytes of memory allocated.
 * Expected result: Success
 */
void Test_DisplayMemory_03()
{
	arg_t test_var;
	test_var.mem_address = address;
	test_var.mem_size = size;
	test_var.n_bytes = 16;

    UCUNIT_TestcaseBegin("\n\rTEST:Test_DisplayMemory\n\r");

	display_memory(&test_var);

	UCUNIT_CheckIsEqual(test_var.error, SUCCESS);

    UCUNIT_TestcaseEnd(); /* Pass */
}

/**
 * Unit test Function to check functionality of invert the 2 bytes of data present on dynamically allocated memory.
 * Expected result: Success
 */
void Test_InvertBlock()
{
	arg_t test_var;
	test_var.mem_address = address;
	test_var.mem_size = size;
	test_var.n_bytes = 2;
	test_var.m_offset = 9;		//ToDo: change off-set value in variable

    UCUNIT_TestcaseBegin("\n\rTEST:Test_InvertBlock\n\r");
    uint8_t inv_byte = 0xFF;
	uint8_t *dummy_mem = NULL;
	dummy_mem = (uint8_t *)address;
	uint8_t *data = (dummy_mem + (test_var.m_offset - 1));
    uint8_t *invert_data = (uint8_t *)malloc(test_var.n_bytes * sizeof(uint8_t));

    for(uint8_t i = 0; i < test_var.n_bytes; i++)
    {
    	*(invert_data + i) = *(data + i);
    	*(invert_data + i) ^= inv_byte;
    }

	invert_block(&test_var);

	UCUNIT_CheckIsEqual(test_var.error, SUCCESS);
	UCUNIT_CheckIsEqual(*(dummy_mem + (test_var.m_offset - 1)), *invert_data);
	UCUNIT_CheckIsEqual(*(dummy_mem + test_var.m_offset), *(invert_data + 1));

    UCUNIT_TestcaseEnd(); /* Pass */
}

/**
 * Unit test Function to check functionality of write random pattern bytes into dynamically allocated memory.
 * Testing pattern of 16 bytes written with seed value passed as 143.
 * Expected result: Success
 */
void Test_WritePattern()
{
	arg_t test_var;
	test_var.mem_address = address;
	test_var.mem_size = size;
	test_var.n_bytes = 16;
	test_var.seed = 143;
    uint8_t *pattern = (uint8_t *)malloc(test_var.n_bytes * (sizeof(uint8_t)));
    uint8_t *dummy_mem;
    dummy_mem = (uint8_t *)address;

    gen_pattern(test_var.n_bytes, test_var.seed, pattern);

    UCUNIT_TestcaseBegin("\n\rTEST:Test_WritePattern\n\r");

	write_pattern(&test_var);

	UCUNIT_CheckIsEqual(test_var.error, SUCCESS);

	for(uint8_t i = 0; i < test_var.n_bytes; i++)
	{
		UCUNIT_CheckIsEqual(*(dummy_mem + i), *(pattern + i));
	}

    UCUNIT_TestcaseEnd(); /* Pass */
}

/**
 * Unit test Function to check negative functionality of compare random pattern bytes written into dynamically allocated memory.
 * Testing pattern of 18 bytes comparison with seed value passed as 143. (comparing more bytes then bytes actually got written)
 * Expected result: failed
 */
void Test_ComparePattern()
{
	arg_t test_var;
	test_var.mem_address = address;
	test_var.mem_size = size;
	test_var.n_bytes = 18;

	test_var.seed = 143;

    UCUNIT_TestcaseBegin("\n\rTEST:Test_ComparePattern\n\r");

	compare_pattern(&test_var);

	UCUNIT_CheckIsEqual(test_var.error, FAILED);

    UCUNIT_TestcaseEnd(); /* Pass */
}

/**
 * Unit test Function to check functionality of making dynamically allocated memory free.
 * Expected result: Success
 */
void Test_FreeAllocated()
{
	arg_t test_var;
	test_var.mem_address = address;
	test_var.mem_size = size;
	UCUNIT_TestcaseBegin("\n\rTEST:Test_FreeAllocated\n\r");

    free_allocated(&test_var);

	UCUNIT_CheckIsEqual(test_var.mem_size, 0 ); /* Pass*/

	UCUNIT_CheckIsEqual(test_var.mem_allocated, 0);

    UCUNIT_TestcaseEnd(); /* Pass */
}
