/*
 * function_args->allocate_mem.c
 *
 *  Created on: Feb 22, 2020
 *      Author: Disha
 */

#include "main.h"

void allocate_bytes(arg_t *function_args)
{
	uint32_t mem_start = (uint32_t)function_args->mem_address;
	uint32_t heap_end = 0x1ffff620;

	if((mem_start + function_args->n_bytes) == heap_end)
	{
		function_args->error = INVALID_REQUEST;
		PRINTF("ERROR: INVALID ALLOCATION REQUEST\n\r");
		log_string("ERROR NO:");
		log_integer(function_args->error);
		log_string("INVALID_REQUEST: Allocation request surpassing max heap size.");
	}

	function_args->allocate_mem = (uint32_t *)malloc((function_args->n_bytes / 4) * (sizeof(uint32_t)));
	memset(function_args->allocate_mem, 0, ((function_args->n_bytes / 4) * (sizeof(uint32_t))));
	function_args->mem_address = (uint32_t *) function_args->allocate_mem;

	if(!function_args->allocate_mem)
	{
		function_args->error = FAILED;
		log_string("ERROR NO:");
		log_integer(function_args->error);
		log_string("FAILED: MEMORY ALLOCATION FAILED!");
	}
	else
	{
		function_args->error = SUCCESS;
	}
	function_args->mem_size = function_args->n_bytes;

	log_string("Allocate Bytes Result:");
	log_integer(function_args->error);
}
