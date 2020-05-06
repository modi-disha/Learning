

#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "error_code.h"
#include "miscellaneous.h"
#include "uCUnit_testsuit.h"
#include "logger.h"

/* structure to pass function arguments */
typedef struct function_argumetns
{
	mem_status error;
	uint32_t *allocate_mem;
	uint32_t *mem_address;
	uint16_t mem_size;
	uint8_t n_bytes;
	uint8_t m_offset;
	uint8_t seed;
	uint8_t *values;   //ToDo: from command script convert string to hex value and then typecast it to uint8_t pointer or array
	bool mem_allocated;
} arg_t;

typedef void(*memTest)(arg_t *arg);

/* structure to define pattern for commands */
typedef struct commandStruct
{
	char const *name;     /* command-names like A, M, D... */
	memTest memFunction;  /* pointer to memory test functions */
	char const *description; /* Function description */
} command_t;

void allocate_bytes(arg_t *function_args);
void free_allocated(arg_t *function_args);
void verify_memory(arg_t *function_args);
void display_memory(arg_t *function_args);
void write_memory(arg_t *function_args);
void invert_block(arg_t *function_args);
void write_pattern(arg_t *function_args);
void compare_pattern(arg_t *function_args);



#endif /* MAIN_H_ */
