/*
 * free_mem.c
 *
 *  Created on: Feb 22, 2020
 *      Author: Disha
 */
#include "main.h"

void free_allocated(arg_t *function_args)
{
	function_args->allocate_mem = function_args->mem_address;

	if(!function_args->allocate_mem)
	{
		function_args->error = FAILED;
		printf("Warning: NO ALLOCATED MEMORY\n\r");
		log_string("ERROR NO:");
		log_integer(function_args->error);
		log_string("FAILED: NO ALLOCATED MEMORY, FREE MEM FAILED!"); //ToDo: Define function_args->error-msg and pass to the logger to print
	}
	else
	{
		function_args->error = SUCCESS;
	}

	free(function_args->allocate_mem);
	function_args->allocate_mem = NULL;
	function_args->mem_size = 0;
	function_args->mem_allocated = 0;

	log_string("Free Memory Result:");
	log_integer(function_args->error);
}
