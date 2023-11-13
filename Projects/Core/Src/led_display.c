/*
 * led_display.c
 *
 *  Created on: Oct 6, 2023
 *      Author: ADMIN
 */

#include "led_display.h"

uint8_t red_duration = 5;
uint8_t green_duration = 3;
uint8_t yellow_duration = 2;

//initial state: red at one road and green at the other
uint8_t roadCounter[NO_OF_ROADS];

enum TrafficLightState roadState[NO_OF_ROADS] = {RED, GREEN};
GPIO_TypeDef * redPort[NO_OF_ROADS] = {LED1_RED_GPIO_Port, LED2_RED_GPIO_Port};
GPIO_TypeDef * greenPort[NO_OF_ROADS] = {LED1_GREEN_GPIO_Port, LED2_GREEN_GPIO_Port};
GPIO_TypeDef * yellowPort[NO_OF_ROADS] = {LED1_YELLOW_GPIO_Port, LED2_YELLOW_GPIO_Port};
uint16_t redPin[NO_OF_ROADS] = {LED1_RED_Pin, LED2_RED_Pin};
uint16_t greenPin[NO_OF_ROADS] = {LED1_GREEN_Pin, LED2_GREEN_Pin};
uint16_t yellowPin[NO_OF_ROADS] = {LED1_YELLOW_Pin, LED2_YELLOW_Pin};

/*scanning led values
 * normal mode: {1st road tenth, 1st road unit, 2nd road tenth, 2nd road unit}
 * other modes: {duration value tenth, duration value unit, mode tenth, mode unit}
 */
uint8_t led_7seg_values[NUM_OF_7SEG_LEDS];
uint8_t led7_status = 0;

void traffic_light_reset()
{
	roadCounter[0] = red_duration;
	roadState[0] = RED;
	roadCounter[1] = green_duration;
	roadState[1] = GREEN;
	set_timer_traffic1(TRAFFIC_DURATION);
	set_timer_traffic2(TRAFFIC_DURATION);

	HAL_GPIO_WritePin(redPort[0], redPin[0], GPIO_PIN_RESET);
	HAL_GPIO_WritePin(greenPort[0], greenPin[0], GPIO_PIN_SET);
	HAL_GPIO_WritePin(yellowPort[0], yellowPin[0], GPIO_PIN_SET);
	HAL_GPIO_WritePin(redPort[1], redPin[1], GPIO_PIN_SET);
	HAL_GPIO_WritePin(greenPort[1], greenPin[1], GPIO_PIN_RESET);
	HAL_GPIO_WritePin(yellowPort[1], yellowPin[1], GPIO_PIN_SET);
}

