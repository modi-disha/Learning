
/********************************************************************************
 * File name: "SPI.c"
 *
 * Description: SPI driver routines
 *
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

#include "SPI.h"

//SPI initialization routine
void SPI_init(void)
{

	// Enable clock to SPI0
	SIM->SCGC4 |= SIM_SCGC4_SPI1_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;

	// disable SPI0 to allow configuration
	SPI1->C1 &= ~SPI_C1_SPE_MASK;

	// Set PTE2 as SPI1_SCK -- ALT2
	PORTE->PCR[2] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[2] |= PORT_PCR_MUX(2);

	// Set PTE3 as SPI1_MOSI -- ALT5
	PORTE->PCR[3] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[3] |= PORT_PCR_MUX(5);

	// Set PTE1 as SPI1_MISO -- ALT5
	PORTE->PCR[1] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[1] |= PORT_PCR_MUX(5);

	// Set PTE4 as SPI1_PCS0 -- ALT2
	PORTE->PCR[4] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[4] |= PORT_PCR_MUX(2);

	// Select master mode, enable SS output
	SPI1->C1 = SPI_C1_MSTR_MASK | SPI_C1_SSOE_MASK;
	SPI1->C2 = SPI_C2_MODFEN_MASK;

	// Select active high clock, first edge sample
	SPI1->C1 &= ~SPI_C1_CPHA_MASK;
	SPI1->C1 &= ~SPI_C1_CPOL_MASK;

	// Baudrate = BusClock / ((SPPR+1)*2^(SPR+1))
	SPI1->BR = SPI_BR_SPPR(1) | SPI_BR_SPR(3);

	// Enable SPI0
	SPI1->C1 |= SPI_C1_SPE_MASK;

}

//SPI loopback routine, echo routine
uint8_t spi_loopback(uint8_t byte){

	while (!(SPI1->S & SPI_S_SPTEF_MASK))
		;
	SPI1->D = byte;

	while(!(SPI1->S & SPI_S_SPRF_MASK))
		;

	return SPI1->D;

}

