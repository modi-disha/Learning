/*
 * invert_mem.c
 *
 *  Created on: Feb 22, 2020
 *      Author: Disha
 */

#include "main.h"

void invert_block(arg_t *function_args)
{
	function_args->allocate_mem = function_args->mem_address;

    uint8_t inv_byte = 0xFF;
	verify_memory(function_args);

	if(!function_args->mem_allocated)
	{
		function_args->error = FAILED;
		log_string("ERROR NO:");
		log_integer(function_args->error);
		log_string("FAILED: NO ALLOCATED MEMORY, DISPLAY MEM FAILED!");
	}
	else if((function_args->n_bytes + (function_args->m_offset - 1)) > function_args->mem_size)
	{
		function_args->error = OUT_OF_RANGE;
		log_string("ERROR NO:");
		log_integer(function_args->error);
		log_string("function_args->error: NUMBER OF BYTES TO DISPLAY IS LARGER THAN ALLOCATED MEM SIZE!");

	}
	else
	{
		uint8_t *mem_8;
		mem_8 = (uint8_t *)function_args->allocate_mem;

		for(uint8_t i = (function_args->m_offset - 1); i < (function_args->n_bytes + (function_args->m_offset - 1)); i++)
		{
			*(mem_8 + i) ^= inv_byte;
		}
		function_args->error = SUCCESS;
	}

	log_string("Invert Block Result:");
	log_integer(function_args->error);
}

