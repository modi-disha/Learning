
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
 * @file queue.h
 * @brief An abstraction for circular buffer drivers.
 *
 * This header file provides an abstraction for helper routines to implement circular buffer.
 *
 * @author Disha Modi and Alexandra Paquin
 * @date April 2020
 * @version 1.0
 *
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include "main.h"

#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>

//Enum for circular buffer possible errors
typedef enum Errors
{
	Success, Error, Buff_full, Buff_empty, Invalid_request, Malloc_fail, Invalid_buffer
}errors_e;

//Structure include buffer pointer, head, tail, length
typedef struct Buffer
{
	uint8_t *buffer;
	unsigned int head;
	unsigned int tail;
	unsigned int length;
	bool full;

}buffer_t;

typedef buffer_t* buffer_p;

/**
 * @brief  Function to Pass in a storage buffer and size and Returns a circular buffer handle
 *
 * @param buffer_p cbuff, buffer structure pointer
 * @param unsigned int size, buffer size
 *
 * @return errors_e, returns error number
 */
errors_e circular_buff_init(buffer_p cbuff, unsigned int size);

/**
 * @brief Free a circular buffer structure and data buffer
 *
 * @param buffer_p cbuff, buffer structure pointer
 *
 * @return errors_e, returns error number
 */
errors_e circular_buff_free(buffer_p cbuff);

/**
 * @brief Reset the circular buffer to empty, head == tail
 *
 * @param buffer_p cbuff, buffer structure pointer
 *
 * @return errors_e, returns error number
 */
errors_e circular_buff_reset(buffer_p cbuff);

/**
 * @brief Put items in buffer continues to add data if the buffer is full
 * Old data is overwritte
 *
 * @param buffer_p cbuff, buffer structure pointer
 * @param uint8_t data, data to enqueue
 *
 * @return errors_e, returns error number
 */
errors_e circular_buff_enqueue(buffer_p cbuff, uint8_t data);

/**
 * @brief Retrieve a value from the buffer
 *
 * @param buffer_p cbuff, buffer structure pointer
 * @param uint8_t *data, returns data dequeued
 *
 * @return errors_e, returns error number
 */
errors_e circular_buff_dequeue(buffer_p cbuff, uint8_t *data);

/**
 * @brief Returns true if the buffer is empty
 *
 * @param buffer_p cbuff, buffer structure pointer
 *
 * @return errors_e, returns error number
 */
errors_e circular_buff_empty(buffer_p cbuff);

/**
 * @brief Returns true if the buffer is full
 *
 * @param buffer_p cbuff, buffer structure pointer
 *
 * @return errors_e, returns error number
 */
errors_e circular_buff_full(buffer_p cbuff);

/**
 * @brief Returns the size of the buffer
 *
 * @param buffer_p cbuff, buffer structure pointer
 *
 * @return errors_e, returns error number
 */
uint8_t circular_buff_size(buffer_p cbuff);

/**
 * @brief Function to verify buffer is initialized  - buffer member inside struct is not null and have valid size
 *
 * @param buffer_p cbuff, buffer structure pointer
 *
 * @return errors_e, returns error number
 */
errors_e circular_buff_initialized(buffer_p cbuff);

/**
 * @brief Function to verify the buffer pointer is valid - buffer pointer returning valid address location
 *
 * @param buffer_p cbuff, buffer structure pointer
 *
 * @return errors_e, returns error number
 */
errors_e circular_buff_valid(buffer_p cbuff);

/**
 * @brief Function to verify the buffer pointer is valid
 *
 * @param buffer_p cbuff, buffer structure pointer
 *
 * @return errors_e, returns error number
 */
errors_e pointer_check(buffer_p cbuff);

#endif /* QUEUE_H_ */
