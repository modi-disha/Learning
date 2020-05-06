/*
 * logger.c
 *
 *  Created on: Feb 27, 2020
 *      Author: Disha
 */

#include "logger.h"

typedef enum log{ log_off = 0, log_on }log;

log logger = log_off;

void log_enable(void)
{
	logger = log_on;
	#define LOG
	printf("Logger enabled!\n\r");
	printf("**************************************\n\r");
	printf("Name: ");
	printf("PES Project#3\n\r");
	printf("Compiled: ");
	printf(__DATE__);
	printf("	Time: ");
	printf(__TIME__);
	printf("\n\rVersion: 1.0\n\r");
	printf("**************************************\n\r");
}

void log_disable(void)
{
	logger = log_off;
	printf("Logger disabled!\n\r");
}

void log_status(void)
{
	log_string("Log Status: ");
	if(logger == log_on)
	{
		printf("Log on\n\r");
	}
	else
	{
		printf("Log Off\n\r");
	}
}

/*
 * display in hexadecimal an address and contents of a memory location,
 * arguments are a pointer to a sequence of bytes and a specified length
 * */
void log_data(uint8_t *pointer, uint8_t size)
{
#ifdef LOG

	printf("An address of a memory location: %p\n\r", pointer);
	printf("Sequence of %d bytes at the memory location: ", size);

	for(uint8_t i = 0; i < size; i++)
	{
		if((i % 8) == 0)
		{
			printf("\n\r");
		}
		printf("%2x ", *(pointer + i));
	}
	printf("\n\r");

#endif
}

/* display a string */
void log_string(char *s)
{
#ifdef LOG

	printf("%s\n\r", s);

#endif
}

/* display an integer */
void log_integer(int x)
{
#ifdef LOG

	printf("%d\n\r", x);

#endif
}
