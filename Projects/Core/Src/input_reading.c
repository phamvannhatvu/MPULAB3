/*
 * input_reading.c
 *
 *  Created on: Oct 6, 2023
 *      Author: ADMIN
 */

#include "main.h"
#include "input_reading.h"

#define NO_OF_BUTTONS 1

#define DURATION_FOR_AUTO_INCREASING 100
#define BUTTON_IS_PRESSED GPIO_PIN_RESET
#define BUTTON_IS_RELEASED GPIO_PIN_SET

static GPIO_PinState buttonBuffer[] = {BUTTON_IS_RELEASED};

static GPIO_PinState debounceButtonBuffer1[NO_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2[NO_OF_BUTTONS];

static uint8_t flagForButtonPress1s[NO_OF_BUTTONS];
static uint16_t counterForButtonPress1s[NO_OF_BUTTONS];

void button_reading(void)
{
	for (uint8_t i = 0; i < NO_OF_BUTTONS; ++i)
	{
		debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
		debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(BUTTON_GPIO_Port, BUTTON_Pin);
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
	return (buttonBuffer[0] == BUTTON_IS_PRESSED);
}

unsigned char is_button_pressed_1s(uint8_t index)
{
	if (index >= NO_OF_BUTTONS) return 0;
	return (flagForButtonPress1s[index] == 1);
}
