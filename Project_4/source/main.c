/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include "main.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
static uint8_t s1_entrycount;
static uint8_t flag_s1, flag_s2;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/


/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */
int main(void)
{
    /* Init board hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    i2c_init();
    if(!acc_init())
    {
    	printf("Error connecting Accelerometer!\n\r");
    	exit(0);
    }
    LED_init();						// Initialize LED
	TOUCH_init(BOARD_TOUCH_PORT);	// Initialize capacitive touch sensor
	flag_s1 = 1;
	flag_s2 = 0;
	state_e (*state_table[MAX_STATES][MAX_EVENTS]) (void) = {
			{ Read_XYZ_Acc_Handler, Error_Handler, Error_Handler, Error_Handler, Read_XYZ_Acc_Handler, Read_XYZ_Acc_Handler, Error_Handler	},
			{ Error_Handler, Error_Handler, Process_Acc_Handler, Error_Handler, Error_Handler, Error_Handler, Error_Handler	},
			{ Error_Handler, Error_Handler, Poll_Slider_Handler, Error_Handler, Error_Handler, Error_Handler, Error_Handler },
			{ Error_Handler, Error_Handler, Error_Handler, Acc_Disconnect_Handler, Error_Handler, Error_Handler, Error_Handler },
			{ Error_Handler, Error_Handler, Error_Handler, Error_Handler, Error_Handler, Error_Handler }
	};

    event_e current_event;
    state_e current_state;
    state_e next_state;
    s1_entrycount = 0;

    next_state = POST_Test_Handler();

    while(1)
    {
		if(flag_s1)
		{
			current_event = read_event();
			current_state = next_state;

			if((current_event == Fail) || (current_event == Right_slider))
			{
				end_state();
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
				case(Acc_Disconnect):
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

		if(flag_s2)
		{
			current_event = read_event();
			current_state = next_state;

			if((current_event >= 0) && (current_event < MAX_EVENTS))
			{
				next_state = state_table[current_state][current_event]();
			}
		}
    }
}

void end_state(void)
{
	exit(1);
}

uint8_t read_state1_count(void)
{
	return s1_entrycount;
}

void reset_state1_count(void)
{
	s1_entrycount = 0;
}

state_e Error_Handler(void)
{
	end_state();
	return Error;
}

void change_state(void)
{
	flag_s1 ^= 1;
	flag_s2 ^= 1;

	if(flag_s2 == 1)
	{
		Enable_irq();
	}
	else
	{
		Disable_irq();
	}
}



