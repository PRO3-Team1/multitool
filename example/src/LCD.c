/*
 * LCD.c
 *
 *  Created on: 11. okt. 2017
 *      Author: Test Bruger
 */
#include <time.h>
#include "LCD.h"
#include "board.h"

void delay_ms(int ms) {
int i = 40000*ms;

while (i--);

}

/**
 * Control PINS. All as output
 */
void controlpin_output(void) {

	/*This pin was set to ADC or DAC, and we need to initialize it to GPIO
	 * Ideally all pins should be set to GPIO.
	 */
	Chip_IOCON_PinMuxSet(LPC_IOCON, RS_PORT, RS_PIN, IOCON_FUNC0);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, RS_PORT, RS_PIN);

	Chip_IOCON_PinMuxSet(LPC_IOCON, RW_PORT, RW_PIN, IOCON_FUNC0);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, RW_PORT, RW_PIN);

	Chip_IOCON_PinMuxSet(LPC_IOCON, ENABLE_PORT, ENABLE_PIN, IOCON_FUNC0);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, ENABLE_PORT, ENABLE_PIN);

}

/**
 * Data PINS. p23-p30. All as output.
 */
void datapin_output(void) {

	Chip_GPIO_SetPinDIROutput(LPC_GPIO, DATA0_PORT, DATA0_PIN);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, DATA1_PORT, DATA1_PIN);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, DATA2_PORT, DATA2_PIN);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, DATA3_PORT, DATA3_PIN);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, DATA4_PORT, DATA4_PIN);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, DATA5_PORT, DATA5_PIN);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, DATA6_PORT, DATA6_PIN);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, DATA7_PORT, DATA7_PIN);

}

/**
 * Set RS to 0. To send commands.
 * Set RW to 0. To write data.
 * Set enable to 0.
 */
void command_mode(void) {

	Chip_GPIO_SetPinState(LPC_GPIO, RS_PORT, RS_PIN, 0);

	Chip_GPIO_SetPinState(LPC_GPIO, RW_PORT, RW_PIN, 0);

	Chip_GPIO_SetPinState(LPC_GPIO, ENABLE_PORT, ENABLE_PIN, 0);
}

void data_mode(void) {
	Chip_GPIO_SetPinState(LPC_GPIO, RS_PORT, RS_PIN, 1);
}

void setbus(char c) {

	Chip_GPIO_SetPinState(LPC_GPIO, DATA0_PORT, DATA0_PIN, c & 0x1);
	Chip_GPIO_SetPinState(LPC_GPIO, DATA1_PORT, DATA1_PIN, c & 0x2);
	Chip_GPIO_SetPinState(LPC_GPIO, DATA2_PORT, DATA2_PIN, c & 0x4);
	Chip_GPIO_SetPinState(LPC_GPIO, DATA3_PORT, DATA3_PIN, c & 0x8);
	Chip_GPIO_SetPinState(LPC_GPIO, DATA4_PORT, DATA4_PIN, c & 0x10);
	Chip_GPIO_SetPinState(LPC_GPIO, DATA5_PORT, DATA5_PIN, c & 0x20);
	Chip_GPIO_SetPinState(LPC_GPIO, DATA6_PORT, DATA6_PIN, c & 0x40);
	Chip_GPIO_SetPinState(LPC_GPIO, DATA7_PORT, DATA7_PIN, c & 0x80);
}

void toggle_enable(void) {

	Chip_GPIO_SetPinState(LPC_GPIO, ENABLE_PORT, ENABLE_PIN, 1);
	delay_ms(10);

	Chip_GPIO_SetPinState(LPC_GPIO, ENABLE_PORT, ENABLE_PIN, 0);
	delay_ms(10);
}

void lcd_write(char c) {
	setbus(c);
	toggle_enable();
}

/*
 * The delay function is crucial.
 */
void function_mode(void) {

	lcd_write(FUNCTION_MODE);
	toggle_enable();

}

void display_mode(void) {

	lcd_write(DISPLAY_MODE);
	toggle_enable();
}

void clear_mode(void) {

	lcd_write(CLEAR_MODE);
	toggle_enable();
}

void lcd_init(void) {
	delay_ms(10);
	Chip_GPIO_Init(LPC_GPIO);
	Chip_IOCON_Init(LPC_IOCON);

	controlpin_output();
	datapin_output();
	command_mode();
	function_mode();
	display_mode();
	clear_mode();
}

void set_line(int line) {
	command_mode();
	if (line) {
		lcd_write(JUMP_LINE_1);
	}
	else{
		lcd_write(JUMP_LINE_0);
	}
	toggle_enable();
}

void char_to_LCD(char value) {

	data_mode();
	lcd_write(value);
}

void string_to_LCD(char *string) {
	while (*string) {
		char_to_LCD(*string++);
	}
}
