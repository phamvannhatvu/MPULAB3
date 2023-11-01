/*
 * input_reading.c
 *
 *  Created on: Oct 6, 2023
 *      Author: ADMIN
 */

#include "main.h"
#include "input_reading.h"

static GPIO_PinState buttonBuffer[NO_OF_BUTTONS];

static GPIO_PinState debounceButtonBuffer1[NO_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2[NO_OF_BUTTONS];

static uint8_t flagForButtonPress1s[NO_OF_BUTTONS];
static uint16_t counterForButtonPress1s[NO_OF_BUTTONS];

static GPIO_TypeDef * buttonPort[NO_OF_BUTTONS] = {SELECT_MODE_BTN_GPIO_Port};
static uint16_t buttonPin[NO_OF_BUTTONS] = {SELECT_MODE_BTN_Pin};

void button_reading(void)
{
	for (uint8_t i = 0; i < NO_OF_BUTTONS; ++i)
	{
		debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
		debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(buttonPort[i], buttonPin[i]);
		if (debounceButtonBuffer1[i] == debounceButtonBuffer2[i])
		{
			buttonBuffer[i] = debounceButtonBuffer1[i];
			if (buttonBuffer[i] == BUTTON_IS_PRESSED)
			{
				if (counterForButtonPress1s[i] < DURATION_FOR_AUTO_INCREASING)
				{
					++counterForButtonPress1s[i];
				}else
				{
					flagForButtonPress1s[i] = 1;
				}
			}else
			{
				counterForButtonPress1s[i] = 0;
				flagForButtonPress1s[i] = 0;
			}
		}
	}
}

unsigned char is_button_pressed(uint8_t index)
{
	if (index >= NO_OF_BUTTONS) return 0;
	return (buttonBuffer[index] == BUTTON_IS_PRESSED);
}

unsigned char is_button_pressed_1s(uint8_t index)
{
	if (index >= NO_OF_BUTTONS) return 0;
	return (flagForButtonPress1s[index] == 1);
}

void init_button()
{
	for (uint8_t i = 0; i < NO_OF_BUTTONS; ++i)
	{
		buttonBuffer[i] = BUTTON_IS_RELEASED;
		debounceButtonBuffer1[i] = BUTTON_IS_RELEASED;
		debounceButtonBuffer2[i] = BUTTON_IS_RELEASED;

		flagForButtonPress1s[i] = 0;
		counterForButtonPress1s[i] = 0;
	}
}
