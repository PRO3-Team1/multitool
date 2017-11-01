/*
 * adc.c
 *
 *  Created on: Nov 5, 2015
 *      Author: mortenopprudjakobsen
 */
#include "chip.h"

#define PCADC			(1 << 12)
#define PDN				(1 << 21)
#define START			(1 << 24)
#define ADC_DONE		(1 << 31)
#define ADC4_SEL		(1 << 4)
#define FUNC			0x00000003
#define RES				(3300.0/4096.0)
/**
 *  Initialize the ADC for simple polled mode
 *  Setup one single pin for reading the 12 bit analog value
 *
 * */
void adc_init (void)
{
	/* see section 32.1 in UM10562 for details
	 * The ADC is configured using the following registers:
	 *	1. Power: In the PCONP register (Section 3.3.2.2), set the PCADC bit.
	 *	Remark: On reset, the ADC is disabled. To enable the ADC, first set the PCADC bit,
	 *	and then enable the ADC in the AD0CR register (bit PDN Table 678). To disable the
	 *	ADC, first clear the PDN bit, and then clear the PCADC bit. */
	LPC_SYSCTL->PCONP |= PCADC;
	LPC_ADC->CR |= PDN;

	/*	2. Peripheral clock: The ADC operates from the common PCLK that clocks both the bus
	 *	interface and functional portion of most APB peripherals. See Section 3.3.3.5. To
	 *	scale the clock for the ADC, see bits CLKDIV in Table 678.
	 *	We assume the CPU runs 120MHz, so divide with 10 to get 12Mhz (must be below 12.4MHz)*/

	/* first clear bits 7:15*/
	LPC_ADC->CR &= ~0x0000FF00;

	/* now set bits 7:15 to prescale value -1 */
	LPC_ADC->CR |= 0x00000900;

	/*	3. Pins: Enable ADC0 pins and pin modes for the port pins with ADC0 functions through
	 *	the relevant IOCON registers (Section 7.4.1).*/

	/* Use ADC channel 0 - P15 on the mBed, P0.23 on the LPC4088, see table85, P138 in the UM for details */
	//LPC_IOCON->p[0][23] = 0x00000001;
	/* Use ADC channel 1 - P19 on the mBed, P1.30 on the LPC4088, see table85, P138 in the UM for details */
	LPC_IOCON->p[1][30] = FUNC;
	//	/* Use ADC channel 0 - P20 on the mBed, P1.31 on the LPC4088, see table85, P138 in the UM for details */
	LPC_IOCON->p[1][31] = FUNC;
}

/**
 * Read a value fromADC channel 0
 * blocking function, returns when conversion is done
 * */
unsigned int adc_read (int chan_sel)
{
	unsigned int val;

	/* first clear bits 0:7*/
	LPC_ADC->CR &= ~0x000000FF;

	/* select channel 0*/
	//allready done in the AdcInit function
	/* start conversion, manually */
	LPC_ADC->CR |= START | (1 << chan_sel);

	/* read the Global data register, also holds the DONE bit, NOT cleared on read */
	val = LPC_ADC->GDR;

	while (!(val & ADC_DONE))
	{
		/* read the Global data register, also holds the DONE bit, NOT cleared on read */
		val = LPC_ADC->GDR;
	}

	/* stop conversion, manually */
	LPC_ADC->CR &= ~START;

	/* conversion is done, extract result, needs to be rightshifted 4 bits */
	val = (val>>4) ;

	/* mask out 12 lower result bits DONE and other possible status bits */
	val &= 0xFFF;

	return val;
}

unsigned int cal_val (unsigned int val)
{
	return val*RES;
}
