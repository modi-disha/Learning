
/********************************************************************************
 * File name: "SysTick.c"
 *
 * Description: SysTick interrupt routines
 *
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

#include "SysTick.h"

timeout_e timeout_reached = NO_TIMEOUT;

//SysTick timer interrupt enable routine
void SysTick_enable_interrupt(void)
{
	log_string(Debug, SysTick_enable_interrupt_f, "Enabling SysTick 3s Interrupt");

	timeout_reached = PENDING_TIMEOUT;
	SysTick->LOAD = ((48000000L/16)*3);				// Set reload to get 3s interrupts
	SysTick->VAL = 0;								// Force load of reload value
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk		// Enable interrupt, alt.clock source
						| SysTick_CTRL_ENABLE_Msk;	// Enable SysTick timer
}

//SysTick timer interrupt disable routine
void SysTick_disable_interrupt(void)
{
	log_string(Debug, SysTick_disable_interrupt_f, "Disabling SysTick Interrupt");

	timeout_reached = NO_TIMEOUT;
	SysTick->CTRL &= ~(SysTick_CTRL_TICKINT_Msk		// Disable interrupt, alt.clock source
						| SysTick_CTRL_ENABLE_Msk); // Disable SysTick timer
}

//SysTick timer interrupt service routine
void SysTick_Handler(void)
{
	timeout_reached = TIMEOUT;

}

