/*
 * button.h
 *
 *  Created on: 6. nov. 2017
 *      Author: Test Bruger
 */

#ifndef SRC_BUTTON_H_
#define SRC_BUTTON_H_

#include "chip.h"
#include "board.h"

#define BTN0PORT 	0
#define BTN0PIN		23

#define BTN1PORT 	0
#define BTN1PIN		24

#define BTN2PORT 	0
#define BTN2PIN		25

#define BTN0GET() ( (LPC_GPIO[BTN0PORT].PIN) & (1UL << BTN0PIN) )
#define BTN1GET() ( (LPC_GPIO[BTN1PORT].PIN) & (1UL << BTN1PIN) )
#define BTN2GET() ( (LPC_GPIO[BTN2PORT].PIN) & (1UL << BTN2PIN) )


enum button_t {BTN_0, BTN_1, BTN_2, BTN_3};


void button_init();
int button_get(enum button_t btn);


#endif /* SRC_BUTTON_H_ */
