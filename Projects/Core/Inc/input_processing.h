/*
 * input_processing.h
 *
 *  Created on: Oct 6, 2023
 *      Author: ADMIN
 */

#ifndef INC_INPUT_PROCESSING_H_
#define INC_INPUT_PROCESSING_H_

#include "main.h"
#include "input_reading.h"

enum ButtonState
{
	BUTTON_RELEASED,
	BUTTON_PRESSED,
	BUTTON_PRESSED_MORE_THAN_1_SECOND
};

enum ButtonState get_button_state(uint8_t);
void init_button_state();
void not_auto_increase_btn_fsm(uint8_t);

#endif /* INC_INPUT_PROCESSING_H_ */
