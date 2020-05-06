
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
 * @file SPI.h
 * @brief An abstraction for SPI drivers.
 *
 * This header file provides an abstraction for spi_loopback routine.
 *
 * @author Disha Modi and Alexandra Paquin
 * @date March 2020
 * @version 1.0
 *
 */

#ifndef SPI_H_
#define SPI_H_

#include <MKL25Z4.H>
#include "logger.h"

/**
 * @brief SPI initialization routine
 *
 * @param void
 *
 * @return void
 */
void SPI_init(void);

/**
 * @brief SPI loopback (echo) routine
 *
 * @param uint8_t echoed/received value
 *
 * @return uint8_t transmitted value
 */
uint8_t spi_loopback(uint8_t byte);


#endif /* SPI_H_ */
