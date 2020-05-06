
/********************************************************************************
 * File name: "slider.c"
 *
 * Description: Touch Slider driver routines
 *
 * File​ ​ Author​ ​ Name: Disha Modi and Alexandra Paquin
 *
 * Tools​ ​ used​ ​ to​ ​ process​ ​ the​ ​ code​ ​ (compiler,​ ​ linker,​ ​ debugger):
 * 		NXP MCU Tools, Gnu Make Builder, Putty
 *
 * Identification​ ​ of​ ​ any​ ​ leveraged​ ​ code: https://www.digikey.com/eewiki/display/microcontroller/Using+the+Capacitive+Touch+Sensor+on+the+FRDM-KL46Z"
 *
 * Applicable​ ​ Links: None
 *******************************************************************************/
#include "slider.h"

// Touch Slider initialization routine
void TOUCH_init(TSI_Type *base)
{
	log_string(Status, TOUCH_init_f, "Initializing Capacitive Touch Sensor");

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

// Touch Slider Calibration routine
uint16_t TOUCH_Calibrate(TSI_Type *base)
{
	log_string(Status, TOUCH_Calibrate_f, "Polling Capacitive Touch Sensor");

	// Enable SysTick interrupt
	SysTick_enable_interrupt();

	// Set slider value as untouched initially
	uint16_t calibratedData = SLIDER_NONE_MIN;


	base->DATA = ((base->DATA) & ~TSI_DATA_TSICH_MASK) | (TSI_DATA_TSICH(10u)); // Using channel 10 of The TSI
	base->DATA |= TSI_DATA_SWTS_MASK; // Software trigger for scan

	// Continues looping when slider is not being touched
	while (calibratedData < SLIDER_RIGHT_MIN)
	{
		// If sampling is done
		if ((base->GENCS & TSI_GENCS_EOSF_MASK))
		{
			// Check if we have reached the 3 second timeout
			if (timeout_reached == TIMEOUT)
			{

				calibratedData = SLIDER_NONE_MIN; // setup to return an untouched slider value
				break;
			}
		}

		// Get the slider value
		calibratedData = (uint16_t)(base->DATA & TSI_DATA_TSICNT_MASK);
	}

	// Disable SysTick interrupt
	SysTick_disable_interrupt();

	// Reset end of scan flag
	base->GENCS |= TSI_GENCS_EOSF_MASK ;

	return calibratedData;
}
