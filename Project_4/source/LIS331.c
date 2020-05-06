/*
 * LIS331.c
 *
 *  Created on: Mar 19, 2020
 *      Author: Disha
 */
#include "LIS331.h"
#include <math.h>

volatile int16_t xaccel, yaccel, zaccel;

int acc_init(void)
{
	uint8_t data = 0x01;	//set active mode, 14 bit samples and 800 Hz ODR

	i2c_write_byte(dev_id, REG_CTRL1, data);
	return 1;
}

int accel_read(void)
{
	uint8_t xl, xh, yl, yh, zl, zh;
	int16_t tempx, tempy, tempz;

	i2c_start();
	i2c_read_setup(dev_id, REG_XHI);
	xh = i2c_repeated_read(0);
	xl = i2c_repeated_read(0);

	yh = i2c_repeated_read(0);
	yl = i2c_repeated_read(0);

	zh = i2c_repeated_read(0);
	zl = i2c_repeated_read(1);

	tempx = (int16_t) (xl | (xh << 8)); //concatenate low and high bits together, load into signed 16 bit
	xaccel = SCALE * tempx;    //multiply by scale factor for g-level
	tempy = (int16_t) (yl | (yh << 8));
	yaccel = SCALE * tempy;
	tempz = (int16_t) (zl | (zh << 8));
	zaccel = SCALE * tempz;

	int fail = read_i2c_lock();

	if(fail == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int self_test(void)
{
	uint8_t data = 0x80;	//normal mode, 400Hz, xyz-enabled
	int16_t pre_x = 0 , pre_y = 0, pre_z = 0;
	int16_t post_x = 0, post_y = 0, post_z = 0;
	int16_t diff_x, diff_y, diff_z;

	accel_read();
	pre_x = xaccel;
	pre_y = yaccel;
	pre_z = zaccel;
	Delay(100);
	i2c_write_byte(dev_id, REG_CTRL2, data); //Full scale, Self-test enabled, self-test plus mode

	Delay(100);
	accel_read();

	Delay(100);
	data = 0x00;
	i2c_write_byte(dev_id, REG_CTRL2, data); //Disable self-test mode

	post_x = xaccel;
	post_y = yaccel;
	post_z = zaccel;

	diff_x = post_x - pre_x;
	diff_y = post_y - pre_y;
	diff_z = post_z - pre_z;

	/*
	//+181 +255 +1680
	if((diff_x >= 0) && (diff_x <= 185))
	{
		flag_x = 1;
	}
	if((diff_y >= 0) && (diff_y <= 260))
	{
		flag_y = 1;
	}
	if((diff_z >= 0) && (diff_y <= 1685))
	{
		flag_z = 1;
	}
	*/

	if((diff_z + diff_y + (-diff_x)) != 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void accel_return(double *x, double *y, double *z)
{
	*x = xaccel;
	*y = yaccel;
	*z = zaccel;
}

void Delay(uint32_t dly)
{
	 volatile uint32_t t;

		for (t=dly*10000; t>0; t--)
			;
}
