/*
 * timer.c
 *
 *  Created on: Oct 6, 2023
 *      Author: ADMIN
 */

#include "timer.h"

uint16_t timerBtnReadingCounter = 0;
uint8_t timerBtnReadingFlag = 0;
uint16_t timerBlinkCounter = 0;
uint8_t timerBlinkFlag = 0;

void set_timer_blink(uint16_t duration)
{
	timerBlinkCounter = duration / TIME_UNIT;
	timerBlinkFlag = 0;
}

uint8_t is_timer_blink_flagged()
{
	return timerBlinkFlag;
}

void timer_blink_run(void)
{
	--timerBlinkCounter;
	if (timerBlinkCounter <= 0)
	{
		timerBlinkFlag = 1;
	}
}

void set_timer_btn_reading(uint16_t duration)
{
	timerBtnReadingCounter = duration / TIME_UNIT;
	timerBtnReadingFlag = 0;
}

uint8_t is_timer_btn_reading_flagged(void)
{
	return timerBtnReadingFlag;
}

void timer_btn_reading_run(void)
{
	--timerBtnReadingCounter;
	if (timerBtnReadingCounter <= 0)
	{
		timerBtnReadingFlag = 1;
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim)
{
	if (htim->Instance == TIM2)
	{
		timer_blink_run();
		timer_btn_reading_run();
	}
}

