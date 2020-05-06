
/********************************************************************************
 * File name: "i2c.c"
 *
 * Description: I2C driver routines
 *
 *
 * File​ ​ Author​ ​ Name: Disha Modi and Alexandra Paquin
 *
 * Tools​ ​ used​ ​ to​ ​ process​ ​ the​ ​ code​ ​ (compiler,​ ​ linker,​ ​ debugger):
 * 		NXP MCU Tools, Gnu Make Builder, Putty
 *
 * Identification​ ​ of​ ​ any​ ​ leveraged​ ​ code: https://github.com/alexander-g-dean/ESF/blob/master/Code/Chapter_8/I2C-Demo/src/i2c.c
 *
 * Applicable​ ​ Links: None
 *******************************************************************************/

#include "I2C.h"
#include <MKL25Z4.H>
int lock_detect=0;
int i2c_lock=0;
int INT_ENABLE = 0;
int INT_SERVED = 0;

//I2C0 initialization routine
void I2C_init(void)
{

	log_string(Status, I2C_init_f, "Initializing I2C Device");

	//clock i2c peripheral and port C
	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;

	//set pins to I2C function
	PORTE->PCR[24] |= PORT_PCR_MUX(5);
	PORTE->PCR[25] |= PORT_PCR_MUX(5);

	//set to 400k baud
	//baud = bus freq/(scl_div+mul)
	 //~400k = 24M/(64); icr=0x12 sets scl_div to 64
	I2C0->F = I2C_F_ICR(0x10) | I2C_F_MULT(0);

	//enable i2c and set to master mode
	I2C0->C1 |= I2C_C1_IICEN_MASK;

	/* Enable TX mode */
	I2C0 -> C1 |= I2C_C1_TX_MASK;

	// Select high drive mode
	I2C0->C2 |= I2C_C2_HDRS_MASK;

	//I2C0->SLTH |= I2C_SLTL_SSLT(0x01);
}

//send start sequence
void i2c_start()
{
	log_string(Test, i2c_start_f, "Sending start sequence");
	I2C_TRAN;							/*set to transmit mode */
	I2C_M_START;					/*send start	*/
}

//send device and register addresses
void i2c_read_setup(uint8_t dev, uint8_t address)
{
	log_string(Test, i2c_read_setup_f, "Sending device and register addresses");

	I2C0->D = dev;			  /*send dev address	*/
	I2C_WAIT							/*wait for completion */

	I2C0->D =  address;		/*send read address	*/
	I2C_WAIT							/*wait for completion */

	I2C_M_RSTART;				   /*repeated start */
	I2C0->D = (dev|0x1);	 /*send dev address (read)	*/
	I2C_WAIT							 /*wait for completion */

	I2C_REC;						   /*set to receive mode */

}

//read a byte and ack/nack as appropriate
// #pragma no_inline
uint8_t i2c_repeated_read(uint8_t isLastRead)
{
	log_string(Test, i2c_repeated_read_f, "Repeated reading");

	uint8_t data;

	lock_detect = 0;

	if(isLastRead)	{
		NACK;								/*set NACK after read	*/
	} else	{
		ACK;								/*ACK after read	*/
	}

	data = I2C0->D;				/*dummy read	*/
	I2C_WAIT							/*wait for completion */

	if(isLastRead)	{
		I2C_M_STOP;					/*send stop	*/
	}
	data = I2C0->D;				/*read data	*/

	return  data;
}

//////////funcs for reading and writing a single byte
//using 7bit addressing reads a byte from dev:address
// #pragma no_inline
uint8_t i2c_read_byte(uint8_t dev, uint8_t address)
{
	log_string(Test, i2c_read_byte_f, "Reading single byte");

	uint8_t data;

	I2C_TRAN;							/*set to transmit mode */
	I2C_M_START;					/*send start	*/
	I2C0->D = dev;			  /*send dev address	*/
	I2C_WAIT							/*wait for completion */

	I2C0->D =  address;		/*send read address	*/
	I2C_WAIT							/*wait for completion */

	I2C_M_RSTART;				   /*repeated start */
	I2C0->D = (dev|0x1);	 /*send dev address (read)	*/
	I2C_WAIT							 /*wait for completion */

	I2C_REC;						   /*set to recieve mode */
	NACK;									 /*set NACK after read	*/

	data = I2C0->D;					/*dummy read	*/
	I2C_WAIT								/*wait for completion */

	I2C_M_STOP;							/*send stop	*/
	data = I2C0->D;					/*read data	*/

	return data;
}



