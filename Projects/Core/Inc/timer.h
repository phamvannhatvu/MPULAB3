/*
 * timer.h
 *
 *  Created on: Oct 6, 2023
 *      Author: ADMIN
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "main.h"
//#include "input_reading.h"

#define TIME_UNIT 10 //in ms

void set_timer_blink(uint16_t);
uint8_t is_timer_blink_flagged(void);
void set_timer_btn_reading(uint16_t);
uint8_t is_timer_btn_reading_flagged(void);

#endif /* INC_TIMER_H_ */
