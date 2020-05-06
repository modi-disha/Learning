
/********************************************************************************
 * File name: "loopback.c"
 *
 * Description: SPI driver routines
 *
 * File​ ​ Author​ ​ Name: Disha Modi and Alexandra Paquin
 *
 * Tools​ ​ used​ ​ to​ ​ process​ ​ the​ ​ code​ ​ (compiler,​ ​ linker,​ ​ debugger):
 * 		NXP MCU Tools, Gnu Make Builder, Putty
 *
 * Identification​ ​ of​ ​ any​ ​ leveraged​ ​ code: https://github.com/alexander-g-dean/ESF/blob/master/Code/Chapter_8/SPI-Demo/src/spi.c
 *
 * Applicable​ ​ Links: None
 *******************************************************************************/

#include "main.h"
#include "SPI.h"

volatile uint8_t spi_sent, spi_received;

// Internal SPI master and SPI slave, master echos the command to slave
state_e Loopback(void)
{
	static uint8_t send = 0;

	spi_sent = ++send;

	spi_received = spi_loopback(spi_sent);

	if (spi_received != spi_sent)
	{
		log_string(Status, Loopback_f, "SPI Loopback disconnected");
		event = Disconnected;
		return Disconnect;
	}

	event = Complete;
	return Process_Loopback;
}

//Displays the echoed instruction,status
state_e Display_Loopback_Result(void)
{

	uint8_t count = (int8_t)read_state3_count();

	char message1[40];
	char message2[2];
	strcpy(message1, "Current Timeout Count: ");
	itoa((count - 1), message2, 10);
	strcat(message1, message2);

	log_string(Status, Display_Loopback_Result_f, message1);

	char message3[40];
	char message4[2];
	char message5[2];
	strcpy(message3, "Sent ");
	itoa(spi_sent, message4, 10);
	strcat(message3, message4);
	strcat(message3, " and received ");
	itoa(spi_received, message5, 10);
	strcat(message3, message5);
	strcat(message3, " with SPI Loopback.");

	log_string(Status, Display_Loopback_Result_f, message3);

	event = Complete;
	return Poll_Slider;
}
