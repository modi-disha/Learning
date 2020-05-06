
/********************************************************************************
 * File name: "UART.c"
 *
 * Description: UART driver routines
 *
 * File​ ​ Author​ ​ Name: Disha Modi and Alexandra Paquin
 *
 * Tools​ ​ used​ ​ to​ ​ process​ ​ the​ ​ code​ ​ (compiler,​ ​ linker,​ ​ debugger):
 * 		NXP MCU Tools, Gnu Make Builder, Putty
 *
 * Identification​ ​ of​ ​ any​ ​ leveraged​ ​ code: https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code/Chapter_8/Serial-Demo/
 *
 * Applicable​ ​ Links: None
 *******************************************************************************/

#include "UART.h"
#include <stdio.h>

buffer_p txbuffer_p, rxbuffer_p;

/**
 * @brief Function for UART hardware initialization including baud rate and serial message format (parity, start/stop bits)
 */
void Init_UART0_Poll(uint32_t baud_rate)
{
	uint16_t sbr;
	uint8_t temp;

	// Enable clock gating for UART0 and Port A
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

	// Make sure transmitter and receiver are disabled before init
	UART0->C2 &= ~UART0_C2_TE_MASK & ~UART0_C2_RE_MASK;

	// Set UART clock to 48 MHz clock
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);
	SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;

	// Set pins to UART0 Rx and Tx
	PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Rx
	PORTA->PCR[2] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Tx

	// Set baud rate and oversampling ratio
	sbr = (uint16_t)((SYS_CLOCK)/(baud_rate * UART_OVERSAMPLE_RATE));
	UART0->BDH &= ~UART0_BDH_SBR_MASK;
	UART0->BDH |= UART0_BDH_SBR(sbr>>8);
	UART0->BDL = UART0_BDL_SBR(sbr);
	UART0->C4 |= UART0_C4_OSR(UART_OVERSAMPLE_RATE-1);

	// Disable interrupts for RX active edge and LIN break detect, select one stop bit
	UART0->BDH |= UART0_BDH_RXEDGIE(0) | UART0_BDH_SBNS(0) | UART0_BDH_LBKDIE(0);

	// Don't enable loopback mode, use 8 data bit mode, don't use parity
	UART0->C1 = UART0_C1_LOOPS(0) | UART0_C1_M(0) | UART0_C1_PE(0);
	// Don't invert transmit data, don't enable interrupts for errors
	UART0->C3 = UART0_C3_TXINV(0) | UART0_C3_ORIE(0)| UART0_C3_NEIE(0)
			| UART0_C3_FEIE(0) | UART0_C3_PEIE(0);

	// Clear error flags
	UART0->S1 = UART0_S1_OR(1) | UART0_S1_NF(1) | UART0_S1_FE(1) | UART0_S1_PF(1);

	// Try it a different way
	UART0->S1 |= UART0_S1_OR_MASK | UART0_S1_NF_MASK |
									UART0_S1_FE_MASK | UART0_S1_PF_MASK;

	// Send LSB first, do not invert received data
	UART0->S2 = UART0_S2_MSBF(0) | UART0_S2_RXINV(0);

	// Enable UART receiver and transmitter
	UART0->C2 |= UART0_C2_RE(1) | UART0_C2_TE(1);

	// Clear the UART RDRF flag
	temp = UART0->D;
	UART0->S1 &= ~UART0_S1_RDRF_MASK;
}

/**
 * @brief  Function for UART hardware initialization as above with addition of interrupt
 * configuration and enable (configure the KL25Z so the UART generates an interrupt when ready
 * to transmit a character, when a character has been received, or when there is an error)
 */
