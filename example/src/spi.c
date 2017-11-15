/*
 * spi.c
 *
 *  Created on: Nov 24, 2015
 *      Author: mortenopprudjakobsen
 */

#include "board.h"



/*
 * Initialize SSP0 controller to run in SPI mode
 * - 1Mhz
 * - 8 bits
 * - MSB first
 *
 * */
void spi_init (void)
{
	unsigned int clkDiv;
	unsigned int perClkDiv;

	//1. Power: In the PCONP register (Section 3.3.2.2), set bit PCSSP1 to enable SSP1 and
	//bit PCSSP1 to enable SSP1.
	//enable clk for SSP1
	LPC_SYSCON->PCONP |= (1 << 10);

	//2. Peripheral clock: The SSPs operate from the common PCLK that clocks both the bus
	//interface and functional portion of most APB peripherals. See Section 3.3.3.5. In
	//master mode, the clock must be scaled down (see Section 21.6.5).
	//global peripereal prescaler
	clkDiv = LPC_SYSCON->PCLKSEL;

	//tagerget SPI clk is 1Mhz CPU is 120Mhz
	perClkDiv = 120 / clkDiv;

	//write calculated prescaler value
	LPC_SSP1->CPSR = perClkDiv;

	//3. Pins: Select the SSP pins and pin modes through the relevant IOCON registers
	//(Section 7.4.1).
	/*
	 * Initialize SSP1 pins connect, (see section 7.4.1.1, table 84)
	 * See README
	 */

	Chip_IOCON_PinMuxSet (LPC_IOCON, 0, 6,
	                      (IOCON_FUNC0 | IOCON_MODE_INACT | IOCON_DIGMODE_EN)); //Chip Select - Use as GPIO
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 6);
	Chip_GPIO_SetPinState(LPC_GPIO, 0, 6, 1);

	Chip_IOCON_PinMuxSet (LPC_IOCON, 0, 7,
	                      (IOCON_FUNC2 | IOCON_MODE_INACT | IOCON_DIGMODE_EN));
	Chip_IOCON_PinMuxSet (LPC_IOCON, 0, 8,
	                      (IOCON_FUNC2 | IOCON_MODE_INACT | IOCON_DIGMODE_EN));
	Chip_IOCON_PinMuxSet (LPC_IOCON, 0, 9,
	                      (IOCON_FUNC2 | IOCON_MODE_INACT | IOCON_DIGMODE_EN));

	/*  8bit transfer size, SPI, CPOL0, CPHA0,
	 * NOTE prescaler value is allready set w CPSR*/
	LPC_SSP1->CR0 = 0x00000007;

	/* no loopback, enable SSP, MAster */
	LPC_SSP1->CR1 = 2;	//(1<<1);

}

void spi_start() {
	Chip_GPIO_SetPinState(LPC_GPIO, 0, 6, 0);
}

void spi_stop() {
	Chip_GPIO_SetPinState(LPC_GPIO, 0, 6, 1);
}
/**
 * Transfer one byte on SPI
 * arguments: tx - byte to transmit
 * returns  : byte read from SPI
 *
 * */
unsigned char spi_xfer (unsigned char tx)
{
	unsigned char rx;

	/* wait for SSP controller to be IDLE (bit 4 is SR)*/
	while (LPC_SSP1->SR & 0x10);

	/* transmit a frame */
	LPC_SSP1->DR = (unsigned int) tx;

	/* wait for SSP controller to be IDLE (bit 4 is SR)
	 * when IDLE we assume the frame is transmitted, and a new recieved*/
	while (LPC_SSP1->SR & 0x10);

	/*read incoming frame*/
	rx = LPC_SSP1->DR;

	/* return recieve data */
	return rx;

}

