/*
 * Team1 MultiTool project
 */

#include <stdio.h>

#include "board.h"
#include "LCD.h"
#include "us_timer.h"
#include "tone.h"
#include "adc.h"
#include "button.h"

char func_strings[3][5] = { "SQRE", "RAMP", "SINE" };

/**
 * Performs ADC conversion on both channels and sends to display
 */
void voltmeter() {
	puts("Voltmeter");
	unsigned int adc_val;
	char display[17];

	set_line(0);
	/* read from the adc*/
	adc_val = adc_read(4);
	adc_val++; //One extra for a more accurate readout
	adc_val = cal_val(adc_val);
	sprintf(display, "P19: %4u mV    ", adc_val);
	string_to_LCD(display);

	/* read from the other adc*/
	adc_val = adc_read(5);
	adc_val++;
	adc_val = cal_val(adc_val);

	set_line(1);
	sprintf(display, "P20: %4u mV    ", adc_val);
	string_to_LCD(display);
}

void tone_generator(wavetype function, int frequency) {
	tone_set(frequency, function);
	char display[17];

	set_line(0);
	sprintf(display, "MODE       FREQ");
	string_to_LCD(display);

	set_line(1);
	sprintf(display, "%s  %6d Hz", func_strings[function], frequency);
	string_to_LCD(display);
}

void init() {
	SystemCoreClockUpdate();
	Board_Init();
	Chip_GPIO_Init(LPC_GPIO);
	Chip_IOCON_Init(LPC_IOCON);
	button_init();
	lcd_init();
	adc_init();
	tone_init();
	us_timer_init();
}

int main(void) {

	init();

	int mode = 3;
	int old_mode = 3;
	int frequency = 1000;
	int old_freqency = 999;
	//Our main loop
	while (1) {
		if (button_get(0)) {
			puts("Button MODE");
			mode++;
			if (mode >= 4) {
				mode = 0;
			}
		}

		if (button_get(1)) {
			puts("Button UP");
			frequency += 100;
		}
		if (button_get(2)) {
			puts("Button DOWN");
			frequency -= 100;
		}

		if (mode == 3) {
			voltmeter();
		} else { //Function generatormode (Only do this if there is a change)
			if (mode != old_mode || frequency != old_freqency) {
				printf("Setting new tone: %d,%d\n", mode, frequency);
				tone_generator(mode, frequency);
				old_mode = mode;
				old_freqency = frequency;
			}

		}
	}
	return (0);
}

