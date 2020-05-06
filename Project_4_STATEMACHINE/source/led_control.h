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
 * @file led_control.h
 * @brief An abstraction for handling initialization, setting, and clearing of the KL25Z LED.
 *
 * This header file provides an abstraction for handling initialization, setting, and clearing of the
 * Red, Blue, and Green LED on the KL25Z.
 *
 * @author Disha Modi and Alexandra Paquin
 * @date March 2020
 * @version 1.0
 *
 */


#ifndef LED_CONTROL_H_
#define LED_CONTROL_H_

#include "board.h"
#include "pin_mux.h"
#include "MKL25Z4.h"
#include "logger.h"

#define BOARD_LED_RED 				GPIOB
#define BOARD_LED_RED_PIN 			18U
#define BOARD_LED_RED_PIN_MASK 		(1U << BOARD_LED_RED_PIN)
#define BOARD_LED_GREEN 			GPIOB
#define BOARD_LED_GREEN_PIN 		19U
#define BOARD_LED_GREEN_PIN_MASK 	(1U << BOARD_LED_GREEN_PIN)
#define BOARD_LED_BLUE 				GPIOD
#define BOARD_LED_BLUE_PIN 			1U
#define BOARD_LED_BLUE_PIN_MASK 	(1U << BOARD_LED_BLUE_PIN)

/*
 * Enumerations
 */
typedef enum LED_pin_direction
{
    LED_DigitalInput = 0U,  /*!< Set current pin as digital input*/
    LED_DigitalOutput = 1U, /*!< Set current pin as digital output*/
} LED_pin_direction_t;



/*
 * Structs
 */
typedef struct LED_pin_config
{
    LED_pin_direction_t pinDirection; 	/*!< GPIO direction, input or output */
    /* Output configurations; ignore if configured as an input pin */
    uint8_t outputLogic; 				/*!< Set a default output logic, which has no use in input */
} LED_pin_config_t;


/**
 * @brief Initializes the LED
 *
 * Initializes the LED for the red, green, and blue colors. Additionally, initializes LED specific ports and pins as output.
 *
 * @param Void
 *
 * @return Void
 */
void LED_init(void);

/**
 * @brief Turns the LED on
 *
 * Clears the LED pin for specific specified port and pin.
 *
 * @param *base: pointer to port number
 * @param mask: bit mask for to specify the pin number
 *
 * @return Void
 */
void LED_SetPinsOutput(GPIO_Type *base, uint32_t mask);

/**
 * @brief Turns the LED off
 *
 * Sets the LED pin for specific specified port and pin.
 *
 * @param *base: pointer to port number
 * @param mask: bit mask for to specify the pin number
 *
 * @return Void
 */
void LED_ClearPinsOutput(GPIO_Type *base, uint32_t mask);


/**
 * @brief Initializes the LED
 *
 * Initializes the LED for the red, green, and blue colors. Additionally, initializes LED pin configuration as output and output directions.
 *
 * @param *base: pointer to port number
 * @param mask: bit mask for to specify the pin number
 * @param *config: Pointer to LED configuration structure
 * @return Void
 */
void LED_PinInit(GPIO_Type *base, uint32_t pin_mask, const LED_pin_config_t *config);

/**
 * @brief Turns off the LED
 *
 * Turns off the red, green, and blue LED colors
 *
 * @param Void
 *
 * @return Void
 */
void LED_SetAll(void);

/**
 * @brief Turns on the red LED
 *
 * Turns on the red LED
 *
 * @param Void
 *
 * @return Void
 */
void LED_ClearRed(void);

/**
 * @brief Turns on the green LED
 *
 * Turns on the green LED
 *
 * @param Void
 *
 * @return Void
 */
void LED_ClearGreen(void);

/**
 * @brief Turns on the blue LED
 *
 * Turns on the blue LED
 *
 * @param Void
 *
 * @return Void
 */
void LED_ClearBlue(void);

#endif /* LED_CONTROL_H_ */
