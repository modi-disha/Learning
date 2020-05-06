/*
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    MKL25Z128xxx4_Project.c
 * @brief   Application entry point.
 */

#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "command_parser.h"
#include "main.h"

#define UCUNIT

/*
 * @brief   Application entry point.
 */
int main(void)
{
/*  -------------------------------------------------------------------  */
  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

/* Uncomment log_enable() to turn on the log messages */
    log_enable();
    //log_disable();

    log_status();

    uint8_t NUMBER_OF_COMMANDS = 21;
/*  -----------	--------------------------------------------------------  */

    /* Input Command Set as defined in Project 3 Description */
    const char *command_set[21] = {
    		"A,32",						//Allocate a 32 byte region in the heap
			"M",						//Verify that memory is allocated (True)
			"P,32,143",					//Write a pattern using the seed 143 to the first 32 bytes of the allocated memory
			"D,32",						//Display the first 32 bytes of allocated memory
			"D,34",						//Display the first 34 bytes of allocated memory (Out of range error)
			"C,32,143",					//Compare the first 32 bytes of allocated memory to the pattern with seed 143 (True)
			"W,12,2,0xFFEE",			//Write the hex value 0xFFEE to 2 bytes of allocated memory starting at byte 12
			"D,32",						//Display the first 32 bytes of allocated memory
			"C,32,143",					//Compare the first 32 bytes of allocated memory to the pattern with seed 143 (False)
			"P,16,127",					//Write a pattern using the seed 127 to the first 16 bytes of the allocated memory
			"D,16",						//Display the first 16 bytes of allocated memory
			"C,16,127",					//Compare the first 16 bytes of allocated memory to the pattern with seed 127 (True)
			"I,35,2",					//Invert all bits in 2 bytes of allocated memory starting at byte 35 (Out of range error)
			"I,9,2",					//Invert all bits in 2 bytes of allocated memory starting at byte 9
			"D,16",						//Display the first 16 bytes of allocated memory
			"C,16,127",					//Compare the first 16 bytes of allocated memory to the pattern with seed 127 (False)
			"I,9,2",					//Invert all bits in 2 bytes of allocated memory starting at byte 9
			"C,16,127",					//Compare the first 16 bytes of allocated memory to the pattern with seed 127 (True)
			"D,16",						//Display the first 16 bytes of allocated memory
			"F",						//Free the allocated memory in the heap
			"M"							//Verify that memory is allocated (False)
    };


	/* Array for a set of commands */
    const command_t commands[] = {
    		{"A", &allocate_bytes, "Allocate n_bytes (arg0) region in the heap"},			//ToDo: Write the description
			{"F", &free_allocated, "Free the allocated memory in the heap"},
			{"M", &verify_memory, "Verify memory is allocated"},
			{"D", &display_memory, "Display first n_bytes (arg0) of allocated memory"},
			{"W", &write_memory, "Write hex value (arg2) to n_bytes (arg1) of allocated memory starting at mem_address (arg0) "},
			{"I", &invert_block, "Invert all bits in n_bytes (arg1) of allocated memory starting at mem_address (arg0)"},
			{"P", &write_pattern, "Write a pattern using the seed (arg1) to the first n_bytes (arg0) of the allocated memory"},
			{"C", &compare_pattern, "Compare the first n_bytes (arg0) of allocated memory starting at mem_address (arg1)"},
			{"",0,""}
    };

  /* Assumption: Memory allocation limit 255 bytes */

    uint32_t heap_address = 0x1ffff220;  /* heap_start address */
    uint16_t heap_size = 0;
    arg_t assigned_arg;    /* Assign arguments to assigned_arg struct object from command script */
    assigned_arg.allocate_mem = NULL;
	assigned_arg.values = NULL;

    for (int i=0; i<NUMBER_OF_COMMANDS; i++)
    {
    	// Get the current command
        assigned_arg.mem_size = heap_size;
        assigned_arg.mem_address = heap_address;
    	// Parse the current command
    	char current_command[15];
    	memset(current_command, '\0', 15);
    	strcpy(current_command,command_set[i]);
    	uint8_t cmd_type = command_parser(&assigned_arg, current_command);

    	// Assign the correct function to the function pointer
    	memTest command_func = commands[cmd_type].memFunction;

    	log_string(commands[cmd_type].description);
    	// Call the function
    	command_func(&assigned_arg);

    	// Update the global variables
    	heap_address = assigned_arg.mem_address;
    	heap_size = assigned_arg.mem_size;
    }


	//ToDo: after function run check error_status error to turn-on the LED.

#ifdef UCUNIT

    Run_Testcases();

#endif

    return 0 ;
}
