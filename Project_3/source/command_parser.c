/*
 * script_parser.c
 *
 *  Created on: Feb 27, 2020
 *      Author: Alexandra Paquin
 */

#include "main.h"
#include "command_parser.h"
#include <string.h>

uint8_t command_parser(arg_t *arguments, char *command){

		int cmd_index = ERROR;
		char *end = NULL;
		char *arg = NULL;
		arg = strtok(command,",");

		// Check if Allocate Memory command
		if (!strcmp("A",arg))
		{
			arg = strtok(NULL,",");
			if (arg != NULL)
			{
				arguments->n_bytes = (uint8_t)strtoul(arg, &end, 10);
				cmd_index = ALLOCATE_MEM;
			}
		}
		// Check if Free Memory command
		else if (!strcmp("F",arg))
		{
			cmd_index = FREE_MEM;
		}
		// Check if Verify Memory command
		else if (!strcmp("M",arg))
		{
			cmd_index = VERIFY_MEM;
		}
		// Check if Display Memory command
		else if (!strcmp("D",arg))
		{
			arg = strtok(NULL,",");
			if (arg != NULL)
			{
				arguments->n_bytes = (uint8_t)strtoul(arg, &end, 10);
				cmd_index = DISPLAY_MEM;
			}
		}
		// Check if Write Hex Value command
		else if (!strcmp("W",arg))
		{
			arg = strtok(NULL,",");
			if (arg != NULL)
			{
				arguments->m_offset = (uint8_t)strtoul(arg, &end, 10);
				arg = strtok(NULL,",");
				if (arg != NULL){
					arguments->n_bytes = (uint8_t)strtoul(arg, &end, 10);
					arg = strtok(NULL,",");
					if (arg != NULL){
						uint32_t hex_value;
						sscanf(arg,"%x",&hex_value);
						uint8_t msb = (uint8_t)((hex_value) >> 8);
						uint8_t lsb = (uint8_t)((hex_value) & 0x00FF);
						arguments->values = (uint8_t *)malloc((arguments->n_bytes) * sizeof(uint8_t));
						memset(arguments->values, 0, arguments->n_bytes);
						*(arguments->values) = msb;
						*(arguments->values + 1) = lsb;
						cmd_index = WRITE_MEM;
					}
				}
			}
		}
		// Check if Invert Block command
		else if (!strcmp("I",arg))
		{
			arg = strtok(NULL,",");
			if (arg != NULL)
			{
				arguments->m_offset = (uint8_t)strtoul(arg, &end, 10);
				arg = strtok(NULL,",");
				if (arg != NULL){
					arguments->n_bytes = (uint8_t)strtoul(arg, &end, 10);
					arg = strtok(NULL,",");
					cmd_index = INVERT_BLOCK;
				}
			}
		}
		// Check if Write Pattern command
		else if (!strcmp("P",arg))
		{
			arg = strtok(NULL,",");
			if (arg != NULL)
			{
				arguments->n_bytes = (uint8_t)strtoul(arg, &end, 10);
				arg = strtok(NULL,",");
				if (arg != NULL){
					arguments->seed = (uint8_t)strtoul(arg, &end, 10);
					arg = strtok(NULL,",");
					cmd_index = WRITE_PATTERN;
				}
			}
		}
		// Check if Compare Pattern command
		else if (!strcmp("C",arg))
		{
			arg = strtok(NULL,",");
			if (arg != NULL)
			{
				arguments->n_bytes = (uint8_t)strtoul(arg, &end, 10);
				arg = strtok(NULL,",");
				if (arg != NULL){
					arguments->seed = (uint8_t)strtoul(arg, &end, 10);
					arg = strtok(NULL,",");
					cmd_index = COMPARE_PATTERN;
				}
			}
		}
		return (uint8_t)cmd_index;
}



