
/********************************************************************************
 * File name: "Accelerometer.c"
 *
 * Description: Include all accelerometer related functions like Init XYZ,
 * read XYZ, Process XYZ
 *
 * File​ ​ Author​ ​ Name: Disha Modi and Alexandra Paquin
 *
 * Tools​ ​ used​ ​ to​ ​ process​ ​ the​ ​ code​ ​ (compiler,​ ​ linker,​ ​ debugger):
 * 		NXP MCU Tools, Gnu Make Builder, Putty
 *
 * Identification​ ​ of​ ​ any​ ​ leveraged​ ​ code: As per main.c
 *
 * Applicable​ ​ Links: None
 *******************************************************************************/

#include "main.h"


//In the Read XYZ Accel state you will access the LIS331 for its last X, Y, Z acceleration readings via I2C.
state_e Read_XYZ_Acc_Handler(void)
{
	uint8_t result;
	result = accel_read();

	if(result == 1)
	{
		log_string(Status, Read_XYZ_Acc_Handler_f,"Read XYZ Accelerometer failed.");
		event = Disconnected;
		return Disconnect;
	}
	else
	{
		log_string(Status, Read_XYZ_Acc_Handler_f,"Read XYZ Accelerometer succeed.");
		event = Complete;
		return Process_Acc;
	}
}

//In the Process/Display state use the current acceleration readings to display:
// Last X, Y, Z readings and the state entry count
// Average X, Y, Z readings
// Low X, Y, Z readings
// High X, Y, Z readings
state_e Process_Acc_Handler(void)
{
	display_accel();
	event = Complete;
	return Poll_Slider;
}

//In the Wait/Poll Slider state, count the number of times you have entered this state and wait for a 3 second timeout with SysTick Timer.
// poll the KL25Z Touch Slider.
// If the timer times out for state entries 1 through 5, go to the Timeout 1-5 transition.
// On Left Slider or Timeout 6, the state change to Read XYZ Accel in the OTHER state machine
// On Timeout 1-5, the state change to Read XYZ Accel in this state machine
// On Right Slider, the program will end
state_e Poll_Slider_Handler(void)
{
	uint16_t calibration;
	calibration = TOUCH_Calibrate(BOARD_TOUCH_PORT);
	uint8_t state = read_state();
	uint8_t count = (state == 1) ? read_state1_count() : (state == 2) ? read_state2_count() : read_state3_count();

	if((calibration < SLIDER_RIGHT_MIN) && (count < MAX_TIMEOUTS))
	{
		event = Timeout;
	}
	if((calibration < SLIDER_RIGHT_MIN) && (count >= MAX_TIMEOUTS))
	{
		(state == 1) ? reset_state1_count() : (state == 2) ? reset_state2_count() : reset_state3_count();
		change_state();
		event = Timeout;
	}
	if(calibration > SLIDER_RIGHT_MIN && calibration <= SLIDER_LEFT_MIN)
	{
		change_state();
		event = Left_slider;
	}
	if(calibration > SLIDER_LEFT_MIN)
	{
		event = Right_slider;
	}

	if (read_state() == 3)
	{
		return SPI_Loopback;
	}

	return Read_XYZ_Acc;
}

//The Disconnected state indicates the Accelerometer is not responding for some reason.
// This state is reached via a Disconnect event, which should occur if the sensor is physically disconnected.
state_e Acc_Disconnect_Handler(void)
{
	LED_ClearRed();
	log_string(Status, Acc_Disconnect_Handler_f,"Sensor Disconnected.");
	log_string(Status, Acc_Disconnect_Handler_f,"Program ends.");
	end_state();
	return Error;
}

//Tests that all three accels in accelerometer is working properly.
state_e POST_Test_Handler(void)
{
	uint8_t result = 0;

	result = self_test();
	if(result == 1)
	{
		log_string(Status, POST_Test_Handler_f, "Power On Self Test failed.");
		event = Fail;
	}
	else
	{
		log_string(Status, POST_Test_Handler_f, "Power On Self Test Succeeded.");
		event = Pass;
	}
	return Read_XYZ_Acc;
}

