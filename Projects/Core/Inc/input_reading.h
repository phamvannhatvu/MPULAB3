/*
 * input_reading.h
 *
 *  Created on: Oct 6, 2023
 *      Author: ADMIN
 */

#ifndef INC_INPUT_READING_H_
#define INC_INPUT_READING_H_

#define NO_OF_BUTTONS 3

#define DURATION_FOR_AUTO_INCREASING 100
#define BUTTON_IS_PRESSED GPIO_PIN_RESET
#define BUTTON_IS_RELEASED GPIO_PIN_SET

void button_reading(void);
unsigned char is_button_pressed(unsigned char index);
unsigned char is_button_pressed_1s(unsigned char index);
void init_button(void);

#endif /* INC_INPUT_READING_H_ */
