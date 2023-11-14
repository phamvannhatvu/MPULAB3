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
#define SCANNING_DURATION 250

void set_timer_blink(uint16_t);
uint8_t is_timer_blink_flagged(void);

void set_timer_btn_reading(uint16_t);
uint8_t is_timer_btn_reading_flagged(void);

void set_timer_7seg_scan(uint16_t);
uint8_t is_timer_7seg_scan_flagged(void);

void set_timer_traffic1(uint16_t);
uint8_t is_timer_traffic1_flagged(void);
void set_timer_traffic2(uint16_t);
uint8_t is_timer_traffic2_flagged(void);

void set_timer_auto_increase(uint16_t);
uint8_t is_timer_auto_increase_flagged(void);

#endif /* INC_TIMER_H_ */
