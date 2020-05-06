
/*****************************************************************************
 * Copyright (C) 2020 by Disha Modi and Alexandra Paquin
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Disha Modi, Alexandra Paquin, and the University of Colorado are not
 * liable for any misuse of this material.
 *
******************************************************************************/
/**
 * @file UART.h
 * @brief An abstraction for UART drivers.
 *
 * This header file provides an abstraction for UART driver routines.
 *
 * @author Disha Modi and Alexandra Paquin
 * @date April 2020
 * @version 1.0
 *
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include <MKL25Z4.H>
#include <stdio.h>
#include "queue.h"
#include "main.h"
#include "application.h"
#include "led_control.h"
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#define UART_OVERSAMPLE_RATE 	(16)
#define BUS_CLOCK 				(24e6)
#define SYS_CLOCK				(48e6)

/********************************************************************************/
/*						UART Device Driver 1 – Blocking/Polled					*/
/********************************************************************************/

/**
 * @brief Function for UART hardware initialization including baud rate and serial message format (parity, start/stop bits)
 *
 * @param uint32_t baud_rate, defines baud rate of serial communication
 *
 * @return void
 */
void Init_UART0_Poll(uint32_t baud_rate);

/**
 * @brief Function to check whether the transmitter is available to accept a new character for transmission
 *
 * @param void
 *
 * @return void
 */
void UART0_Transmit_Poll(void);


/**
* @brief  Function to transmit a character assuming transmitter is available.
*
* @param uint8_t data, tx character
*
* @return void
*/
void PutChar_Poll(uint8_t data);


/**
 * @brief  Function using these two functions to wait (block) for the transmitter to be available and then
 * once available transmit a character and return wrapper to use UART0_Transmit_Poll & PutChar_Poll
 *
 * @param uint8_t data, tx character
 *
 * @return void
 */
void PrintChar_Poll(uint8_t data);

 /**
  * @brief  Function to check whether the receiver has a new character to receive
  *
  * @param void
  *
  * @return void
  */
void UART0_Receive_Poll(void);

 /**
  * @brief  Function to receive the character assuming receiver has data
  *
  * @param void
  *
  * @return uint8_t, rx character
  */
uint8_t	GetChar_Poll(void);

 /**
  * @brief Function using these two functions to wait (block) for the receiver to receive a new character
  * and then return that character Wrapper to use UART0_Receive_Poll & GetChar_Poll
  *
  * @param void
  *
  * @return uint8_t, rx character
  */
uint8_t ScanChar_Poll(void);

 /**
  * @brief An echo function that uses the get and put functions to echo received characters one at a time
  * back to the PC-based sender
  *
  * @param void
  *
  * @return void
  */
void Char_Poll(void);

/**
 * @brief An printstr function that prints the string to the PC-based terminal
 *
 * @param uint8_t *str, tx string
 *
 * @return void
 */
void PrintStr_Poll(uint8_t *str);


/********************************************************************************/
/*					UART Device Driver 2 – Non-blocking/Interrupt				*/
/********************************************************************************/

 /**
  * @brief  Function for UART hardware initialization as above with addition of interrupt
  * configuration and enable (configure the KL25Z so the UART generates an interrupt when ready
  * to transmit a character, when a character has been received, or when there is an error)
  *
  * @param void
  *
  * @return void
  */
void Init_UART0_INT(void);

/**
 * @brief  Function to check whether the transmitter is available to accept a new character for transmission
 *
 * @param void
 *
 * @return bool, tx interrupt flag status
 */
bool UART0_Transmit_INT(void);

 /**
  * @brief  Function to transmit a character assuming transmitter is available
  *
  * @param void
  *
  * @return void
  */
void PutChar_INT(void);

/**
 * @brief  Function to check whether the receiver is available to accept a new character to receive
 *
 * @param void
 *
 * @return bool, rx interrupt flag status
 */
bool UART0_Receive_INT(void);

 /**
  * @brief  Function called by the ISR for receiving a character
  * (i.e. on the IRQ, verify a character was received and read it from the data register)
  *
  * @param void
  *
  * @return void
  */
void GetChar_INT(void);

/**
 * @brief  Function to check UART error interrupt flags
 *
 * @param void
 *
 * @return bool, error interrupt flag status
 */
bool UART0_Error_INT(void);

/**
 * @brief  Function to clear UART error interrupt flags
 *
 * @param void
 *
 * @return void
 */
void ClearErrFlags(void);

/**
 * @brief An echo function that uses the get and put functions to echo received characters
 * one at a time back to the PC-based sender
 *
 * @param void
 *
 * @return void
 */
void Char_INT(void);

/**
 * @brief An printstr function that prints the string to the PC-based terminal
 *
 * @param uint8_t *str, tx string
 *
 * @return void
 */
void PrintStr_INT(uint8_t *str);


#endif /* UART_H_ */
