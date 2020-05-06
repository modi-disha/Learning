 /*****************************************************************************
 * File name: "main.c"
 *
 * Description: – Main program for PES project 5 combine the KL25Z with an
 * UART drivers (both polling and interrupt) using circular buffer. This setup implements
 * UART communication device drivers, circular buffers, and more on interrupts and timers.
 * Implements KL25Z USB port to send and receive data from a PC-based terminal program.
 * This project is targeted to run on the KL25Z only – the program is capable of
 * running in three modes
 * 1) In debug mode, with detailed debug messages.
 * 2) In normal mode, with normal status messages.
 * 3) In test mode, with detailed test messages.
 *
 * Program also runs several unit test cases by defining UCUNIT.
 *
 * File​ ​ Author​ ​ Name: Disha Modi and Alexandra Paquin
 *
 * Tools​ ​ used​ ​ to​ ​ process​ ​ the​ ​ code​ ​ (compiler,​ ​ linker,​ ​ debugger):
 * 		NXP MCU Tools, Gnu Make Builder, Putty
 *
 * Identification​ ​ of​ ​ any​ ​ leveraged​ ​ code:
 * @ref: https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code/Chapter_8/Serial-Demo/
 * @ref: https://embeddedartistry.com/blog/2017/05/17/creating-a-circular-buffer-in-c-and-c/
 *
 * Applicable​ ​ Links: None
 *******************************************************************************/

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "main.h"



/*
 * @brief Main Function: Application entry point.
 */
int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    LED_init();					// Initialize LED
    LED_ClearBlue();

#if USE_TEST_MODE == 0
    Init_UART0_Poll(115200);	// Initialize UART
#if USE_UART_INTERRUPTS == 1
    Init_UART0_INT();			// Initialize UART interrupt
#endif
#endif

    log_enable();		///enable the log
    log_level(Debug); 	///set the log level from test, debug or status

    SysTick_enable_interrupt();

#if USE_TEST_MODE == 1
    Run_Testcases();		//uCUnit test cases
#endif

#if USE_UART_INTERRUPTS == 1
    log_string(Status, main_f, "UART Interrupts Enabled, Polling Disabled");
    Char_INT();			//Echo Mode using interrupt UART: send any received characters back to the PC terminal program
#else
    log_string(Status, main_f, "UART Interrupts Disabled, Polling Enabled");
    Char_Poll();	//Echo Mode using polling UART: send any received characters back to the PC terminal program
#endif

    return 0 ;
}
