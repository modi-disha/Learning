 /*****************************************************************************
 * File name: "main.c"
 *
 * Description: – Main program for PES project 4 combine the KL25Z with an
 * I2C-based Accelerometer board, the MMA8451Q. This setup implements
 * state machines, interrupts, timers, I2C communications, and SPI communication.
 * This project is targeted to run on the KL25Z only – the program is capable of
 * running in three modes
 * 1) In debug mode, with detailed debug messages logged to the UART.
 * 2) In normal mode, with normal status messages logged to the UART.
 * 3) In test mode, with detailed test messages logged to the UART.
 *
 * Program also runs several unit test cases by defining UCUNIT.
 * At the start of the program, it first checks accelerometer using a POST (Power-On Startup Test).
 *
 * File​ ​ Author​ ​ Name: Disha Modi and Alexandra Paquin
 *
 * Tools​ ​ used​ ​ to​ ​ process​ ​ the​ ​ code​ ​ (compiler,​ ​ linker,​ ​ debugger):
 * 		NXP MCU Tools, Gnu Make Builder, Putty
 *
 * Identification​ ​ of​ ​ any​ ​ leveraged​ ​ code:
 * @ref: https://www.nxp.com/docs/en/reference-manual/KL25P80M48SF0RM.pdf
 * @ref: https://github.com/alexander-g-dean/ESF/tree/master/Code/Chapter_8/I2C-Demo
 * @ref: https://community.nxp.com/thread/319111
 * @ref: https://www.embedded.com/implementing-finite-state-machines-in-embedded-systems/
 *
 * Applicable​ ​ Links: None
 *******************************************************************************/

#include <stdio.h>


#include "main.h"

#define UCUNIT 0

/*******************************************************************************
 * Definitions
 ******************************************************************************/
static uint8_t s1_entrycount, s2_entrycount, s3_entrycount;
static flag_e flag_s1, flag_s2, flag_s3;
state_e next_state;

event_e event = Pass;

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */
int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    log_enable();		///enable the log
    log_level(Status); 	///set the log level from test, debug or status

    LED_init();						// Initialize LED
    SPI_init();			///initialize SPI
    I2C_init();			///initialize I2C
    if(!ACC_init())		///initialize Accelerometer
    {
		log_string(Status, ACC_init_f,"Accelerometer Initialization failed!");
		end_state();
    }

	TOUCH_init(BOARD_TOUCH_PORT);	// Initialize capacitive touch sensor

	///Flags to handle the state machines
	flag_s1 = FLAG_HIGH;
	flag_s2 = FLAG_LOW;
	flag_s3 = FLAG_LOW;

	///Function pointer for table-driven state machine
	state_e (*state_table[MAX_STATES][MAX_EVENTS]) (void) = {
		/*	  Pass 					Fail			Complete 				Disconnected			Timeout					Left_slider				Right_slider  */
			{ Read_XYZ_Acc_Handler, Error_Handler, 	Error_Handler, 			Error_Handler, 			Read_XYZ_Acc_Handler, 	Read_XYZ_Acc_Handler, 	Error_Handler}, // Read_XYZ_Acc
			{ Error_Handler, 		Error_Handler, 	Process_Acc_Handler, 	Error_Handler, 			Error_Handler, 			Error_Handler, 			Error_Handler},	// Process_Acc
			{ Error_Handler, 		Error_Handler, 	Poll_Slider_Handler, 	Error_Handler, 			Error_Handler, 			Error_Handler, 			Error_Handler},	// Poll_Slider
			{ Error_Handler, 		Error_Handler,	Error_Handler, 			Acc_Disconnect_Handler, Error_Handler, 			Error_Handler, 			Error_Handler},	// Acc_Disconnect
			{ Error_Handler, 		Error_Handler, 	Error_Handler, 			Error_Handler, 			Error_Handler, 			Error_Handler,			Error_Handler}  // Error
	};

    event_e current_event;
    state_e current_state;
    s1_entrycount = 0, s2_entrycount = 0, s3_entrycount = 0;

    LED_ClearBlue();
    next_state = POST_Test_Handler();		///POST test

    if (next_state != Error) LED_ClearGreen();
    else LED_ClearRed();

#if UCUNIT == 1

    Run_Testcases();	///UCUINT unit test-cases routine

