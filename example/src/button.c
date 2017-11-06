/*
 * button.c
 *
 *  Created on: 6. nov. 2017
 *      Author: Test Bruger
 */

#include "button.h"

void button_init() {

	/* Setup DAC pins for pin 0.26 -AOUT, P18 on the LPC4088 QSB
	 * see section 7.3 in UM10562 for details, table 85 & 86  */
	Chip_IOCON_PinMuxSet(LPC_IOCON, BTN0PORT, BTN0PIN, IOCON_FUNC0);
	Chip_IOCON_PinMuxSet(LPC_IOCON, BTN1PORT, BTN1PIN, IOCON_FUNC0);
	Chip_IOCON_PinMuxSet(LPC_IOCON, BTN2PORT, BTN2PIN, IOCON_FUNC0);

	Chip_GPIO_SetPinDIRInput(LPC_GPIO, BTN0PORT,BTN0PIN);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, BTN1PORT,BTN1PIN);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, BTN2PORT,BTN2PIN);

}

bool button_get(int btn)
{
	switch (btn)
	{
	case 1:
		return Chip_GPIO_GetPinState(LPC_GPIO, BTN1PORT, BTN1PIN);
	case 2:
		return Chip_GPIO_GetPinState(LPC_GPIO, BTN2PORT, BTN2PIN);
	default:
		return Chip_GPIO_GetPinState(LPC_GPIO, BTN0PORT, BTN0PIN);
	}
}
