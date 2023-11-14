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

uint16_t timer7SegScanCounter = 0;
uint8_t timer7SegScanFlag = 0;

uint16_t timerTraffic1Counter = 0;
uint8_t timerTraffic1Flag = 0;
uint16_t timerTraffic2Counter = 0;
uint8_t timerTraffic2Flag = 0;

uint16_t timerAutoIncreaseCounter = 0;
uint8_t timerAutoIncreaseFlag = 0;

void set_timer_blink(uint16_t duration)
{
	timerBlinkCounter = duration / TIME_UNIT;
	timerBlinkFlag = 0;
}

uint8_t is_timer_blink_flagged()
{
	return timerBlinkFlag;
}

void timer_blink_run()
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

uint8_t is_timer_btn_reading_flagged()
{
	return timerBtnReadingFlag;
}

void timer_btn_reading_run()
{
	--timerBtnReadingCounter;
	if (timerBtnReadingCounter <= 0)
	{
		timerBtnReadingFlag = 1;
	}
}

void set_timer_7seg_scan(uint16_t duration)
{
	timer7SegScanCounter = duration / TIME_UNIT;
	timer7SegScanFlag = 0;
}

uint8_t is_timer_7seg_scan_flagged()
{
	return timer7SegScanFlag;
}

void timer_7seg_scan_run()
{
	--timer7SegScanCounter;
	if (timer7SegScanCounter <= 0)
	{
		timer7SegScanFlag = 1;
	}
}

void set_timer_traffic1(uint16_t duration)
{
	timerTraffic1Counter = duration / TIME_UNIT;
	timerTraffic1Flag = 0;
}

uint8_t is_timer_traffic1_flagged()
{
	return timerTraffic1Flag;
}

void timer_traffic1_run()
{
	--timerTraffic1Counter;
	if (timerTraffic1Counter <= 0)
	{
		timerTraffic1Flag = 1;
	}
}

void set_timer_traffic2(uint16_t duration)
{
	timerTraffic2Counter = duration / TIME_UNIT;
	timerTraffic2Flag = 0;
}

uint8_t is_timer_traffic2_flagged()
{
	return timerTraffic2Flag;
}

void timer_traffic2_run()
{
	--timerTraffic2Counter;
	if (timerTraffic2Counter <= 0)
	{
		timerTraffic2Flag = 1;
	}
}

void set_timer_auto_increase(uint16_t duration)
{
	timerAutoIncreaseCounter = duration / TIME_UNIT;
	timerAutoIncreaseFlag = 0;
}

void timer_auto_increase_run()
{
	--timerAutoIncreaseCounter;
	if (timerAutoIncreaseCounter <= 0)
	{
		timerAutoIncreaseFlag = 1;
	}
}

uint8_t is_timer_auto_increase_flagged()
{
	return timerAutoIncreaseFlag;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim)
{
	if (htim->Instance == TIM2)
	{
		timer_7seg_scan_run();
		timer_btn_reading_run();
		timer_traffic1_run();;
		timer_traffic2_run();
		timer_blink_run();
		timer_auto_increase_run();
	}
}