// In the Process/Display state, use the current acceleration readings to display.
// Last X, Y, Z readings and the state entry count
// Average X, Y, Z readings
// Low X, Y, Z readings
// High X, Y, Z readings
void display_accel(void)
{
	uint8_t state, count;
	int16_t x_accel, y_accel, z_accel;
	accel_return(&x_accel, &y_accel, &z_accel);

	state = read_state();
	count = (int8_t)((state == 1) ? read_state1_count() : (state == 2) ? read_state2_count() : read_state3_count());

	static int16_t x1[6], y1[6], z1[6], x2[6], y2[6], z2[6], x3[6], y3[6], z3[6];

	int16_t ax = 0, ay = 0, az = 0;
	int16_t minx, miny, minz, maxx, maxy, maxz;

	if(state == 1)		///Calculations for State machine 1
	{
		x1[count - 1] = x_accel;
		y1[count - 1] = y_accel;
		z1[count - 1] = z_accel;

		minx = x1[0], miny = y1[0], minz = z1[0];
		maxx = x1[0], maxy = y1[0], maxz = z1[0];

		for(uint8_t i = 0; i < count; i++)			// Calculate the average value
		{
			ax += x1[i];
			ay += y1[i];
			az += z1[i];
		}
		ax = (int16_t) (ax / count);
		ay = (int16_t) (ay / count);
		az = (int16_t) (az / count);

		for(uint8_t i = 1; i < count; i++)				//Calculate the minimum value
		{
			if(x1[i] < minx) { minx = x1[i]; }
			if(y1[i] < miny) { miny = y1[i]; }
			if(z1[i] < minz) { minz = z1[i]; }
		}

		for(uint8_t i = 1; i < count; i++)			//Calculate the maximum value
		{
			if(x1[i] > maxx) { maxx = x1[i]; }
			if(y1[i] > maxy) { maxy = y1[i]; }
			if(z1[i] > maxz) { maxz = z1[i]; }
		}
	}

	if(state == 2)			///Calculations for State machine 2
	{
		x2[count - 1] = x_accel;
		y2[count - 1] = y_accel;
		z2[count - 1] = z_accel;

		minx = x2[0], miny = y2[0], minz = z2[0];
		maxx = x2[0], maxy = y2[0], maxz = z2[0];

		for(uint8_t i = 0; i < count; i++)
		{
			ax += x2[i];
			ay += y2[i];
			az += z2[i];
		}
		ax = (int16_t) (ax / count);
		ay = (int16_t) (ay / count);
		az = (int16_t) (az / count);

		for(uint8_t i = 2; i < count; i++)
		{
			if(x2[i] < minx) { minx = x2[i]; }
			if(y2[i] < miny) { miny = y2[i]; }
			if(z2[i] < minz) { minz = z2[i]; }
		}

		for(uint8_t i = 2; i < count; i++)
		{
			if(x2[i] > maxx) { maxx = x2[i]; }
			if(y2[i] > maxy) { maxy = y2[i]; }
			if(z2[i] > maxz) { maxz = z2[i]; }
		}
	}

	if(state == 3)						///Calculations for State machine 3
	{
		x3[count - 1] = x_accel;
		y3[count - 1] = y_accel;
		z3[count - 1] = z_accel;

		minx = x3[0], miny = y3[0], minz = z3[0];
		maxx = x3[0], maxy = y3[0], maxz = z3[0];

		for(uint8_t i = 0; i < count; i++)
		{
			ax += x3[i];
			ay += y3[i];
			az += z3[i];
		}
		ax = (int16_t) (ax / count);
		ay = (int16_t) (ay / count);
		az = (int16_t) (az / count);

		for(uint8_t i = 1; i < count; i++)
		{
			if(x3[i] < minx) { minx = x3[i]; }
			if(y3[i] < miny) { miny = y3[i]; }
			if(z3[i] < minz) { minz = z3[i]; }
		}

		for(uint8_t i = 1; i < count; i++)
		{
			if(x3[i] > maxx) { maxx = x3[i]; }
			if(y3[i] > maxy) { maxy = y3[i]; }
			if(z3[i] > maxz) { maxz = z3[i]; }
		}
	}


	char message1[40];
	char message2[2];
	strcpy(message1, "Current Timeout Count: ");
	itoa((count - 1), message2, 10);
	strcat(message1, message2);

	log_string(Status, display_accel_f, message1);
	log_accel(x_accel,y_accel,z_accel,ax,ay,az,minx,miny,minz,maxx,maxy,maxz);

}

