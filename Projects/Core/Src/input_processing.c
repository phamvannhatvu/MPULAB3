/*
 * input_processing.c
 *
 *  Created on: Oct 6, 2023
 *      Author: ADMIN
 */

#include "input_processing.h"

enum ButtonState buttonState[NO_OF_BUTTONS];

enum ButtonState get_button_state(uint8_t index)
{
	return buttonState[index];
}

void init_button_state()
{
	for (uint8_t i = 0; i < NO_OF_BUTTONS; ++i)
	{
		buttonState[i] = BUTTON_RELEASED;
	}
}

//FSM for buttons that do not support auto-increment while holding.
void not_auto_increase_btn_fsm(uint8_t index)
{
	switch (buttonState[index])
	{
	case BUTTON_RELEASED:
		if (is_button_pressed(0))
		{
			buttonState[index] = BUTTON_PRESSED;
		}
		break;
	case BUTTON_PRESSED:
		if (!is_button_pressed(0))
		{
			buttonState[index] = BUTTON_RELEASED;
		}
		break;
	default:
		break;
	}
}
