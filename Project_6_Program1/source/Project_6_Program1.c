/*
 * Copyright 2016-2020 NXP
 * All rights reserved.
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
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
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
//@Ref: https://electrovolt.ir/wp-content/uploads/2017/07/Freescale_ARM_Cortex_M_Embedded_ElectroVolt.ir_.pdf
/**
 * @file    Project_5_Program1.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include <math.h>
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */
void DAC0_init(void);
#define WAVEFORM_LENGTH 50
int sinewave[WAVEFORM_LENGTH];
void delayMs(int n);
/*
 * @brief   Application entry point.
 */
int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    int i;
    float fRadians;
    const float F_PI = 3.1415926535897;

    /* construct data table for a sine wave */
    fRadians = ((2 * F_PI) / WAVEFORM_LENGTH);

    for (i = 0; i < WAVEFORM_LENGTH; i++)
    {
    	sinewave[i] = ((sinf(fRadians * i) + 2) / 0.000806);
    }

    DAC0_init(); /* Configure DAC0 */

    while (1)
    {
    	for (i = 0; i < WAVEFORM_LENGTH; i++)
    	{
    		/* write value to DAC0 */
			DAC0->DAT[0].DATL = sinewave[i] & 0xff; /* write low byte */
			DAC0->DAT[0].DATH = (sinewave[i] >> 8) & 0x0f;/* write high byte */
			delayMs(100); /* delay 1ms */
		}
    }

    return 0 ;
}

void DAC0_init(void)
{
	SIM->SCGC6 |= 0x80000000; /* clock to DAC module */
	DAC0->C1 = 0; /* disable the use of buffer */
	DAC0->C0 = 0x80 | 0x20; /* enable DAC and use software trigger */
}

/*
 * Delay n milliseconds
 * The CPU core clock is set to MCGFLLCLK at 41.94 MHz in SystemInit().
 */
void delayMs(int n)
{
	int i, j;
	for(i = 0 ; i < n; i++)
	for (j = 0; j < 7000; j++) {}
}
