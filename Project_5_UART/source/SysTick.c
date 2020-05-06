
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

int time_counter = 0;

//SysTick timer interrupt enable routine
void SysTick_enable_interrupt(void)
{
	log_string(Debug, SysTick_enable_interrupt_f, "Enabling SysTick 0.1s Interrupt");

	SysTick->LOAD = ((4800000L/16));				// Set reload to get .1s interrupts
	SysTick->VAL = 0;								// Force load of reload value
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk		// Enable interrupt, alt.clock source
						| SysTick_CTRL_ENABLE_Msk;	// Enable SysTick timer
}

//SysTick timer interrupt disable routine
void SysTick_disable_interrupt(void)
{
	log_string(Debug, SysTick_disable_interrupt_f, "Disabling SysTick Interrupt");

	SysTick->CTRL &= ~(SysTick_CTRL_TICKINT_Msk		// Disable interrupt, alt.clock source
						| SysTick_CTRL_ENABLE_Msk); // Disable SysTick timer
}

//SysTick timer interrupt service routine
void SysTick_Handler(void)
{
	time_counter++;

}

