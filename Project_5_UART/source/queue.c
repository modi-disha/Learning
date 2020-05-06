
/********************************************************************************
 * File name: "queue.c"
 *
 * Description: circular buffer driver routines
 *
 * File​ ​ Author​ ​ Name: Disha Modi and Alexandra Paquin
 *
 * Tools​ ​ used​ ​ to​ ​ process​ ​ the​ ​ code​ ​ (compiler,​ ​ linker,​ ​ debugger):
 * 		NXP MCU Tools, Gnu Make Builder, Putty
 *
 * Identification​ ​ of​ ​ any​ ​ leveraged​ ​ code: https://embeddedartistry.com/blog/2017/05/17/creating-a-circular-buffer-in-c-and-c/
 *
 * Applicable​ ​ Links: None
 *******************************************************************************/

#include "queue.h"
#include "fsl_common.h"

/**
 * @brief  Function to Pass in a storage buffer and size and Returns a circular buffer handle
 */
errors_e circular_buff_init(buffer_p cbuff, unsigned int size)
{
	if(!(cbuff->buffer = (uint8_t*) malloc(size * sizeof(uint8_t))))
		return Malloc_fail;
	cbuff->head = 0;
	cbuff->tail = 0;
	cbuff->length = size;
	cbuff->full = false;
	return Success;
}

/**
 * @brief Free a circular buffer structure and data buffer
 */
errors_e circular_buff_free(buffer_p cbuff)
{
	if(cbuff->buffer)
		free(cbuff->buffer);
	if(!cbuff)
		return Invalid_request;
	free(cbuff);
	return Success;
}


/**
 * @brief Reset the circular buffer to empty, head == tail
 */
errors_e circular_buff_reset(buffer_p cbuff)
{
	if(pointer_check(cbuff))
		return Invalid_buffer;
	cbuff->head = 0;
	cbuff->tail = 0;
	cbuff->full = false;
	return Success;
}

/**
 * @brief Put items in buffer continues to add data if the buffer is full
 * Old data is overwritte
 */
errors_e circular_buff_enqueue(buffer_p cbuff, uint8_t data)
{
	if(pointer_check(cbuff))
		return Invalid_buffer;

	uint32_t _intMask;
	_intMask = START_CRITICAL(); 								// disable interrupts

	cbuff->buffer[cbuff->head] = data;							//enqueue

	if(circular_buff_full(cbuff))
	{
		cbuff->tail = (cbuff->tail + 1) % cbuff->length;		//over-write tail shift
	}

	cbuff->head = (cbuff->head + 1) % cbuff->length;
	if(cbuff->head == cbuff->tail)
	{
		cbuff->full = true;
	}
	END_CRITICAL(_intMask);										//re-enable the interrupts

	return Success;
}

/**
 * @brief Retrieve a value from the buffer
 */
errors_e circular_buff_dequeue(buffer_p cbuff, uint8_t *data)
{
	if(pointer_check(cbuff))
		return Invalid_buffer;
	if(!data)
		return Invalid_request;

	if(!circular_buff_empty(cbuff))
	{
		uint32_t _intMask;
		_intMask = START_CRITICAL(); 			// disable interrupts
		*data = cbuff->buffer[cbuff->tail];		//dequeue
		cbuff->full = false;
		cbuff->tail = (cbuff->tail + 1) % cbuff->length;
		END_CRITICAL(_intMask);					//re-enable the interrupts
		return Success;
	}
	else
		return Buff_empty;
}

/**
 * @brief Returns true if the buffer is empty
 */
errors_e circular_buff_empty(buffer_p cbuff)
{
	if(pointer_check(cbuff))
		return Invalid_buffer;

	return(!cbuff->full && (cbuff->head == cbuff->tail));
}

/**
 * @brief Returns true if the buffer is full
 */
errors_e circular_buff_full(buffer_p cbuff)
{
	if(pointer_check(cbuff))
		return Invalid_buffer;

	if(circular_buff_size(cbuff) == cbuff->length)
	{
		cbuff->full = true;
	}
	else if(!cbuff->full)
		cbuff->full = false;
	return (cbuff->full);
}

/**
 * @brief Returns the size of the buffer
 */
uint8_t circular_buff_size(buffer_p cbuff)
{
	uint8_t size;
	if(pointer_check(cbuff))
		return Invalid_buffer;

	size = cbuff->length;

	if(!cbuff->full)
	{
		if(cbuff->head >= cbuff->tail)
			size = (cbuff->head - cbuff->tail);
		else
			size = (cbuff->length + cbuff->head - cbuff->tail);
	}
	return size;
}

/**
 * @brief Function to verify buffer is initialized  - buffer member inside struct is not null and have valid size
 */
errors_e circular_buff_initialized(buffer_p cbuff)
{
	if(pointer_check(cbuff))
		return Invalid_buffer;

	if(!cbuff->length)
		return Invalid_buffer;
	return Success;
}

/**
 * @brief Function to verify the buffer pointer is valid - buffer pointer returning valid address location
 */
errors_e circular_buff_valid(buffer_p cbuff)
{
	return pointer_check(cbuff);
}

/**
 * @brief Function to verify the buffer pointer is valid
 */
errors_e pointer_check(buffer_p cbuff)
{
	if(!cbuff->buffer)
		return Invalid_buffer;
	return Success;
}
