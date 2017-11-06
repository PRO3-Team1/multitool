/*
 * button.h
 *
 *  Created on: 6. nov. 2017
 *      Author: Test Bruger
 */

#include "board.h"

#ifndef SRC_BUTTON_H_
#define SRC_BUTTON_H_

#define BTN0PORT 0
#define BTN0PIN 23

#define BTN1PORT 0
#define BTN1PIN 24

#define BTN2PORT 0
#define BTN2PIN 25




void button_init();
bool button_get();

#endif /* SRC_BUTTON_H_ */
