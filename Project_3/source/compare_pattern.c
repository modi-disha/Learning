/*
 * compare_pattern.c
 *
 *  Created on: Feb 22, 2020
 *      Author: Disha
 */

#include "main.h"

void compare_pattern(arg_t *function_args)
{
	function_args->allocate_mem = function_args->mem_address;

	verify_memory(function_args);

	if(!function_args->mem_allocated)
	{
		function_args->error = FAILED;
		log_string("ERROR NO:");
		log_integer(function_args->error);
		log_string("FAILED: NO ALLOCATED MEMORY, COMPARE PATTERN FAILED!");
	}
	else if(function_args->n_bytes > function_args->mem_size)
	{
		function_args->error = OUT_OF_RANGE;
		log_string("ERROR NO:");
		log_integer(function_args->error);
		log_string("OUT_OF_RANGE: NUMBER OF BYTES TO COMPARE IS LARGER THAN ALLOCATED MEM SIZE!");
	}
	else
	{
		uint8_t *mem_8;
		uint8_t buff_8[function_args->n_bytes + 1];
		mem_8 = (uint8_t *)function_args->allocate_mem;
		function_args->error = SUCCESS;

		gen_pattern(function_args->n_bytes, function_args->seed, buff_8);

		for(uint8_t i = 0; i < function_args->n_bytes; i++)
		{
			if(*(mem_8 + i) != buff_8[i])
			{
				function_args->error = FAILED;
			}
		}
	}

	log_string("Compare Pattern Result:");
	log_integer(function_args->error);

}

