/*
 * Accelerometer.c
 *
 *  Created on: Mar 15, 2020
 *      Author: Disha
 */

#include "main.h"

event_e event;

//In the Read XYZ Accel state you will access the LIS331 for its last X, Y, Z acceleration readings via I2C.
state_e Read_XYZ_Acc_Handler(void)
{
	uint8_t result;
	result = accel_read();

	if(result == 1)
	{
		printf("Read XYZ Accelerometer failed.\n\r");
		event = Disconnected;
		return Acc_Disconnect;
	}
	else
	{
		printf("Read XYZ Accelerometer succeed.\n\r");
		event = Complete;
		return Process_Acc;
	}
}

//In the Process/Display state you will use the current acceleration readings to display:
//o Last X, Y, Z readings and the state entry count
//o Average X, Y, Z readings
//o Low X, Y, Z readings
//o High X, Y, Z readings
state_e Process_Acc_Handler(void)
{
	display_accel();
	event = Complete;
	return Poll_Slider;
}

//In the Wait/Poll Slider state, you will count the number of times you have entered this state and you will wait for a 3 second timeout. You MUST use the SysTick timer to create this specific 3 second delay. While waiting for the timer interrupt, you will poll the KL25Z Touch Slider. If you receive a left side touch event, you will go to the Left Slider transition. If you receive a right side touch event, you will go to the Right Slider transition. If the timer times out for state entries 1 through 5, you will go to the Timeout 1-5 transition, if the timer times out for state entry 6, clear the visit counter and go to the Timeout 6 transition. There are four transitions from this state: Left Slider, Right Slider, Timeout 1-5, and Timeout 6.
//o On Left Slider or Timeout 6, the state will change to Read XYZ Accel in the OTHER state machine
//o On Timeout 1-5, the state will change to Read XYZ Accel in this state machine
//o On Right Slider, the program will end
state_e Poll_Slider_Handler(void)
{
	uint16_t calibration;
	calibration = TOUCH_Calibrate(BOARD_TOUCH_PORT);		//ToDo: Implement 3 second timeout with sys_tick timer
	uint8_t count = read_state1_count();

	if((calibration == 0) && (count <= 6))
	{
		event = Timeout;
	}
	if((calibration == 0) && (count > 6))
	{
		reset_state1_count();
		change_state();
		event = Timeout;
	}
	if(calibration > 0 && calibration <= 750)
	{
		change_state();
		event = Left_slider;
	}
	if(calibration > 750)
	{
		event = Right_slider;
	}
	return Read_XYZ_Acc;
}

//The Disconnected state indicates the LIS331 is not responding for some reason. This state is reached via a Disconnect event, which should occur if the sensor is physically disconnected. There is one possible transition from this state, which is that the program will end.
state_e Acc_Disconnect_Handler(void)
{
	printf("Sensor Disconnected.\n\r");
	printf("Program ends.\n\r");
	end_state();
	return Error;
}

state_e POST_Test_Handler(void)
{
	uint8_t result = 0;

	result = self_test();
	if(result == 1)
	{
		printf("Power On Self Test failed.\n\r");
		event = Fail;
	}
	else
	{
		printf("Power On Self Test Succeed.\n\r");
		event = Pass;
	}
	return Read_XYZ_Acc;
}

//In the Process/Display state you will use the current acceleration readings to display:
//o Last X, Y, Z readings and the state entry count
//o Average X, Y, Z readings
//o Low X, Y, Z readings
//o High X, Y, Z readings
void display_accel(void)
{
	static double x[6], y[6], z[6];
	uint8_t count;
	count = read_state1_count();
	double x_accel, y_accel, z_accel;
	accel_return(&x_accel, &y_accel, &z_accel);
	x[count - 1] = x_accel;
	y[count - 1] = y_accel;
	z[count - 1] = z_accel;

	double ax, ay, az;
	double minx = x[0], miny = y[0], minz = z[0];
	double maxx = x[0], maxy = y[0], maxz = z[0];

	for(uint8_t i = 0; i < count; i++)
	{
		ax += x[i];
		ay += y[i];
		az += z[i];
	}
	ax = (ax / (double)count);
	ay = (ay / (double)count);
	az = (az / (double)count);

	for(uint8_t i = 1; i < count; i++)
	{
		if(x[i] < minx) { minx = x[i]; }
		if(y[i] < miny) { miny = y[i]; }
		if(z[i] < minz) { minz = z[i]; }
	}

	for(uint8_t i = 1; i < count; i++)
	{
		if(x[i] > maxx) { maxx = x[i]; }
		if(y[i] > maxy) { maxy = y[i]; }
		if(z[i] > maxz) { maxz = z[i]; }
	}

	printf("Accelerometer Readings:\n\r");
	printf("x = %6.2f,	", x_accel);
	printf("y = %6.2f,	", y_accel);
	printf("z = %6.2f\n\r", z_accel);
	printf("\n\r");
	printf("State Entry Count: %d\n\r", count);
	printf("\n\r");
	printf("Average Accelerometer Readings:\n\r");
	printf("x = %6.2f,	", ax);
	printf("y = %6.2f,	", ay);
	printf("z = %6.2f\n\r", az);
	printf("Low Accelerometer Readings:\n\r");
	printf("x = %6.2f,	", minx);
	printf("y = %6.2f,	", miny);
	printf("z = %6.2f\n\r", minz);
	printf("High Accelerometer Readings:\n\r");
	printf("x = %6.2f,	", maxx);
	printf("y = %6.2f,	", maxy);
	printf("z = %6.2f\n\r", maxz);

}

event_e read_event(void)
{
	return event;
}
