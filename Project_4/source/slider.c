/*
 * slider.c
 *
 *  Created on: Mar 19, 2020
 *      Author: Disha
 */
#include "slider.h"

/* Initializes the LED */
void LED_init(void)
{
	/* Define the init structure for the output LED pin*/
	LED_pin_config_t led_config = {
	            LED_DigitalOutput, 0,
	        };

	LED_PinInit(BOARD_LED_RED, BOARD_LED_RED_PIN_MASK, &led_config);
	LED_SetPinsOutput(BOARD_LED_RED, BOARD_LED_RED_PIN_MASK);
	LED_PinInit(BOARD_LED_GREEN, BOARD_LED_GREEN_PIN_MASK, &led_config);
	LED_SetPinsOutput(BOARD_LED_GREEN, BOARD_LED_GREEN_PIN_MASK);
	LED_PinInit(BOARD_LED_BLUE, BOARD_LED_BLUE_PIN_MASK, &led_config);
	LED_SetPinsOutput(BOARD_LED_BLUE, BOARD_LED_BLUE_PIN_MASK);
}

/* @ref: https://www.digikey.com/eewiki/display/microcontroller/Using+the+Capacitive+Touch+Sensor+on+the+FRDM-KL46Z" */
void TOUCH_init(TSI_Type *base)
{
	SIM->SCGC5 |= SIM_SCGC5_TSI_MASK; //System clock gating control resistor

	/*! @brief GENCS - TSI General Control and Status Register */
	base->GENCS =
	TSI_TSHD_THRESL(0) |
	TSI_TSHD_THRESH(0) |
	TSI_GENCS_PS(0u) | 				// 0-7 for electrode pre-scaler
	TSI_GENCS_EXTCHRG(0u) | 		// 0-7 for External charge
	TSI_GENCS_REFCHRG(0u) | 		// 0-7 for Reference charge
	TSI_GENCS_NSCN(31u) | 			// 0-31 + 1 for number of scans per electrode
	TSI_GENCS_MODE(0u) |  			// Set at 0 for capacitive sensing.  Other settings are 4 and 8 for threshold detection, and 12 for noise detection
	TSI_GENCS_DVOLT(0u) | 			// 0-3 sets the Voltage range
	TSI_GENCS_TSIEN_MASK | 			// TSI enable bit
	TSI_GENCS_STPE_MASK | 			// Enables TSI in low power mode
	TSI_GENCS_OUTRGF_MASK |  		// Out of range flag, set to 1 to clear
	TSI_GENCS_EOSF_MASK ; 			// End of scan flag, set to 1 to clear
}

uint16_t TOUCH_Calibrate(TSI_Type *base)
{
	uint16_t calibratedData = 0;
	base->DATA = ((base->DATA) & ~TSI_DATA_TSICH_MASK) | (TSI_DATA_TSICH(10u)); // Using channel 10 of The TSI
	base->DATA |= TSI_DATA_SWTS_MASK; 											// Software trigger for scan
	while (!(base->GENCS & TSI_GENCS_EOSF_MASK))
	{
	}
	calibratedData = (uint16_t)(base->DATA & TSI_DATA_TSICNT_MASK);
	base->GENCS |= TSI_GENCS_EOSF_MASK ; 										// Reset end of scan flag
//        DELAY_itr(BOARD_delay[2]);
	return calibratedData;
}

void LED_SetPinsOutput(GPIO_Type *base, uint32_t mask)
{
    base->PSOR = mask;
}

void LED_ClearPinsOutput(GPIO_Type *base, uint32_t mask)
{
    base->PCOR = mask;
}

/* Initializes the LED */
void LED_PinInit(GPIO_Type *base, uint32_t pin_mask, const LED_pin_config_t *config)
{
    if (config->pinDirection == LED_DigitalInput)
    {
        base->PDDR &= ~(pin_mask);
    }
    else
    {
    	if (config->outputLogic == 0U)
		{
			base->PCOR = pin_mask;
		}
		else
		{
			base->PSOR = pin_mask;
		}
        base->PDDR |= (pin_mask);
    }
}