#endif


    log_string(Status, main_f,"Entering State Machine 1");

    while(1)
    {
    	/// State Machine 1 - I2C drivers uses Polling method
		if(flag_s1)
		{
			current_event = event;
			current_state = next_state;

			if((current_event == Fail) || (current_event == Right_slider))
			{
				end_state();		/// in case of error End the program
			}

			switch(current_state)
			{
				case(Read_XYZ_Acc):
					s1_entrycount++;
					if((current_event == Pass) || (current_event == Timeout) || (current_event == Left_slider)) {
						next_state = Read_XYZ_Acc_Handler(); }
					else {
						next_state = Error;	}
					break;
				case(Process_Acc):
					if(current_event == Complete)	{
						next_state = Process_Acc_Handler(); }
					else {
						next_state = Error;	}
					break;
				case(Poll_Slider):
					if(current_event == Complete)	{
						next_state = Poll_Slider_Handler(); }
					else {
						next_state = Error;	}
					break;
				case(Disconnect):
					if(current_event == Disconnected)	{
						next_state = Acc_Disconnect_Handler(); }
					else {
						next_state = Error;	}
					break;
				case(Error):
					Error_Handler();
					break;
				default:
					next_state = Error;
					break;
			}

		}

		/// State Machine 2 - I2C drivers uses Interrupt method
		if(flag_s2)
		{
			current_event = event;
			current_state = next_state;

			if(current_state == Read_XYZ_Acc)
			{
				s2_entrycount++;
			}

			if((current_event >= 0) && (current_event < MAX_EVENTS))
			{
				next_state = state_table[current_state][current_event]();
			}
		}

		/// State Machine 3 - SPI drivers
		if(flag_s3)
		{
			current_event = event;
			current_state = next_state;

			if((current_event == Fail) || (current_event == Right_slider))
			{
				end_state();
			}

			switch(current_state)
			{
				case(SPI_Loopback):
					s3_entrycount++;
					if((current_event == Pass) || (current_event == Timeout) || (current_event == Left_slider)) {
						next_state = Loopback(); }
					else {
						next_state = Error;	}
					break;
				case(Process_Loopback):
					if(current_event == Complete)	{
						next_state = Display_Loopback_Result(); }
					else {
						next_state = Error;	}
					break;
				case(Poll_Slider):
					if(current_event == Complete)	{
						next_state = Poll_Slider_Handler(); }
					else {
						next_state = Error;	}
					break;
				case(Disconnect):
					if(current_event == Disconnected)	{
						next_state = Acc_Disconnect_Handler(); }
					else {
						next_state = Error;	}
					break;
				case(Error):
					Error_Handler();
					break;
				default:
					next_state = Error;
					break;
			}

		}
    }
    return 0;
}

/*
 * @brief   Ends the program
 */
void end_state(void)
{
	log_string(Status, end_state_f,"Program Ended!");
	exit(1);
}

/*
 * @brief  Read the entry count of State machine 3
 */
uint8_t read_state1_count(void)
{
	return s1_entrycount;
}

/*
 * @brief Reset the entry count of State machine 1
 */
void reset_state1_count(void)
{
	s1_entrycount = 0;
}

/*
 * @brief  Reads the entry count of State machine 2
 */
uint8_t read_state2_count(void)
{
	return s2_entrycount;
}

/*
 * @brief  Reset the entry count of State machine 2
 */
void reset_state2_count(void)
{
	s2_entrycount = 0;
}

/*
 * @brief Reads the entry count of State machine 3
 */
uint8_t read_state3_count(void)
{
	return s3_entrycount;
}

/*
 * @brief  Reset the entry count of State machine 3
 */
void reset_state3_count(void)
{
	s3_entrycount = 0;
}

/*
 * @brief Call the routine to End the program in case of error
 */
state_e Error_Handler(void)
{
	end_state();
	return Error;
}

/*
 * @brief  Changes to the next state machine
 */
void change_state(void)
{
	if(flag_s1 == FLAG_HIGH)
	{
		flag_s1 = FLAG_LOW;
		flag_s2 = FLAG_HIGH;
		log_string(Status, change_state_f,"Switched to State Machine 2");

	}
	else if(flag_s2 == FLAG_HIGH)
	{
		flag_s2 = FLAG_LOW;
		flag_s3 = FLAG_HIGH;
		next_state = SPI_Loopback;
		log_string(Status, change_state_f,"Switched to State Machine 3");
	}
	else
	{
		flag_s3 = FLAG_LOW;
		flag_s1 = FLAG_HIGH;
		log_string(Status, change_state_f,"Switched to State Machine 1");
	}

	if(flag_s2 == FLAG_HIGH)
	{
		Enable_irq();
	}
	else
	{
		Disable_irq();
	}

}

/*
 * @brief  Reads the current state machine
 */
uint8_t read_state(void)
{
	uint8_t state = 0;
	state = (flag_s1 == 1) ? 1 : (flag_s2 == 1) ? 2 : 3;
	return state;
}