void Init_UART0_INT()
{
	errors_e buff1_status, buff2_status;

	if(!(txbuffer_p = (buffer_t *)malloc(sizeof(buffer_t))))		//tx buffer structure
		exit(0);
	if(!(rxbuffer_p = (buffer_t *)malloc(sizeof(buffer_t))))		//rx buffer structure
		exit(0);
	buff1_status = circular_buff_init(txbuffer_p, 100);			//create tx buffer of size 100
	buff2_status = circular_buff_init(rxbuffer_p, 100);			//create rx buffer of size 100

	if((buff1_status != Success) || (buff2_status != Success))
	{
		exit(0);	///malloc failed
	}
	NVIC_SetPriority(UART0_IRQn, 2); // 0, 1, 2, or 3
	NVIC_ClearPendingIRQ(UART0_IRQn);
	NVIC_EnableIRQ(UART0_IRQn);

	// Enable receive interrupts but not transmit interrupts yet
	UART0->C2 |= UART_C2_RIE(1);
}

/**
 * @brief Function to check whether the transmitter is available to accept a new character for transmission
 */
void UART0_Transmit_Poll(void)
{
	LED_ClearGreen();
	while (!(UART0->S1 & UART0_S1_TDRE_MASK));
}

/**
* @brief  Function to transmit a character assuming transmitter is available.
*/
void PutChar_Poll(uint8_t data)
{
	LED_ClearGreen();
	UART0->D = data;
}

/**
 * @brief  Function using these two functions to wait (block) for the transmitter to be available and then once available transmit a character and return
 * 		   wrapper to use UART0_Transmit_Poll & PutChar_Poll
 */
void PrintChar_Poll(uint8_t data)
{
	LED_ClearGreen();
	UART0_Transmit_Poll();
	PutChar_Poll(data);
}

/**
 * @brief  Function to check whether the receiver has a new character to receive
 */
void UART0_Receive_Poll(void)
{
	LED_ClearBlue();
	while (!(UART0->S1 & UART0_S1_RDRF_MASK));
}

/**
 * @brief  Function to receive the character assuming receiver has data
 */
uint8_t	GetChar_Poll(void)
{
	LED_ClearBlue();
	return UART0->D;
}

/**
 * @brief Function using these two functions to wait (block) for the receiver to receive a new character and then return that character
 * Wrapper to use UART0_Receive_Poll & GetChar_Poll
 */
uint8_t ScanChar_Poll(void)
{
	UART0_Receive_Poll();
	return GetChar_Poll();
}

// UART0 IRQ Handler.
void UART0_IRQHandler(void)
{
	if(UART0_Error_INT())		//check error interrupt flag
	{
		ClearErrFlags();		//clear flags
	}
	if (UART0_Receive_INT())	//check receive character interrupt flag
	{
		GetChar_INT();			//receive the character
	}
	if (UART0_Transmit_INT())	//check transmit character interrupt flag
	{
		PutChar_INT();			//transmit the character
	}
}

/**
 * @brief  Function to check whether the transmitter is available to accept a new character for transmission
 */
bool UART0_Transmit_INT(void)
{
	LED_ClearGreen();
	if((UART0->C2 & UART0_C2_TIE_MASK) && // transmitter interrupt enabled
			(UART0->S1 & UART0_S1_TDRE_MASK))		//// tx buffer empty
		return 1;
	else
		return 0;
}

/**
 * @brief  Function to transmit a character assuming transmitter is available
 */
void PutChar_INT(void)
{
	LED_ClearGreen();
	if (!circular_buff_empty(txbuffer_p)) {
		uint8_t data;
		UART0->D = data;
		circular_buff_dequeue(txbuffer_p, &data);
	} else {
		// queue is empty so disable transmitter interrupt
		UART0->C2 &= ~UART0_C2_TIE_MASK;
	}
}

/**
 * @brief  Function to check whether the receiver is available to accept a new character to receive
 */
bool UART0_Receive_INT(void)
{
	LED_ClearBlue();
	if (UART0->S1 & UART0_S1_RDRF_MASK)
		return 1;
	else
		return 0;
}

/**
 * @brief  Function called by the ISR for receiving a character
 * (i.e. on the IRQ, verify a character was received and read it from the data register)
 */
