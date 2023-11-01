/*
 * led_display.c
 *
 *  Created on: Oct 6, 2023
 *      Author: ADMIN
 */

#include "led_display.h"

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
