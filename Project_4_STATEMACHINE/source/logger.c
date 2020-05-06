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

log_e logger = log_off;

log_level_e current_log_level = Test;

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
	printf("Logger enabled!\n\r");
	printf("**************************************\n\r");
	printf("Name: ");
	printf("PES Project#4\n\r");
	printf("Compiled: ");
	printf(__DATE__);
	printf("	Time: ");
	printf(__TIME__);
	printf("\n\rVersion: 1.0\n\r");
	printf("**************************************\n\r");
}

/* Disables the logger */
void log_disable(void)
{

	logger = log_off;
	printf("Logger disabled!\n\r");
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
		printf("%-8s%-29s %s\n\r", log_levels[log_level], functions[func], s);
	}

}

/* display an integer */
void log_integer(log_level_e log_level, functions_e func, int x)
{

	if (log_level >= current_log_level && logger == log_on)
	{
		printf("%-8s%-29s %d\n\r", log_levels[log_level], functions[func], x);
	}

}

/* displays the accel XYZ readings */
void log_accel(int16_t x_accel, int16_t y_accel, int16_t z_accel,
		int16_t ax, int16_t ay, int16_t az,
		int16_t minx, int16_t miny, int16_t minz,
		int16_t maxx, int16_t maxy, int16_t maxz)
{
	log_string(Status, display_accel_f,"Accelerometer Readings:");
	printf("%30s         |     x      |     y      |     z       \n\r", "");
	printf("%30s ------------------------------------------------\n\r" , "");
	printf("%30s Current | %10d | %10d | %10d\n\r", "", x_accel, y_accel, z_accel);
	printf("%30s Average | %10d | %10d | %10d\n\r", "", ax, ay, az);
	printf("%30s     Low | %10d | %10d | %10d\n\r", "", minx, miny, minz);
	printf("%30s    High | %10d | %10d | %10d\n\r", "", maxx, maxy, maxz);
}
