/*
 * logger.h
 *
 *  Created on: Feb 23, 2020
 *      Author: Disha
 *
 *
 *      Logging functions include:
o Log_enable – begin printing log messages when called
o Log_disable – ignore any log messages until re-enabled
o Log_status – returns a flag to indicate whether the logger is enabled or disabled
o Log_data – display in hexadecimal an address and contents of a memory location, arguments are a pointer to a sequence of bytes and a specified length
o Log_string – display a string
o Log_integer – display an integer
o The previous three commands should include a new line after each display
 */


#ifndef LOGGER_H_
#define LOGGER_H_

#include<stdio.h>
#include<string.h>
#include<stdint.h>
#include<stdlib.h>

/* Log_enable – begin printing log messages when called
o Log_disable – ignore any log messages until re-enabled
o Log_status – returns a flag to indicate whether the logger is enabled or disabled
o Log_data – display in hexadecimal an address and contents of a memory location, arguments are a pointer to a sequence of bytes and a specified length
o Log_string – display a string
o Log_integer – display an integer */

void log_enable(void);
void log_disable(void);
void log_status(void);
void log_data(uint8_t *pointer, uint8_t size);
void log_string(char *s);
void log_integer(int x);

#endif /* LOGGER_H_ */
