/*
 * verify_mem.c
 *
 *  Created on: Feb 22, 2020
 *      Author: Disha
 */
#include "main.h"

void verify_memory(arg_t *function_args)
{

	function_args->allocate_mem = function_args->mem_address;

	if(!function_args->allocate_mem)
	{
		function_args->error = FAILED;
		log_string("ERROR NO:");
		log_integer(function_args->error);
		log_string("FAILED: NO ALLOCATED MEMORY, VERIFY MEM FAILED!");
		function_args->mem_allocated = 0;
	}
	else
	{
		function_args->mem_allocated = 1;
		function_args->error = SUCCESS;
	}

	log_string("Verify Memory Result:");
	log_integer(function_args->error);
}
