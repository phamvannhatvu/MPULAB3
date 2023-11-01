/*
 * timer.c
 *
 *  Created on: Oct 6, 2023
 *      Author: ADMIN
 */

#include "timer.h"

//uint16_t timerAutoIncreaseCounter = 0;
//uint8_t timerAutoIncreaseFlag = 0;
uint16_t timerBlinkCounter = 0;
uint8_t timerBlinkFlag = 0;

//void set_timer_auto_increase(uint16_t duration)
//{
//	timerAutoIncreaseCounter = duration / TIME_UNIT;
//	timerAutoIncreaseFlag = 0;
//}

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

//void timer_auto_increase_run(void)
//{
//	--timerAutoIncreaseCounter;
//	if (timerAutoIncreaseCounter <= 0)
//	{
//		timerAutoIncreaseFlag = 1;
//	}
//}
//
//uint8_t is_flagged_timer_auto_increase(void)
//{
//	return timerAutoIncreaseFlag;
//}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim)
{
	if (htim->Instance == TIM2)
	{
//		timer_auto_increase_run();
		timer_blink_run();
//		button_reading();
	}
}

