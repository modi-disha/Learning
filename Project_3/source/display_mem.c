/*
 * display_mem.c
 *
 *  Created on: Feb 22, 2020
 *      Author: Disha
 */

#include "main.h"

void display_memory(arg_t *function_args)
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
		log_string("ERROR NO:");
		log_integer(function_args->error);
		log_string("OUT OF RANGE: NUMBER OF BYTES TO DISPLAY IS LARGER THAN ALLOCATED MEM SIZE!");
	}
	else
	{
		uint8_t *mem_8;
		uint32_t *mem_32;
		mem_32 = function_args->allocate_mem;
		mem_8 = (uint8_t *)function_args->allocate_mem;
		uint8_t num = function_args->n_bytes;


		printf("\n\rMemory Display:\n\r");
		printf("start_address hex_value_4bytes binary values of 4bytes:\n\r");
		for(uint8_t i = 0; i < num; i = i+4)
		{
			char *byte0 = NULL;
			char *byte1 = NULL;
			char *byte2 = NULL;
			char *byte3 = NULL;
			byte0 = dec_to_bstr((uint8_t)*(mem_8 + i), 8);
			byte1 = dec_to_bstr((uint8_t)*(mem_8 + i + 1), 8);
			byte2 = dec_to_bstr((uint8_t)*(mem_8 + i + 2), 8);
			byte3 = dec_to_bstr((uint8_t)*(mem_8 + i + 3), 8);

			printf("0x%08x 0x%08x %s %s %s %s\n\r", mem_32, *mem_32, byte0, byte1, byte2, byte3);

			mem_32++;
			free(byte0);
			free(byte1);
			free(byte2);
			free(byte3);
		}
		function_args->error = SUCCESS;
		printf("\n\r");
	}

	log_string("Display Memory Result:");
	log_integer(function_args->error);
}


