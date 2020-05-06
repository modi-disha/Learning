/*
 * command_parser.h
 *
 *  Created on: Feb 27, 2020
 *      Author: Alexandra Paquin
 */

#ifndef COMMAND_PARSER_H_
#define COMMAND_PARSER_H_

#include "main.h"

typedef enum command_index{
	ALLOCATE_MEM = 0,
	FREE_MEM = 1,
	VERIFY_MEM = 2,
	DISPLAY_MEM = 3,
	WRITE_MEM = 4,
	INVERT_BLOCK = 5,
	WRITE_PATTERN = 6,
	COMPARE_PATTERN = 7,
	ERROR = 8
}command_index;


uint8_t command_parser(arg_t *arguments, char *command);

#endif /* COMMAND_PARSER_H_ */
