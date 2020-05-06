/*
 * write_pattern.c
 *
 *  Created on: Feb 22, 2020
 *      Author: Disha
 */
#include "main.h"

void write_pattern(arg_t *function_args)
{
	function_args->allocate_mem = function_args->mem_address;

	verify_memory(function_args);

	if(!function_args->mem_allocated)
	{
		function_args->error = FAILED;
		log_string("ERROR NO:");
		log_integer(function_args->error);
		log_string("FAILED: NO ALLOCATED MEMORY, DISPLAY MEM FAILED!");
	}
	else if(function_args->n_bytes > function_args->mem_size)
	{
		function_args->error = OUT_OF_RANGE;
		log_string("OUT_OF_RANGE: NUMBER OF BYTES TO DISPLAY IS LARGER THAN ALLOCATED MEM SIZE!");
	}
	else
	{
		uint8_t *mem_8;
		mem_8 = (uint8_t *)function_args->allocate_mem;

		gen_pattern(function_args->n_bytes, function_args->seed, mem_8);
		function_args->error = SUCCESS;
	}

	log_string("Write Pattern Result:");
	log_integer(function_args->error);
}


