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

#define TIME_UNIT 1 //in ms

void set_timer_blink(uint16_t);
uint8_t is_timer_blink_flagged(void);

//void set_timer_auto_increase(uint16_t);
//uint8_t is_flagged_timer_auto_increase(void);
#endif /* INC_TIMER_H_ */
