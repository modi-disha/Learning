
/********************************************************************************
 * File name: "uCUnit_testsuit.c"
 *
 * Description: uCUnit test cases
 *
 * File​ ​ Author​ ​ Name: Disha Modi and Alexandra Paquin
 *
 * Tools​ ​ used​ ​ to​ ​ process​ ​ the​ ​ code​ ​ (compiler,​ ​ linker,​ ​ debugger):
 * 		NXP MCU Tools, Gnu Make Builder, Putty (serial port, 115200 baudrate)
 *
 * Identification​ ​ of​ ​ any​ ​ leveraged​ ​ code: None
 *
 * Applicable​ ​ Links: None
 *******************************************************************************/

#include "uCUnit_testsuit.h"

buffer_p xbuffer_p;

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
    Test_CreateBuffer();
    Test_DataAccess();
    Test_BufferSize();
    Test_WrapRemove();
    Test_WrapAdd();
    Test_Overfill();
    Test_Overempty();
    Test_WrapAddData();
    Test_ExtendedBuffer();
    Test_DestroyBuffer();

    UCUNIT_WriteSummary();
}

/**
 * Unit test Function to test Create Buffer functionality.
 * Expected result: Success
 */
void Test_CreateBuffer()
{
    UCUNIT_TestcaseBegin("\n\rTEST:Test_CreateBuffer\n\r");
	errors_e buff_status;
	// Enable interrupts. Listing 8.11 on p. 234
	if(!(xbuffer_p = (buffer_t *)malloc(sizeof(buffer_t))))		//Circular buffer structure
		exit(0);
	buff_status = circular_buff_init(xbuffer_p, 20);
	UCUNIT_CheckIsEqual(buff_status, Success); /* Pass*/
	UCUNIT_CheckIsEqual(xbuffer_p->length, 20); /* Pass*/

    UCUNIT_TestcaseEnd(); /* Pass */
    LED_Blink();
}

/**
 * Unit test Function to check functionality of circular buffer enqueue and dequeue same length
 * Expected result: Success
 */
void Test_DataAccess()
{
    UCUNIT_TestcaseBegin("\n\rTEST:Test_DataAccess\n\r");
    uint8_t data = 0;
    errors_e status;
    for(data = 0; data < 10; data++)
    {
    	status = circular_buff_enqueue(xbuffer_p, data);
    	UCUNIT_CheckIsEqual(status, Success); /* Pass*/
    }

    data = 0;
    uint8_t get_data;
    for(data = 0; data < 10; data++)
    {
    	status = circular_buff_dequeue(xbuffer_p, &get_data);
    	UCUNIT_CheckIsEqual(status, Success); /* Pass*/
    	UCUNIT_CheckIsEqual(get_data, data); /* Pass*/
    }

    UCUNIT_CheckIsEqual(circular_buff_size(xbuffer_p), 0);		//check
    UCUNIT_TestcaseEnd(); /* Pass */
    LED_Blink();
}

/**
 * Unit test Function to check functionality of buffer counts by
 * enqueue 10 characters and then dequeue 5 characters
 */
void Test_BufferSize()
{
    UCUNIT_TestcaseBegin("\n\rTEST:Test_BufferSize\n\r");
    uint8_t data = 0;
    errors_e status;
    for(data = 0; data < 10; data++)
    {
    	status = circular_buff_enqueue(xbuffer_p, data);
    	UCUNIT_CheckIsEqual(status, Success); /* Pass*/
    }

    UCUNIT_CheckIsEqual(circular_buff_size(xbuffer_p), 10);

    data = 0;
	uint8_t get_data;
	for(data = 0; data < 10; data++)
	{
		if(data == 5)
		{
			UCUNIT_CheckIsEqual(circular_buff_size(xbuffer_p), 5);
		}
		status = circular_buff_dequeue(xbuffer_p, &get_data);
		UCUNIT_CheckIsEqual(status, Success); /* Pass*/
		UCUNIT_CheckIsEqual(get_data, data); /* Pass*/
	}

    UCUNIT_TestcaseEnd(); /* Pass */
    LED_Blink();
}

/**
 * Unit test Function to check functionality of that Tail wraps around the edge boundary when a remove occurs at the boundary
 * Expected result: Success
 */
void Test_WrapRemove()
{
	UCUNIT_TestcaseBegin("\n\rTEST:Test_WrapRemove\n\r");

	uint8_t data = 0;
	errors_e status;
	for(data = 0; data < 20; data++)
	{
		status = circular_buff_enqueue(xbuffer_p, data);
		UCUNIT_CheckIsEqual(status, Success); /* Pass*/
	}

	data = 0;
	uint8_t get_data;
	for(data = 0; data < 20; data++)
	{
		status = circular_buff_dequeue(xbuffer_p, &get_data);
		UCUNIT_CheckIsEqual(status, Success); /* Pass*/
		UCUNIT_CheckIsEqual(get_data, data); /* Pass*/
	}

	UCUNIT_CheckIsEqual(circular_buff_size(xbuffer_p), 0);
	UCUNIT_CheckIsEqual(xbuffer_p->tail, 0);		//Tail wraps around the edge boundary when a remove occurs at the boundary

	UCUNIT_TestcaseEnd(); /* Pass */
    LED_Blink();
}

/**
 * Unit test Function to check functionality of Verify wrap add
 * test that the buffer can wrap around the edge boundary and add to the front
 * Expected result: Success
 */
