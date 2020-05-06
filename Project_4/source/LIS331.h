/*
 * LIS331.h
 *
 *  Created on: Mar 15, 2020
 *      Author: Disha
 */

#ifndef LIS331_H_
#define LIS331_H_

/*
    3-21-11
    Aaron Weiss, aaron at sparkfun dot com

	License: Creative Commons Attribution Share-Alike 3.0
	http://creativecommons.org/licenses/by-sa/3.0

	v10 Example
	-outputs x,y,z acceleration values every 1 ms
	-output is driven by a timer overflow interrupt, this allows the user to
	 more easily add additional code without messing with the timing
	-values are in g's

	LIS331 Accelerometer Configuration:
	4-wire SPI, normal mode, 400Hz

	Hardware:
	Atmega328p, 3.3V, ext. 8MHz, 38400 baud

	Hardware Conections (LIS to Arduino):

	LIS331   |   Arduino
	---------------------
	  VCC    |    VCC (3.3V)
	  CS     |    pin 10 (PB2)
	  SCL    |    pin 13 (PB5)
	  SA0    |    pin 12 (PB4)
	  SDA    |    pin 11 (PB3)
	  GND    |    pin GND

	Note: if you need a higher sampling frequency, you need to run a higher clock,
		  INT functionality not used
*/


//Use config and Accel functions from here...

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "I2C.h"

#define dev_id 0x3A
#define SCALE 0.25  //sets (2^14bits) = SCALE
#define REG_XHI 0x01
#define REG_XLO	0x02
#define REG_YHI 0x03
#define REG_YLO 0x04
#define REG_ZHI 0x05
#define REG_ZLO 0x06

#define REG_WHOAMI 0x0D
#define REG_CTRL1 0x2A
#define REG_CTRL2 0x2B
#define REG_CTRL4 0x2D

#define WHOAMI 0x1A

#define COUNTS_PER_G (4096.0)
#define M_PI (3.14159265)

int acc_init(void);
int accel_read(void);
void display_accel(void);
int self_test(void);
void Delay(uint32_t dlyticks);
void accel_return(double *x, double *y, double *z);

#endif /* LIS331_H_ */
