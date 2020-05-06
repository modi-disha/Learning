/*
 * application.h
 *
 *  Created on: Apr 9, 2020
 *      Author: Alexandra Paquin
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#define ASCII_CHAR_MIN			(0x21)
#define ASCII_CHAR_MAX			(0x7E)
#define ASCII_CHAR_NUM			94

#define REPORT_MAX_PER_LINE		8

#include <stdint.h>

#include "logger.h"


void update_char_count(uint8_t ch);

char* get_report(void);

uint16_t calc_report_memory_required(void);

#endif /* APPLICATION_H_ */