void GetChar_INT(void)
{
	circular_buff_enqueue(rxbuffer_p, UART0->D);
}

/**
 * @brief  Function to check UART error interrupt flags
 */
bool UART0_Error_INT(void)
{
	if (UART0->S1 & (UART_S1_OR_MASK |UART_S1_NF_MASK |	UART_S1_FE_MASK | UART_S1_PF_MASK))
		return 1;
	else
		return 0;
}

/**
 * @brief  Function to clear UART error interrupt flags
 */
void ClearErrFlags(void)
{
	LED_ClearRed();
	// clear the error flags
	UART0->S1 |= UART0_S1_OR_MASK | UART0_S1_NF_MASK | UART0_S1_FE_MASK | UART0_S1_PF_MASK;
	// read the data register to clear RDRF
	uint8_t ch = UART0->D;
}

/**
 * @brief An printstr function that prints the string to the PC-based terminal
 */
void PrintStr_Poll(uint8_t *str)
{
	while (*str != '\0') { // Send characters up to null terminator
		UART0_Transmit_Poll();
		PutChar_Poll(*str++);

	}
}

/**
 * @brief An printstr function that prints the string to the PC-based terminal
 */
void PrintStr_INT(uint8_t *str)
{
	// enqueue string
	while (*str != '\0')
	{ 							// copy characters up to null terminator
		while (circular_buff_full(txbuffer_p));	// wait for space to open up
		circular_buff_enqueue(txbuffer_p, *str);
		// start transmitter if it isn't already running
		if (!(UART0->C2 & UART0_C2_TIE_MASK))
		{
			UART0->D = *str;
			UART0->C2 |= UART0_C2_TIE(1);
		}
		str++;
	}
}

/**
 * @brief An echo function that uses the get and put functions to echo received characters one at a time back to the PC-based sender
 */
void Char_Poll(void)
{
	uint8_t ch;
	log_string(Status, Char_Poll_f,"Enter in characters and press enter to see report:");
	while(1)
	{
		ch = ScanChar_Poll();

		#if USE_ECHO_MODE
		PrintChar_Poll(ch);		//Receive the character and send it back
		#endif
		#if APPLICATION == 1

			update_char_count(ch);

			if (ch == 0xD)
			{
				char *report = get_report();
				log_string(Status, Char_Poll_f,"Character Report:");
				while (*report != '\0')
				{
					PrintChar_Poll(*(report++));
				}
				log_string(Status, Char_Poll_f,"Enter in characters and press enter to see report:");
			}

		#endif
	}
}

/**
 * @brief An echo function that uses the get and put functions to echo received characters one at a time back to the PC-based sender
 */
void Char_INT(void)
{
	uint8_t ch;
	log_string(Status, Char_INT_f,"Enter in characters and press enter to see report:");
	while(1)
	{
		while(circular_buff_size(rxbuffer_p) == 0);
		if(circular_buff_dequeue(rxbuffer_p, &ch) == Success)			//Receive the character
		{
			if(ch != '\0')
			{
				circular_buff_enqueue(txbuffer_p, ch);

				#if USE_ECHO_MODE == 1
				// start transmitter if it isn't already running
				if (!(UART0->C2 & UART0_C2_TIE_MASK))
				{
					UART0->D = ch;										//Send the same character back
					UART0->C2 |= UART0_C2_TIE(1);
				}
				#endif
				#if APPLICATION == 1

					update_char_count(ch);

					if (ch == 0xD)
					{
						char *report = get_report();
						log_string(Status, Char_INT_f,"Character Report:");
						while (*report != '\0')
						{
							// start transmitter if it isn't already running
							if (!(UART0->C2 & UART0_C2_TIE_MASK))
							{
								UART0->D = *(report++);
								UART0->C2 |= UART0_C2_TIE(1);
							}
						}
						log_string(Status, Char_INT_f,"Enter in characters and press enter to see report:");
					}

				#endif
			}
		}
	}
}

