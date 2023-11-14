/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "input_processing.h"
#include "led_display.h"
#include "timer.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
extern uint8_t red_duration;
extern uint8_t green_duration;
extern uint8_t yellow_duration;
extern uint8_t duration_temp;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void increase_led(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED7SEG_1_Pin GPIO_PIN_1
#define LED7SEG_1_GPIO_Port GPIOA
#define LED7SEG_2_Pin GPIO_PIN_2
#define LED7SEG_2_GPIO_Port GPIOA
#define LED7SEG_3_Pin GPIO_PIN_3
#define LED7SEG_3_GPIO_Port GPIOA
#define LED7SEG_4_Pin GPIO_PIN_4
#define LED7SEG_4_GPIO_Port GPIOA
#define LED7SEG_5_Pin GPIO_PIN_5
#define LED7SEG_5_GPIO_Port GPIOA
#define LED7SEG_6_Pin GPIO_PIN_6
#define LED7SEG_6_GPIO_Port GPIOA
#define LED7SEG_7_Pin GPIO_PIN_7
#define LED7SEG_7_GPIO_Port GPIOA
#define LED1_RED_Pin GPIO_PIN_0
#define LED1_RED_GPIO_Port GPIOB
#define LED1_GREEN_Pin GPIO_PIN_1
#define LED1_GREEN_GPIO_Port GPIOB
#define LED1_YELLOW_Pin GPIO_PIN_2
#define LED1_YELLOW_GPIO_Port GPIOB
#define EN_7SEG1_TEN_Pin GPIO_PIN_8
#define EN_7SEG1_TEN_GPIO_Port GPIOA
#define EN_7SEG1_UNIT_Pin GPIO_PIN_9
#define EN_7SEG1_UNIT_GPIO_Port GPIOA
#define EN_7SEG2_TEN_Pin GPIO_PIN_10
#define EN_7SEG2_TEN_GPIO_Port GPIOA
#define EN_7SEG2_UNIT_Pin GPIO_PIN_11
#define EN_7SEG2_UNIT_GPIO_Port GPIOA
#define SELECT_MODE_BTN_Pin GPIO_PIN_12
#define SELECT_MODE_BTN_GPIO_Port GPIOA
#define MODIFY_CYCLE_BTN_Pin GPIO_PIN_13
#define MODIFY_CYCLE_BTN_GPIO_Port GPIOA
#define SET_VALUE_BTN_Pin GPIO_PIN_14
#define SET_VALUE_BTN_GPIO_Port GPIOA
#define LED2_RED_Pin GPIO_PIN_3
#define LED2_RED_GPIO_Port GPIOB
#define LED2_GREEN_Pin GPIO_PIN_4
#define LED2_GREEN_GPIO_Port GPIOB
#define LED2_YELLOW_Pin GPIO_PIN_5
#define LED2_YELLOW_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