void traffic_light_fsm()
{
	led_7seg_values[0] = roadCounter[0] / 10;
	led_7seg_values[1] = roadCounter[0] % 10;
	led_7seg_values[2] = roadCounter[1] / 10;
	led_7seg_values[3] = roadCounter[1] % 10;

	switch (roadState[0])
	{
	case RED:
		HAL_GPIO_WritePin(redPort[0], redPin[0], GPIO_PIN_RESET);
		if (is_timer_traffic1_flagged())
		{
			--roadCounter[0];
			if (roadCounter[0] <= 0)
			{
				roadState[0] = GREEN;
				HAL_GPIO_WritePin(redPort[0], redPin[0], GPIO_PIN_SET);
				HAL_GPIO_WritePin(greenPort[0], greenPin[0], GPIO_PIN_RESET);
				roadCounter[0] = green_duration;
			}
			set_timer_traffic1(TRAFFIC_DURATION);
		}
		break;
	case GREEN:
		HAL_GPIO_WritePin(greenPort[0], greenPin[0], GPIO_PIN_RESET);
		if (is_timer_traffic1_flagged())
		{
			--roadCounter[0];
			if (roadCounter[0] <= 0)
			{
				roadState[0] = YELLOW;
				HAL_GPIO_WritePin(greenPort[0], greenPin[0], GPIO_PIN_SET);
				HAL_GPIO_WritePin(yellowPort[0], yellowPin[0], GPIO_PIN_RESET);
				roadCounter[0] = yellow_duration;
			}
			set_timer_traffic1(TRAFFIC_DURATION);
		}
		break;
	case YELLOW:
		HAL_GPIO_WritePin(yellowPort[0], yellowPin[0], GPIO_PIN_RESET);
		if (is_timer_traffic1_flagged())
		{
			--roadCounter[0];
			if (roadCounter[0] <= 0)
			{
				roadState[0] = RED;
				HAL_GPIO_WritePin(yellowPort[0], yellowPin[0], GPIO_PIN_SET);
				HAL_GPIO_WritePin(redPort[0], redPin[0], GPIO_PIN_RESET);
				roadCounter[0] = red_duration;
			}
			set_timer_traffic1(TRAFFIC_DURATION);
		}
		break;
	}

	switch (roadState[1])
	{
	case RED:
		HAL_GPIO_WritePin(redPort[1], redPin[1], GPIO_PIN_RESET);
		if (is_timer_traffic2_flagged())
		{
			--roadCounter[1];
			if (roadCounter[1] <= 0)
			{
				roadState[1] = GREEN;
				HAL_GPIO_WritePin(redPort[1], redPin[1], GPIO_PIN_SET);
				HAL_GPIO_WritePin(greenPort[1], greenPin[1], GPIO_PIN_RESET);
				roadCounter[1] = green_duration;
			}
			set_timer_traffic2(TRAFFIC_DURATION);
		}
		break;
	case GREEN:
		HAL_GPIO_WritePin(greenPort[1], greenPin[1], GPIO_PIN_RESET);
		if (is_timer_traffic2_flagged())
		{
			--roadCounter[1];
			if (roadCounter[1] <= 0)
			{
				roadState[1] = YELLOW;
				HAL_GPIO_WritePin(greenPort[1], greenPin[1], GPIO_PIN_SET);
				HAL_GPIO_WritePin(yellowPort[1], yellowPin[1], GPIO_PIN_RESET);
				roadCounter[1] = yellow_duration;
			}
			set_timer_traffic2(TRAFFIC_DURATION);
		}
		break;
	case YELLOW:
		HAL_GPIO_WritePin(yellowPort[1], yellowPin[1], GPIO_PIN_RESET);
		if (is_timer_traffic2_flagged())
		{
			--roadCounter[1];
			if (roadCounter[1] <= 0)
			{
				roadState[1] = RED;
				HAL_GPIO_WritePin(yellowPort[1], yellowPin[1], GPIO_PIN_SET);
				HAL_GPIO_WritePin(redPort[0], redPin[1], GPIO_PIN_RESET);
				roadCounter[1] = red_duration;
			}
			set_timer_traffic2(TRAFFIC_DURATION);
		}
		break;
	}
}

void blink_led(enum TrafficLightState mode_color)
{
	led_7seg_values[0] = 0;

	switch (mode_color)
	{
	case RED:
		led_7seg_values[1] = 2;
		led_7seg_values[2] = red_duration / 10;
		led_7seg_values[3] = red_duration % 10;
		if (is_timer_blink_flagged())
		{
			HAL_GPIO_TogglePin(redPort[0], redPin[0]);
			HAL_GPIO_TogglePin(redPort[1], redPin[1]);
			set_timer_blink(BLINK_DURATION);
		}
		break;
	case GREEN:
		led_7seg_values[1] = 3;
		led_7seg_values[2] = green_duration / 10;
		led_7seg_values[3] = green_duration % 10;
		if (is_timer_blink_flagged())
		{
			HAL_GPIO_TogglePin(greenPort[0], greenPin[0]);
			HAL_GPIO_TogglePin(greenPort[1], greenPin[1]);
			set_timer_blink(BLINK_DURATION);
		}
		break;
	case YELLOW:
		led_7seg_values[1] = 4;
		led_7seg_values[2] = yellow_duration / 10;
		led_7seg_values[3] = yellow_duration % 10;
		if (is_timer_blink_flagged())
		{
			HAL_GPIO_TogglePin(yellowPort[0], yellowPin[0]);
			HAL_GPIO_TogglePin(yellowPort[1], yellowPin[1]);
			set_timer_blink(BLINK_DURATION);
		}
		break;
	}
}

