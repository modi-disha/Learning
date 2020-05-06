
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
 * @file Slider.h
 * @brief An abstraction for Touch Slider unit.
 *
 * This header file provides an abstraction for Touch Slider Calibrations,
 * and initialization.
 *
 * @author Disha Modi and Alexandra Paquin
 * @date March 2020
 * @version 1.0
 *
 */

#ifndef SLIDER_H_
#define SLIDER_H_

#include <MKL25Z4.h>
#include "SysTick.h"
#include "logger.h"

#define SCAN_DATA TSI0->DATA & 0xFFFF 		// Accessing the bits held in TSI0_DATA_TSICNT
#define BOARD_TOUCH_PORT TSI0

#define SLIDER_NONE_MIN		0
#define SLIDER_RIGHT_MIN	700
#define SLIDER_LEFT_MIN 	1400

#define MAX_TIMEOUTS		6

/**
 * @brief Touch Slider initialization routine
 *
 * @param TSI_Type *base pointer to touch slider port
 *
 * @return void
 */
void TOUCH_init(TSI_Type *base);

/**
 * @brief Touch Slider calibration routine
 *
 * @param TSI_Type *base pointer to touch slider port
 *
 * @return uint16_t returns calibration value
 */
uint16_t TOUCH_Calibrate(TSI_Type *base);


#endif /* SLIDER_H_ */
