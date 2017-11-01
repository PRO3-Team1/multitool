/*
 * @brief Blinky example using sysTick
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2014
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "board.h"
#include "LCD.h"
#include <stdio.h>
#include "us_timer.h"
#include "tone.h"
#include "adc.h"

void multimeter() {
	unsigned int adc_val, adc_val2;

	char line0[16];
	char line1[16];

	set_line(0);
	/* rad from the adc*/
	adc_val = adc_read(4);
	adc_val++;
	adc_val = cal_val(adc_val);
	sprintf(line0, "P19: %4u mV    ", adc_val);
	string_to_LCD(line0);

	/* rad from the adc*/
	adc_val2 = adc_read(5);
	adc_val2++;
	adc_val2 = cal_val(adc_val2);

	set_line(1);
	sprintf(line1, "P20: %4u mV    ", adc_val2);
	string_to_LCD(line1);
	//memset(line1,'\0',sizeof(line1));
	delay_ms(200);

}

void tone_generator() {
	set_tone(1, SINE);
	int freq=0;
	char line0[16];
	char line1[16];

	set_line(0);
	sprintf(line0, "mode:1 frq:2u 3n");
	string_to_LCD(line0);

	set_line(1);
	sprintf(line1, "SINE  :%6d Hz",freq);
	string_to_LCD(line1);
}

int main(void) {

	SystemCoreClockUpdate();
	Board_Init();
	delay_ms(1000);

	lcd_init();
	adc_init();
	tone_init();
	us_timer_init();
	int switch0 = 1;

	while (1) {
		if (switch0) {
			tone_generator();

		} else {

			multimeter();

		}
	}
	return (0);
}

