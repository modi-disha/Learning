/********************************************************************************
 * File name: "logger.c"
 *
 * Description: – Methods for handling the enabling/disabling of logging, status of logging,
 * and logging of hex data, strings, and integers.
 *
 * File​ ​ Author​ ​ Name: Disha Modi and Alexandra Paquin
 *
 * Tools​ ​ used​ ​ to​ ​ process​ ​ the​ ​ code​ ​ (compiler,​ ​ linker,​ ​ debugger):
 * 		NXP MCU Tools, Gnu Make Builder, Putty
 *
 * Identification​ ​ of​ ​ any​ ​ leveraged​ ​ code: None
 *
 * Applicable​ ​ Links: None
 *******************************************************************************/


#include "logger.h"

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

log_e logger = log_off;

log_level_e current_log_level = Test;

//Enumration for log levels: test, Debug and Status mode
static char *log_levels[MAX_LOG_LEVEL_COUNT] = {
		"[TEST]",
		"[DEBUG]",
		"[STATUS]"
};

static char *time_str = NULL;

void log_level(log_level_e log_level)
{
	char message[40];
	strcpy(message, "Setting minimum log level to ");
	strcat(message, log_levels[log_level]);

	log_string(Status, log_status_f, message);

	current_log_level = log_level;
}

/* Enables the logger */
void log_enable(void)
{
	logger = log_on;
	char log_str[300];

	strcpy(log_str,"Logger enabled!\n\r");
	strcat(log_str,"**************************************\n\r");
	strcat(log_str,"Name: ");
	strcat(log_str,"PES Project#5\n\r");
	strcat(log_str,"Compiled: ");
	strcat(log_str,__DATE__);
	strcat(log_str,"	Time: ");
	strcat(log_str,__TIME__);
	strcat(log_str,"\n\rVersion: 1.0\n\r");
	strcat(log_str,"**************************************\n\r");
	log_string(Status, log_enable_f,log_str);
}

/* Disables the logger */
void log_disable(void)
{

	logger = log_off;
	log_string(Status, log_disable_f, "Logger disabled!");
}

/* Displays the status of the logger */
void log_status(void)
{
	//log_string("Log Status: ");
	if(logger == log_on)
	{
		log_string(Status, log_status_f, "Log on");
	}
	else
	{
		log_string(Status, log_status_f, "Log Off");
	}
}

/* display a string */
void log_string(log_level_e log_level, functions_e func, char *s)
{
	if (log_level >= current_log_level && logger == log_on)
	{
		format_time();
		char log_str[300];
		#if USE_UART_INTERRUPTS == 1
			sprintf(log_str, "[%s]%-8s%-35s %s\n\r", time_str, log_levels[log_level], functions[func], s);
			PrintStr_INT((uint8_t*)log_str);
		#else
			sprintf(log_str, "[%s]%-8s%-35s %s\n\r", time_str, log_levels[log_level], functions[func], s);
			PrintStr_Poll((uint8_t*)log_str);
		#endif
	}

}

/* display an integer */
void log_integer(log_level_e log_level, functions_e func, int x)
{

	if (log_level >= current_log_level && logger == log_on)
	{
		format_time();
		char log_str[200];
		#if USE_UART_INTERRUPTS == 1
			sprintf(log_str, "[%s]%-8s%-35s %d\n\r", time_str, log_levels[log_level], functions[func], x);
			PrintStr_INT((uint8_t*)log_str);
		#else
			sprintf(log_str, "[%s]%-8s%-35s %d\n\r", time_str, log_levels[log_level], functions[func], x);
			PrintStr_Poll((uint8_t*)log_str);
		#endif
	}

}

/*
 * Method for formating the time counter into a string.
 */
void format_time()
{
	if (!time_str)
	{
		time_str =  (char*) malloc(TIME_STR_SIZE* sizeof(char));
	}

	char hour_str[3];
	char minute_str[3];
	char second_str[3];
	char decisecond_str[2];

	uint32_t _intMask;
	_intMask = START_CRITICAL(); 								// disable interrupts
	uint32_t time_counter_temp = time_counter;
	END_CRITICAL(_intMask);										//re-enable the interrupts

    uint8_t hours = (uint8_t)(time_counter_temp / 36000);
    uint32_t remainder = time_counter_temp % 36000;
    uint8_t minutes = (uint8_t)(remainder / 600);
    remainder = remainder % 600;
    uint8_t seconds = (uint8_t)(remainder / 10);
    uint8_t deciseconds = (uint8_t)(remainder % 10);

    sprintf(hour_str, "%02d", hours);
    sprintf(minute_str, "%02d", minutes);
    sprintf(second_str, "%02d", seconds);
    sprintf(decisecond_str, "%d", deciseconds);

    strcpy(time_str, hour_str);
    strcat(time_str, ":");
    strcat(time_str, minute_str);
    strcat(time_str, ":");
    strcat(time_str, second_str);
    strcat(time_str, ".");
    strcat(time_str, decisecond_str);

}


