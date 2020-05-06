
/********************************************************************************
 * File name: "uCUnit_testsuit.c"
 *
 * Description: uCUnit test cases
 *
 * File​ ​ Author​ ​ Name: Disha Modi and Alexandra Paquin
 *
 * Tools​ ​ used​ ​ to​ ​ process​ ​ the​ ​ code​ ​ (compiler,​ ​ linker,​ ​ debugger):
 * 		NXP MCU Tools, Gnu Make Builder, Putty
 *
 * Identification​ ​ of​ ​ any​ ​ leveraged​ ​ code: None
 *
 * Applicable​ ​ Links: None
 *******************************************************************************/

#include "uCUnit_testsuit.h"

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
    Test_SliderTimeout();
    Test_SliderLefttouch();
    Test_SliderRighttouch();
    Test_AccSelftest();
    Test_AccPositiveX();
    Test_AccPositiveY();
    Test_AccPositiveZ();
    Test_AccNegativeX();
    Test_AccNegativeY();
    Test_AccNegativeZ();
    UCUNIT_WriteSummary();
}

/**
 * Unit test Function to test Accelerometers power on self test functionality.
 * Expected result: Success
 */
void Test_AccSelftest()
{
    UCUNIT_TestcaseBegin("\n\rTEST:Test_AccSelftest\n\r");

    uint8_t ret_val = 0;
    int16_t x, y, z;

    ret_val = self_test();	//self test module
    accel_return(&x, &y, &z);
	UCUNIT_CheckIsEqual(ret_val, 0); /* Pass*/

	UCUNIT_CheckIsInRange(x , 0, 5000);	// check the X readings
	UCUNIT_CheckIsInRange(y , 0, 5000); // check the Y readings
	UCUNIT_CheckIsInRange(z , 0, 5000); // check the Z readings

    UCUNIT_TestcaseEnd(); /* Pass */
    LED_Blink();
}

/**
 * Unit test Function to check functionality of Touch Slider, in case there is no touch readings
 * Expected result: Success
 */
void Test_SliderTimeout()
{
    UCUNIT_TestcaseBegin("\n\rTEST:Test_SliderTimeout\n\r");

	uint16_t calibration;
	calibration = TOUCH_Calibrate(BOARD_TOUCH_PORT);		///Read touch calibration

	UCUNIT_CheckIsInRange(calibration, 0, 650);

    UCUNIT_TestcaseEnd(); /* Pass */
    LED_Blink();
}

/**
 * Unit test Function to check functionality of Touch Slider, in case there is touch on left side of the slider
 */
void Test_SliderLefttouch()
{
    UCUNIT_TestcaseBegin("\n\rTEST:Test_SliderLefttouch\n\r");
    UCUNIT_WriteString("COMMAND: TOUCH THE LEFT SIDE OF THE SLIDER!\n\r");
    Delay(2000);

    uint16_t calibration;
    calibration = TOUCH_Calibrate(BOARD_TOUCH_PORT);		///Read touch calibration

    UCUNIT_CheckIsInRange(calibration, 650, 900);

    UCUNIT_TestcaseEnd(); /* Pass */
    LED_Blink();
}

/**
 * Unit test Function to check functionality of Touch Slider, in case there is touch on right side of the slider
 * Expected result: Success
 */
void Test_SliderRighttouch()
{
	UCUNIT_TestcaseBegin("\n\rTEST:Test_SliderRighttouch\n\r");
	UCUNIT_WriteString("COMMAND: TOUCH THE RIGHT SIDE OF THE SLIDER!\n\r");
	Delay(2000);

	uint16_t calibration;
	calibration = TOUCH_Calibrate(BOARD_TOUCH_PORT);		///Read touch calibration

	UCUNIT_CheckIsInRange(calibration, 900, 2000);

	UCUNIT_TestcaseEnd(); /* Pass */
    LED_Blink();
}

/**
 * Unit test Function to check functionality of Accelerometer X readings positive value
 * by moving it positive X direction
 * Expected result: Success
 */
void Test_AccPositiveX()
{
	UCUNIT_TestcaseBegin("\n\rTEST:Test_AccPositiveX\n\r");
	UCUNIT_WriteString("COMMAND: MOVE ACCELEROMETER IN +VE X DIRECTION!\n\r");
	Delay(2000);

	uint8_t result;
	result = accel_read();			///Read accelerometer XYZ

	int16_t x, y, z;
    accel_return(&x, &y, &z);

    UCUNIT_CheckIsEqual(result, 0); /* Pass*/
	UCUNIT_CheckIsInRange(x, 0, 5000);		///Positive X

	UCUNIT_TestcaseEnd(); /* Pass */
    LED_Blink();
}

