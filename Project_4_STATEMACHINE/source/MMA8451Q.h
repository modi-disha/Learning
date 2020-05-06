
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
 * @file MMA8451Q.h
 * @brief An abstraction for MMA8451Q Accelerometer Unit.
 *
 * This header file provides an abstraction for MMA8451Q Accelerometer Unit's read,
 * self-test and initialization routines.
 *
 * @author Disha Modi and Alexandra Paquin
 * @date March 2020
 * @version 1.0
 *
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#ifndef MMA8451Q_H_
#define MMA8451Q_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "I2C.h"
#include "logger.h"

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
#define REG_CTRL5 0x2E

#define WHOAMI 0x1A

#define COUNTS_PER_G (4096.0)
#define M_PI (3.14159265)

/*******************************************************************************
 * Enums and Structures
 ******************************************************************************/
typedef enum {
	I2C,
	SPI
} serial_protocal;

extern serial_protocal current_protocal;

/**
 * @brief Accelerometer Initialization routine
 *
 * @param Void
 *
 * @return int returns status
 */
int ACC_init(void);

/**
 * @brief Reads Accelerometer XYZ parameters
 *
 * @param Void
 *
 * @return int returns status
 */
int accel_read(void);

/**
 * @brief Accelerometer XYZ readings display routine
 *
 * @param Void
 *
 * @return Void
 */
void display_accel(void);

/**
 * @brief Accelerometer Self-Test routine
 *
 * @param Void
 *
 * @return int returns status
 */
int self_test(void);

/**
 * @brief Delay routine
 *
 * @param uint32_t tick numbers to generate delay
 *
 * @return void
 */
void Delay(uint32_t dlyticks);

/**
 * @brief Accelerometer XYZ readings
 *
 * @param XYZ pass by reference parameters
 *
 * @return void
 */
void accel_return(int16_t *x, int16_t *y, int16_t *z);

#endif /* MMA8451Q_H_ */
