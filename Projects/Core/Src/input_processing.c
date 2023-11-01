/*
 * input_processing.c
 *
 *  Created on: Oct 6, 2023
 *      Author: ADMIN
 */

#include "input_processing.h"

enum ButtonState
{
	BUTTON_RELEASED,
	BUTTON_PRESSED,
	BUTTON_PRESSED_MORE_THAN_1_SECOND
};

enum ButtonState buttonState = BUTTON_RELEASED;

void fsm_for_input_processing(void)
{
//	switch (buttonState)
//	{
//	case BUTTON_RELEASED:
//		if (is_button_pressed(0))
//		{
//			buttonState = BUTTON_PRESSED;
//			HAL_GPIO_TogglePin(LED1_RED_GPIO_Port, LED1_RED_Pin);
//			increase_led();
//		}
//		break;
//	case BUTTON_PRESSED:
//		if (!is_button_pressed(0))
//		{
//			buttonState = BUTTON_RELEASED;
//		}else
//		{
//			if (is_button_pressed_1s(0))
//			{
//				buttonState = BUTTON_PRESSED_MORE_THAN_1_SECOND;
//				set_timer_auto_increase(AUTO_INCREASE_DURATION);
//			}
//		}
//		break;
//	case BUTTON_PRESSED_MORE_THAN_1_SECOND:
//		if (!is_button_pressed(0))
//		{
//			buttonState = BUTTON_RELEASED;
//		}else
//		{
//			if (is_flagged_timer_auto_increase())
//			{
//				increase_led();
//				set_timer_auto_increase(AUTO_INCREASE_DURATION);
//			}
//		}
//		break;
//	}
}