//using 7bit addressing writes a byte data to dev:address
void i2c_write_byte(uint8_t dev, uint8_t address, uint8_t data)
{
	log_string(Test, i2c_write_byte_f, "Writing byte");

	I2C_TRAN;							/*set to transmit mode */
	I2C_M_START;					/*send start	*/
	I2C0->D = dev;			  /*send dev address	*/
	I2C_WAIT						  /*wait for ack */

	I2C0->D =  address;		/*send write address	*/
	I2C_WAIT

	I2C0->D = data;				/*send data	*/
	I2C_WAIT
	I2C_M_STOP;

}

//Resets the accelerometer for any inconsistent state
void i2c_busy(void){
	// Start Signal
	lock_detect=0;
	I2C0->C1 &= ~I2C_C1_IICEN_MASK;
	I2C_TRAN;
	I2C_M_START;
	I2C0->C1 |=  I2C_C1_IICEN_MASK;
	// Write to clear line
	I2C0->C1 |= I2C_C1_MST_MASK; /* set MASTER mode */
	I2C0->C1 |= I2C_C1_TX_MASK; /* Set transmit (TX) mode */
	I2C0->D = 0xFF;
	while ((I2C0->S & I2C_S_IICIF_MASK) == 0U) {
	} /* wait interrupt */
	I2C0->S |= I2C_S_IICIF_MASK; /* clear interrupt bit */


							/* Clear arbitration error flag*/
	I2C0->S |= I2C_S_ARBL_MASK;


							/* Send start */
	I2C0->C1 &= ~I2C_C1_IICEN_MASK;
	I2C0->C1 |= I2C_C1_TX_MASK; /* Set transmit (TX) mode */
	I2C0->C1 |= I2C_C1_MST_MASK; /* START signal generated */

	I2C0->C1 |= I2C_C1_IICEN_MASK;
							/*Wait until start is send*/

							/* Send stop */
	I2C0->C1 &= ~I2C_C1_IICEN_MASK;
	I2C0->C1 |= I2C_C1_MST_MASK;
	I2C0->C1 &= ~I2C_C1_MST_MASK; /* set SLAVE mode */
	I2C0->C1 &= ~I2C_C1_TX_MASK; /* Set Rx */
	I2C0->C1 |= I2C_C1_IICEN_MASK;


								/* wait */
							/* Clear arbitration error & interrupt flag*/
	I2C0->S |= I2C_S_IICIF_MASK;
	I2C0->S |= I2C_S_ARBL_MASK;
	lock_detect=0;
	i2c_lock=1;
}

//Wait for I2C slave Ack or interrupt flag
void i2c_wait(void)
{
	if(INT_ENABLE == 0)
	{
		log_string(Test, i2c_wait_f, "Waiting for next I2C slave ACK");
		lock_detect = 0;
		while(((I2C0->S & I2C_S_IICIF_MASK)==0) & (lock_detect < 200)) {
			lock_detect++;
		}
		if (lock_detect >= 200)
			i2c_busy();
		I2C0->S |= I2C_S_IICIF_MASK;
	}
	else
	{
		log_string(Test, i2c_wait_f, "Waiting for next I2C interrupt");
		while(INT_SERVED == 0){
		}
		log_string(Test, i2c_wait_f, "I2C interrupt Served");
		INT_SERVED = 0;
	}
}

//Returns i2c lock flag
int read_i2c_lock(void)
{
	return i2c_lock;
}

//Enable the i2c interrupt
void Enable_irq()
{
	  log_string(Debug, Enable_irq_f, "Enabling I2C IRQ");

	  /* Enable I2C module and interrupt */
	  I2C0->C1 |= I2C_C1_IICEN_MASK | I2C_C1_IICIE_MASK;

      /* Set the ICPR and ISER registers accordingly */
	  NVIC_ClearPendingIRQ(I2C0_IRQn);
	  NVIC_EnableIRQ(I2C0_IRQn);
	  INT_ENABLE = 1;
}

//Disable the i2c interrupt
void Disable_irq()
{

	log_string(Debug, Disable_irq_f, "Disabling I2C IRQ");
	I2C0->C1 &= ~I2C_C1_IICIE_MASK;

	NVIC_ClearPendingIRQ(I2C0_IRQn);
	NVIC_DisableIRQ(I2C0_IRQn);
	INT_ENABLE = 0;
}

// I2C interrupt service routine
void I2C0_IRQHandler(void)
{
	I2C0->S |= I2C_S_IICIF_MASK;
	INT_SERVED = 1;

	if(I2C0->C1 & I2C_C1_TX_MASK) // Transmitter mode?
	{
		if((I2C0->S & I2C_S_RXAK_MASK) != 0) // ACK Received?
		{
			i2c_busy();
		}
	}
}
