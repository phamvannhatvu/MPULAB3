/*
 * timer.c
 *
 *  Created on: Oct 6, 2023
 *      Author: ADMIN
 */

#include "timer.h"

#define TIME_UNIT 10 //in ms

uint16_t timerAutoIncreaseCounter = 0;
uint8_t timerAutoIncreaseFlag = 0;
uint16_t timerLedTestCounter = 0;
uint8_t timerLedTestFlag = 0;

void set_timer_auto_increase(uint16_t duration)
{
	timerAutoIncreaseCounter = duration / TIME_UNIT;
	timerAutoIncreaseFlag = 0;
}

void set_led_test(uint16_t duration)
{
	timerLedTestCounter = duration / TIME_UNIT;
	timerLedTestFlag = 0;
}

void led_test_run(void)
{
	--timerLedTestCounter;
	if (timerLedTestCounter <= 0)
	{
		timerLedTestFlag = 1;
	}
}

void timer_auto_increase_run(void)
{
	--timerAutoIncreaseCounter;
	if (timerAutoIncreaseCounter <= 0)
	{
		timerAutoIncreaseFlag = 1;
	}
}

uint8_t is_flagged_timer_auto_increase(void)
{
	return timerAutoIncreaseFlag;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim)
{
	if (htim->Instance == TIM2)
	{
		timer_auto_increase_run();
//		led_test_run();
		button_reading();
	}
}