void led7_scanning()
{
	display7SEG(led_7seg_values[led7_status]);
	switch (led7_status)
	{
	case 0:
		if (is_timer_7seg_scan_flagged())
		{
			HAL_GPIO_WritePin(EN_7SEG1_TEN_GPIO_Port, EN_7SEG1_TEN_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(EN_7SEG1_UNIT_GPIO_Port, EN_7SEG1_UNIT_Pin, GPIO_PIN_RESET);
			led7_status = 1;
			set_timer_7seg_scan(SCANNING_DURATION);
		}
		break;
	case 1:
		if (is_timer_7seg_scan_flagged())
		{
			HAL_GPIO_WritePin(EN_7SEG1_UNIT_GPIO_Port, EN_7SEG1_UNIT_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(EN_7SEG2_TEN_GPIO_Port, EN_7SEG2_TEN_Pin, GPIO_PIN_RESET);
			led7_status = 2;
			set_timer_7seg_scan(SCANNING_DURATION);
		}
		break;
	case 2:
		if (is_timer_7seg_scan_flagged())
		{
			HAL_GPIO_WritePin(EN_7SEG2_TEN_GPIO_Port, EN_7SEG2_TEN_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(EN_7SEG2_UNIT_GPIO_Port, EN_7SEG2_UNIT_Pin, GPIO_PIN_RESET);
			led7_status = 3;
			set_timer_7seg_scan(SCANNING_DURATION);
		}
		break;
	case 3:
		if (is_timer_7seg_scan_flagged())
		{
			HAL_GPIO_WritePin(EN_7SEG2_UNIT_GPIO_Port, EN_7SEG2_UNIT_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(EN_7SEG1_TEN_GPIO_Port, EN_7SEG1_TEN_Pin, GPIO_PIN_RESET);
			led7_status = 0;
			set_timer_7seg_scan(SCANNING_DURATION);
		}
		break;
	default:
		break;
	}
}

void blink_led_clear()
{
	HAL_GPIO_WritePin(yellowPort[0], yellowPin[0], GPIO_PIN_SET);
	HAL_GPIO_WritePin(greenPort[0], greenPin[0], GPIO_PIN_SET);
	HAL_GPIO_WritePin(redPort[0], redPin[0], GPIO_PIN_SET);
	HAL_GPIO_WritePin(yellowPort[1], yellowPin[1], GPIO_PIN_SET);
	HAL_GPIO_WritePin(greenPort[1], greenPin[1], GPIO_PIN_SET);
	HAL_GPIO_WritePin(redPort[1], redPin[1], GPIO_PIN_SET);
	set_timer_blink(BLINK_DURATION);
}

void display7SEG(uint8_t led_number)
{
	switch (led_number)
	{
	case 0:
		HAL_GPIO_WritePin(LED7SEG_1_GPIO_Port, LED7SEG_1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_2_GPIO_Port, LED7SEG_2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_3_GPIO_Port, LED7SEG_3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_4_GPIO_Port, LED7SEG_4_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_5_GPIO_Port, LED7SEG_5_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_6_GPIO_Port, LED7SEG_6_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_7_GPIO_Port, LED7SEG_7_Pin, GPIO_PIN_SET);
		break;
	case 1:
		HAL_GPIO_WritePin(LED7SEG_1_GPIO_Port, LED7SEG_1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED7SEG_2_GPIO_Port, LED7SEG_2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_3_GPIO_Port, LED7SEG_3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_4_GPIO_Port, LED7SEG_4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED7SEG_5_GPIO_Port, LED7SEG_5_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED7SEG_6_GPIO_Port, LED7SEG_6_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED7SEG_7_GPIO_Port, LED7SEG_7_Pin, GPIO_PIN_SET);
		break;
	case 2:
		HAL_GPIO_WritePin(LED7SEG_1_GPIO_Port, LED7SEG_1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_2_GPIO_Port, LED7SEG_2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_3_GPIO_Port, LED7SEG_3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED7SEG_4_GPIO_Port, LED7SEG_4_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_5_GPIO_Port, LED7SEG_5_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_6_GPIO_Port, LED7SEG_6_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED7SEG_7_GPIO_Port, LED7SEG_7_Pin, GPIO_PIN_RESET);
		break;
	case 3:
		HAL_GPIO_WritePin(LED7SEG_1_GPIO_Port, LED7SEG_1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_2_GPIO_Port, LED7SEG_2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_3_GPIO_Port, LED7SEG_3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_4_GPIO_Port, LED7SEG_4_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_5_GPIO_Port, LED7SEG_5_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED7SEG_6_GPIO_Port, LED7SEG_6_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED7SEG_7_GPIO_Port, LED7SEG_7_Pin, GPIO_PIN_RESET);
		break;
	case 4:
		HAL_GPIO_WritePin(LED7SEG_1_GPIO_Port, LED7SEG_1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED7SEG_2_GPIO_Port, LED7SEG_2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_3_GPIO_Port, LED7SEG_3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_4_GPIO_Port, LED7SEG_4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED7SEG_5_GPIO_Port, LED7SEG_5_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED7SEG_6_GPIO_Port, LED7SEG_6_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_7_GPIO_Port, LED7SEG_7_Pin, GPIO_PIN_RESET);
		break;
	case 5:
		HAL_GPIO_WritePin(LED7SEG_1_GPIO_Port, LED7SEG_1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_2_GPIO_Port, LED7SEG_2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED7SEG_3_GPIO_Port, LED7SEG_3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_4_GPIO_Port, LED7SEG_4_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_5_GPIO_Port, LED7SEG_5_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED7SEG_6_GPIO_Port, LED7SEG_6_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_7_GPIO_Port, LED7SEG_7_Pin, GPIO_PIN_RESET);
		break;
	case 6:
		HAL_GPIO_WritePin(LED7SEG_1_GPIO_Port, LED7SEG_1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_2_GPIO_Port, LED7SEG_2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED7SEG_3_GPIO_Port, LED7SEG_3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_4_GPIO_Port, LED7SEG_4_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_5_GPIO_Port, LED7SEG_5_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_6_GPIO_Port, LED7SEG_6_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_7_GPIO_Port, LED7SEG_7_Pin, GPIO_PIN_RESET);
		break;
	case 7:
		HAL_GPIO_WritePin(LED7SEG_1_GPIO_Port, LED7SEG_1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_2_GPIO_Port, LED7SEG_2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_3_GPIO_Port, LED7SEG_3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_4_GPIO_Port, LED7SEG_4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED7SEG_5_GPIO_Port, LED7SEG_5_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED7SEG_6_GPIO_Port, LED7SEG_6_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED7SEG_7_GPIO_Port, LED7SEG_7_Pin, GPIO_PIN_SET);
		break;
	case 8:
		HAL_GPIO_WritePin(LED7SEG_1_GPIO_Port, LED7SEG_1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_2_GPIO_Port, LED7SEG_2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_3_GPIO_Port, LED7SEG_3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_4_GPIO_Port, LED7SEG_4_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_5_GPIO_Port, LED7SEG_5_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_6_GPIO_Port, LED7SEG_6_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_7_GPIO_Port, LED7SEG_7_Pin, GPIO_PIN_RESET);
		break;
	case 9:
		HAL_GPIO_WritePin(LED7SEG_1_GPIO_Port, LED7SEG_1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_2_GPIO_Port, LED7SEG_2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_3_GPIO_Port, LED7SEG_3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_4_GPIO_Port, LED7SEG_4_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_5_GPIO_Port, LED7SEG_5_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED7SEG_6_GPIO_Port, LED7SEG_6_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED7SEG_7_GPIO_Port, LED7SEG_7_Pin, GPIO_PIN_RESET);
		break;
	}
}
