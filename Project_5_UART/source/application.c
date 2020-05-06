/*
 * application.c
 *
 *  Created on: Apr 9, 2020
 *      Author: Alexandra Paquin
 */


#include "application.h"

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*
 * Tracks how many times a character has been received
 * Includes all ascii characters between 0x21 and 0x7E
 */
static uint16_t char_count[ASCII_CHAR_NUM] = {0};
static char * report = NULL;



void update_char_count(uint8_t ch)
{

	if ((ch >= ASCII_CHAR_MIN) && (ch <= ASCII_CHAR_MAX))
	{
		char_count[(ch-ASCII_CHAR_MIN)]++;
	}

	char log_str[150];

	sprintf(log_str, "Updating Character Count for ascii character %c. Count is now %d.", ch, char_count[(ch-ASCII_CHAR_MIN)]);
	log_string(Debug, update_char_count_f, log_str);

}

char* get_report(void)
{

	log_string(Test, get_report_f, "Creating Character Report");

	// Calculate memory required for allocation
	uint16_t mem_size = calc_report_memory_required();

	// Free memory if it is allocated
	if (report)
	{
		free(report);
	}

	if (mem_size == 0)
	{
		return "\n\r No characters received";
	}
	report = (char*) malloc(mem_size* sizeof(char));

	if (!report)
	{
		// Print error
		#undef APPLICATION
		#define APPLICATION 0
		LED_ClearRed();
	}
	else
	{
		uint8_t num_characters = 0;
		char char_buff[12];

		// Iterate through all of the characters
		for (uint8_t i = 0; i < ASCII_CHAR_NUM; i++)
		{
			if (char_count[i])
			{
				num_characters += 1;

				if (num_characters % REPORT_MAX_PER_LINE)
				{
					sprintf(char_buff, " %c:%04d;", i+ASCII_CHAR_MIN, char_count[i]);
				}
				else
				{
					sprintf(char_buff, " %c:%04d;\n\r", i+ASCII_CHAR_MIN, char_count[i]);
				}

				if (num_characters == 1)
				{
					strcpy(report, "\n\r");
				}

				strcat(report, char_buff);

			}
		}

		strcat(report, "\n\r");
		if (num_characters % REPORT_MAX_PER_LINE)
		{
			strcat(report, "\n\r");
		}
	}


	return report;
}


uint16_t calc_report_memory_required(void)
{
	uint8_t num_characters = 0;
	uint16_t mem_required = 0;

	// Iterate through all of the characters
	for (uint8_t i = 0; i < ASCII_CHAR_NUM; i++)
	{
		// If the character has been received, add the associated memory required
		// 9 for ie. (" C:65535;", " C:   35;")
		if (char_count[i])
		{
				mem_required += 8;
				num_characters += 1;
		}
	}

	if (num_characters > 0)
	{
		mem_required += 4; // First and last newline/cariage return

		// Add more memory for the newlines and character returns
		mem_required += (num_characters / REPORT_MAX_PER_LINE) * (2);

		// If last line has not received memory for newline and carriage return
		if (num_characters % REPORT_MAX_PER_LINE != 0)
		{
			mem_required += 2;
		}

		// Add one final byte for the null character
		mem_required += 1;
	}

	char log_str1[100], log_str2[100];
	sprintf(log_str1, "Size of character report has been calculated to be %d", mem_required);
	log_string(Debug, calc_report_memory_required_f, log_str1);
	sprintf(log_str2, "Number of different characters received: %d", num_characters);
	log_string(Test, calc_report_memory_required_f, log_str2);

	return mem_required;
}