/**
 * Unit test Function to check functionality of Accelerometer Y readings positive value
 * by moving it positive Y direction
 * Expected result: Success
 */
void Test_AccPositiveY()
{
	UCUNIT_TestcaseBegin("\n\rTEST:Test_AccPositiveY\n\r");
	UCUNIT_WriteString("COMMAND: MOVE ACCELEROMETER IN +VE Y DIRECTION!\n\r");
	Delay(2000);

	uint8_t result;
	result = accel_read();		///Read accelerometer XYZ

	int16_t x, y, z;
    accel_return(&x, &y, &z);

    UCUNIT_CheckIsEqual(result, 0); /* Pass*/
	UCUNIT_CheckIsInRange(y, 0, 5000);		///Positive Y

	UCUNIT_TestcaseEnd(); /* Pass */
    LED_Blink();
}

/**
 * Unit test Function to check functionality of Accelerometer Z readings positive value
 * by moving it positive Z direction
 * Expected result: Success
 */
void Test_AccPositiveZ()
{
	UCUNIT_TestcaseBegin("\n\rTEST:Test_AccPositiveZ\n\r");
	UCUNIT_WriteString("COMMAND: MOVE ACCELEROMETER IN +VE Z DIRECTION!\n\r");
	Delay(2000);

	uint8_t result;
	result = accel_read();		///Read accelerometer XYZ

	int16_t x, y, z;
    accel_return(&x, &y, &z);

    UCUNIT_CheckIsEqual(result, 0); /* Pass*/
	UCUNIT_CheckIsInRange(z, 0, 5000);		///Positive Z

	UCUNIT_TestcaseEnd(); /* Pass */
    LED_Blink();
}

/**
 * Unit test Function to check functionality of Accelerometer X readings negative value
 * by moving it negative X direction
 * Expected result: Success
 */
void Test_AccNegativeX()
{
	UCUNIT_TestcaseBegin("\n\rTEST:Test_AccNegativeX\n\r");
	UCUNIT_WriteString("COMMAND: MOVE ACCELEROMETER IN -VE X DIRECTION!\n\r");
	Delay(2000);

	uint8_t result;
	result = accel_read();		///Read accelerometer XYZ

	int16_t x, y, z;
    accel_return(&x, &y, &z);

    UCUNIT_CheckIsEqual(result, 0); /* Pass*/
	UCUNIT_CheckIsInRange(-x, 1, 5000);		///Negative X

	UCUNIT_TestcaseEnd(); /* Pass */
    LED_Blink();
}

/**
 * Unit test Function to check functionality of Accelerometer Y readings negative value
 * by moving it negative Y direction
 * Expected result: Success
 */
void Test_AccNegativeY()
{
	UCUNIT_TestcaseBegin("\n\rTEST:Test_AccNegativeY\n\r");
	UCUNIT_WriteString("COMMAND: MOVE ACCELEROMETER IN -VE Y DIRECTION!\n\r");
	Delay(2000);

	uint8_t result;
	result = accel_read();		///Read accelerometer XYZ

	int16_t x, y, z;
    accel_return(&x, &y, &z);

    UCUNIT_CheckIsEqual(result, 0); /* Pass*/
	UCUNIT_CheckIsInRange(-y, 1, 5000);		///Negative Y

	UCUNIT_TestcaseEnd(); /* Pass */
    LED_Blink();
}

/**
 * Unit test Function to check functionality of Accelerometer Z readings negative value
 * by moving it negative Z direction
 * Expected result: Success
 */
void Test_AccNegativeZ()
{
	UCUNIT_TestcaseBegin("\n\rTEST:Test_AccNegativeZ\n\r");
	UCUNIT_WriteString("COMMAND: MOVE ACCELEROMETER IN -VE Z DIRECTION!\n\r");
	Delay(2000);

	uint8_t result;
	result = accel_read();		///Read accelerometer XYZ

	int16_t x, y, z;
    accel_return(&x, &y, &z);

    UCUNIT_CheckIsEqual(result, 0);  		/* Pass*/
	UCUNIT_CheckIsInRange(-z, 1, 5000);		///Negative Z

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