void Test_WrapAdd()
{
	UCUNIT_TestcaseBegin("\n\rTEST:Test_WrapAdd\n\r");

	uint8_t data = 0;
	errors_e status;
	for(data = 0; data < 20; data++)
	{
		status = circular_buff_enqueue(xbuffer_p, data);
		UCUNIT_CheckIsEqual(status, Success); /* Pass*/
	}

	UCUNIT_CheckIsEqual(xbuffer_p->head, 0);		//head wraps around the edge boundary when a remove occurs at the boundary
	UCUNIT_CheckIsEqual(xbuffer_p->full, true);
	UCUNIT_CheckIsEqual(circular_buff_size(xbuffer_p), 20);

	data = 6;
	status = circular_buff_enqueue(xbuffer_p, data);
	UCUNIT_CheckIsEqual(status, Success); /* Pass*/

	UCUNIT_CheckIsEqual(xbuffer_p->head, 1);
	UCUNIT_CheckIsEqual(xbuffer_p->full, true);

	uint8_t get_data;
	status = circular_buff_dequeue(xbuffer_p, &get_data);
	UCUNIT_CheckIsEqual(status, Success); /* Pass*/
	UCUNIT_CheckIsEqual(get_data, 1); /* Pass*/

	UCUNIT_CheckIsEqual(xbuffer_p->tail, 2);
	UCUNIT_CheckIsEqual(xbuffer_p->full, false);

	UCUNIT_CheckIsEqual(circular_buff_size(xbuffer_p), 19);

	circular_buff_reset(xbuffer_p);
	UCUNIT_TestcaseEnd(); /* Pass */
    LED_Blink();
}

/**
 * Unit test Function to check functionality of buffer full and new character overwrite the old data
 * Expected result: Success
 */
void Test_WrapAddData()
{
	UCUNIT_TestcaseBegin("\n\rTEST:Test_WrapAddData\n\r");

	uint8_t data = 0;
	errors_e status;
	for(data = 0; data < 20; data++)
	{
		status = circular_buff_enqueue(xbuffer_p, data);
		UCUNIT_CheckIsEqual(status, Success); /* Pass*/
	}

	UCUNIT_CheckIsEqual(xbuffer_p->head, 0);		//Tail wraps around the edge boundary when a remove occurs at the boundary
	UCUNIT_CheckIsEqual(xbuffer_p->full, true);

	data = 6;
	status = circular_buff_enqueue(xbuffer_p, data);
	UCUNIT_CheckIsEqual(status, Success); /* Pass*/

	UCUNIT_CheckIsEqual(xbuffer_p->head, 1);		//Tail wraps around the edge boundary when a remove occurs at the boundary
	UCUNIT_CheckIsEqual(xbuffer_p->full, true);

	UCUNIT_CheckIsEqual(xbuffer_p->tail, 1);		//Tail wraps around the edge boundary when a remove occurs at the boundary
	UCUNIT_CheckIsEqual(xbuffer_p->full, true);

	circular_buff_reset(xbuffer_p);
	UCUNIT_TestcaseEnd(); /* Pass */
    LED_Blink();
}

/**
 * Unit test Function to check functionality of Over-fill
 * (test that your buffer fails when too many items are added)
 * Expected result: Success
 */
void Test_Overfill()
{
	UCUNIT_TestcaseBegin("\n\rTEST:Test_Overfill\n\r");

	uint8_t data = 0;
	errors_e status;
	for(data = 0; data < 20; data++)
	{
		status = circular_buff_enqueue(xbuffer_p, data);
		UCUNIT_CheckIsEqual(status, Success); /* Pass*/
	}

	UCUNIT_CheckIsEqual(xbuffer_p->head, 0);		//Tail wraps around the edge boundary when a remove occurs at the boundary
	UCUNIT_CheckIsEqual(xbuffer_p->full, true);

	circular_buff_reset(xbuffer_p);
	UCUNIT_TestcaseEnd(); /* Pass */
    LED_Blink();
}

/**
 * Unit test Function to check functionality of Over empty
 * (test that your buffer fails to remove an item when empty)
 * Expected result: Success
 */
void Test_Overempty()
{
	UCUNIT_TestcaseBegin("\n\rTEST:Test_AccNegativeX\n\r");
	errors_e status;

	uint8_t get_data = 0;
	status = circular_buff_dequeue(xbuffer_p, &get_data);
	UCUNIT_CheckIsEqual(status, Buff_empty); /* Pass*/
	UCUNIT_CheckIsEqual(get_data, 0); /* Pass*/

	UCUNIT_TestcaseEnd(); /* Pass */
    LED_Blink();
}

/**
 * Unit test Function to check functionality of adding (or reallocate)
 * memory to resize a circular buffer in case of buffer overflow
 * Expected result: Success
 */
void Test_ExtendedBuffer()
{
	UCUNIT_TestcaseBegin("\n\rTEST:Test_ExtendedBuffer\n\r");

	UCUNIT_TestcaseEnd(); /* Pass */
    LED_Blink();
}

/**
 * Unit test Function to check functionality of  Destroy the buffer
 * Expected result: Success
 */
void Test_DestroyBuffer()
{
	UCUNIT_TestcaseBegin("\n\rTEST:Test_DestroyBuffer\n\r");
	errors_e status;

	status = circular_buff_free(xbuffer_p);
	UCUNIT_CheckIsEqual(status, Success); /* Pass*/

	UCUNIT_TestcaseEnd(); /* Pass */
    LED_Blink();
}

//LED Blinks Red in case of errors, LED Blinks Green in case of Success
void LED_Blink(void)
{
	if( 0==(ucunit_testcases_failed_checks - ucunit_checks_failed))
	{
		LED_ClearGreen();
	}
	else
	{
		LED_ClearRed();
	}
	Delay(500);
	LED_SetAll();
}

// Delay Routine
void Delay(uint32_t dly)
{
	 volatile uint32_t t;

		for (t=dly*10000; t>0; t--)
			;
}
