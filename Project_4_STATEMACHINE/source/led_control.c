/********************************************************************************
 * File name: "led_control.c"
 *
 * Description: Methods for handling initialization, setting, and clearing of the
 * Red, Blue, and Green LED on the KL25Z.
 *
 *
 * File​ ​ Author​ ​ Name: Disha Modi and Alexandra Paquin
 *
 * Tools​ ​ used​ ​ to​ ​ process​ ​ the​ ​ code​ ​ (compiler,​ ​ linker,​ ​ debugger):
 * 		NXP MCU Tools, Gnu Make Builder, Putty
 *
 * Identification​ ​ of​ ​ any​ ​ leveraged​ ​ code:
 * @ref: https://github.com/modi-disha/2020/blob/Disha/Project_2/Project_2/source/Project_2.c
 *
 * Applicable​ ​ Links: None
 *******************************************************************************/

#include "led_control.h"

/* Initializes the LED */
void LED_init(void)
{

	log_string(Status, LED_init_f, "Initializing LED");

	/* Define the init structure for the output LED pin*/
	LED_pin_config_t led_config = {
	            LED_DigitalOutput, 0,
	        };															// LED configuration structure

	LED_PinInit(BOARD_LED_RED, BOARD_LED_RED_PIN_MASK, &led_config);	//initialize red led
	LED_SetPinsOutput(BOARD_LED_RED, BOARD_LED_RED_PIN_MASK);
	LED_PinInit(BOARD_LED_GREEN, BOARD_LED_GREEN_PIN_MASK, &led_config); //initialize green led
	LED_SetPinsOutput(BOARD_LED_GREEN, BOARD_LED_GREEN_PIN_MASK);
	LED_PinInit(BOARD_LED_BLUE, BOARD_LED_BLUE_PIN_MASK, &led_config); //initialize blue led
	LED_SetPinsOutput(BOARD_LED_BLUE, BOARD_LED_BLUE_PIN_MASK);
}

// Turns the LED on
void LED_SetPinsOutput(GPIO_Type *base, uint32_t mask)
{
	log_string(Test, LED_SetPinsOutput_f, "Turning LED on");
    base->PSOR = mask;    //Port Set Output Register
}

// Turns the LED off
void LED_ClearPinsOutput(GPIO_Type *base, uint32_t mask)
{
	log_string(Test, LED_ClearPinsOutput_f, "Turning LED off");
    base->PCOR = mask;   //Port Clear Output Register
}

/* Initializes the LED */
void LED_PinInit(GPIO_Type *base, uint32_t pin_mask, const LED_pin_config_t *config)
{
    assert(config);

    if (config->pinDirection == LED_DigitalInput) // base = LED Port
    {
        base->PDDR &= ~(pin_mask);   //Port data direction Register
    }
    else
    {
    	if (config->outputLogic == 0U)
		{
			base->PCOR = pin_mask;   //Port Clear Output Register
		}
		else
		{
			base->PSOR = pin_mask;    //Port Set Output Register
		}
        base->PDDR |= (pin_mask);
    }
}

/* Turns off the LED */
void LED_SetAll(void)
{
	log_string(Debug, LED_SetAll_f, "Turning RGB LED off");
	LED_SetPinsOutput(BOARD_LED_RED, BOARD_LED_RED_PIN_MASK);
	LED_SetPinsOutput(BOARD_LED_GREEN, BOARD_LED_GREEN_PIN_MASK);
	LED_SetPinsOutput(BOARD_LED_BLUE, BOARD_LED_BLUE_PIN_MASK);
}

/* Turns on the red LED */
void LED_ClearRed(void)
{
	log_string(Debug, LED_ClearRed_f, "Turning Red LED on");
	LED_SetPinsOutput(BOARD_LED_GREEN, BOARD_LED_GREEN_PIN_MASK);
	LED_SetPinsOutput(BOARD_LED_BLUE, BOARD_LED_BLUE_PIN_MASK);
	LED_ClearPinsOutput(BOARD_LED_RED, 1u << BOARD_LED_RED_PIN);		// Turn red LED on
}

/* Turns on the green LED */
void LED_ClearGreen(void)
{
	log_string(Debug, LED_ClearGreen_f, "Turning Green LED on");
	LED_SetPinsOutput(BOARD_LED_RED, BOARD_LED_RED_PIN_MASK);
	LED_SetPinsOutput(BOARD_LED_BLUE, BOARD_LED_BLUE_PIN_MASK);
	LED_ClearPinsOutput(BOARD_LED_GREEN, 1u << BOARD_LED_GREEN_PIN);	// Turn green LED on
}

/* Turns on the blue LED */
void LED_ClearBlue(void)
{
	log_string(Debug, LED_ClearBlue_f, "Turning Blue LED on");
	LED_SetPinsOutput(BOARD_LED_RED, BOARD_LED_RED_PIN_MASK);
	LED_SetPinsOutput(BOARD_LED_GREEN, BOARD_LED_GREEN_PIN_MASK);
	LED_ClearPinsOutput(BOARD_LED_BLUE, 1u << BOARD_LED_BLUE_PIN);		// Turn blue LED on
}

