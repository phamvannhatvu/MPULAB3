/*
 * led_display.h
 *
 *  Created on: Oct 6, 2023
 *      Author: ADMIN
 */

#ifndef INC_LED_DISPLAY_H_
#define INC_LED_DISPLAY_H_

#include "main.h"

#define NO_OF_ROADS 2
#define TRAFFIC_DURATION 1000
#define BLINK_DURATION 250
#define NUM_OF_7SEG_LEDS 4

enum TrafficLightState
{
	RED,
	GREEN,
	YELLOW
};

void display7SEG(uint8_t);
void traffic_light_reset(void);
void traffic_light_fsm(void);

void blink_led(enum TrafficLightState);
void blink_led_clear(void);

void led7_scanning();
#endif /* INC_LED_DISPLAY_H_ */
