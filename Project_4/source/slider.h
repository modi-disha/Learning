/*
 * slider.h
 *
 *  Created on: Mar 19, 2020
 *      Author: Disha
 */

#ifndef SLIDER_H_
#define SLIDER_H_
#include <MKL25Z4.h>

#define SCAN_DATA TSI0->DATA & 0xFFFF 		// Accessing the bits held in TSI0_DATA_TSICNT
#define BOARD_TOUCH_PORT TSI0
#define BOARD_LED_RED GPIOB
#define BOARD_LED_RED_PIN 18U
#define BOARD_LED_RED_PIN_MASK (1U << BOARD_LED_RED_PIN)
#define BOARD_LED_GREEN GPIOB
#define BOARD_LED_GREEN_PIN 19U
#define BOARD_LED_GREEN_PIN_MASK (1U << BOARD_LED_GREEN_PIN)
#define BOARD_LED_BLUE GPIOD
#define BOARD_LED_BLUE_PIN 1U
#define BOARD_LED_BLUE_PIN_MASK (1U << BOARD_LED_BLUE_PIN)

/*
 * Enumerations
 */

typedef enum LED { RED, GREEN, BLUE } color;


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

void LED_SetPinsOutput(GPIO_Type *base, uint32_t mask);
void LED_ClearPinsOutput(GPIO_Type *base, uint32_t mask);
void LED_PinInit(GPIO_Type *base, uint32_t pin_mask, const LED_pin_config_t *config);
void TOUCH_init(TSI_Type *base);
uint16_t TOUCH_Calibrate(TSI_Type *base);

/**
 * @brief Initializes the LED
 *
 * Initializes the LED for the red, green, and blue colors. Additionally, initializes
 * the LED to output no color.
 *
 * @param None
 *
 * @return Non
 */
void LED_init(void);

#endif /* SLIDER_H_ */
