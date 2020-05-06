
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
 * @file SysTick.h
 * @brief An abstraction for SysTick interrupt.
 *
 * This header file provides an abstraction for SysTick interrupt enable,
 * disable and initialization.
 *
 * @author Disha Modi and Alexandra Paquin
 * @date March 2020
 * @version 1.0
 *
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "MKL25Z4.h"
#include "logger.h"

typedef enum {
	PENDING_TIMEOUT,
	NO_TIMEOUT,
	TIMEOUT
} timeout_e;

extern timeout_e timeout_reached;

/**
 * @brief SysTick Timer initialization routine
 *
 * @param void
 *
 * @return void
 */
void SysTick_init(void);

/**
 * @brief SysTick Timer enable routine
 *
 * @param void
 *
 * @return void
 */
void SysTick_enable_interrupt(void);

/**
 * @brief SysTick Timer disable routine
 *
 * @param void
 *
 * @return void
 */
void SysTick_disable_interrupt(void);



#endif /* SYSTICK_H_ */
