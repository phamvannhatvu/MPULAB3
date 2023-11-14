/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
enum SystemState
{
	NORMAL_MODE,
	NORMAL_MODE_PRESSED,
	MODIFY_RED,
	UPDATE_RED_COUNTER,
	AUTO_UPDATE_RED_COUTER,
	MODIFY_RED_PRESSED,
	MODIFY_GREEN,
	UPDATE_GREEN_COUNTER,
	AUTO_UPDATE_GREEN_COUTER,
	MODIFY_GREEN_PRESSED,
	MODIFY_YELLOW,
	UPDATE_YELLOW_COUNTER,
	AUTO_UPDATE_YELLOW_COUTER,
	MODIFY_YELLOW_PRESSED,
	NORMAL_MODE_RETURN_PRESSED
};

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define AUTO_INCREASE_DURATION 500
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;
uint8_t red_duration = 5;
uint8_t green_duration = 3;
uint8_t yellow_duration = 2;
uint8_t duration_temp;
/* USER CODE BEGIN PV */
//used to detect the previous state when the "normal mode return" button is pressed
enum SystemState preState = NORMAL_MODE;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */
void init_leds(void);
uint8_t get_system_mode(enum SystemState);
void init_timers(void);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  HAL_TIM_Base_Start_IT(&htim2);
  init_leds();
  init_button_state();
  init_button();
  init_timers();
  traffic_light_reset();

  enum SystemState systemState = NORMAL_MODE;
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  //Read button every 10ms
	  if (is_timer_btn_reading_flagged())
	  {
		  button_reading();
		  set_timer_btn_reading(10);
	  }

	  //Update the state of "select mode" button (index 0)
	  //This button does not support auto-increment while holding
	  not_auto_increase_btn_fsm(0);
	  enum ButtonState selectModeButton = get_button_state(0);

	  //Update the state of "modify cycle" button (index 1)
	  auto_increase_btn_fsm(1);
	  enum ButtonState modifyCycleButton = get_button_state(1);

	  //Update the state of "normal mode return" button (index 2)
	  //This button does not support auto-increment while holding
	  not_auto_increase_btn_fsm(2);
	  enum ButtonState normalModeReturnButton = get_button_state(2);

	  //FSM for the entire system
	  switch (systemState)
	  {
	  case NORMAL_MODE:
		  traffic_light_fsm();
		  if (selectModeButton == BUTTON_PRESSED)
		  {
			  systemState = NORMAL_MODE_PRESSED;
		  }
		  break;
	  case NORMAL_MODE_PRESSED:
		  traffic_light_fsm();
		  if (selectModeButton == BUTTON_RELEASED)
		  {
			  systemState = MODIFY_RED;
			  blink_led_clear();
			  duration_temp = red_duration;
		  }
		  break;
	  case MODIFY_RED:
		  blink_led(RED);
		  if (selectModeButton == BUTTON_PRESSED)
		  {
			  systemState = MODIFY_RED_PRESSED;
		  }
		  if (modifyCycleButton == BUTTON_PRESSED)
		  {
			  systemState = UPDATE_RED_COUNTER;
		  }
		  if (normalModeReturnButton == BUTTON_PRESSED)
		  {
			  preState = systemState;
			  systemState = NORMAL_MODE_RETURN_PRESSED;
		  }
		  break;
	  case UPDATE_RED_COUNTER:
		  blink_led(RED);
		  if (modifyCycleButton == BUTTON_RELEASED)
		  {
			  ++duration_temp;
			  systemState = MODIFY_RED;
		  }
		  if (modifyCycleButton == BUTTON_PRESSED_MORE_THAN_1_SECOND)
		  {
			  set_timer_auto_increase(AUTO_INCREASE_DURATION);
			  systemState = AUTO_UPDATE_RED_COUTER;
		  }
		  break;
	  case AUTO_UPDATE_RED_COUTER:
		  blink_led(RED);
		  if (modifyCycleButton == BUTTON_RELEASED)
		  {
			  systemState = MODIFY_RED;
		  }
		  if (is_timer_auto_increase_flagged())
		  {
			  ++duration_temp;
			  set_timer_auto_increase(AUTO_INCREASE_DURATION);
		  }
		  break;
	  case MODIFY_RED_PRESSED:
		  blink_led(RED);
		  if (selectModeButton == BUTTON_RELEASED)
		  {
			  systemState = MODIFY_GREEN;
			  blink_led_clear();
			  duration_temp = green_duration;
		  }
		  break;
	  case MODIFY_GREEN:
		  blink_led(GREEN);
		  if (selectModeButton == BUTTON_PRESSED)
		  {
			  systemState = MODIFY_GREEN_PRESSED;
		  }
		  if (modifyCycleButton == BUTTON_PRESSED)
		  {
			  systemState = UPDATE_GREEN_COUNTER;
		  }
		  if (normalModeReturnButton == BUTTON_PRESSED)
		  {
			  preState = systemState;
			  systemState = NORMAL_MODE_RETURN_PRESSED;
		  }
		  break;
	  case UPDATE_GREEN_COUNTER:
		  blink_led(GREEN);
		  if (modifyCycleButton == BUTTON_RELEASED)
		  {
			  ++duration_temp;
			  systemState = MODIFY_GREEN;
		  }
		  if (modifyCycleButton == BUTTON_PRESSED_MORE_THAN_1_SECOND)
		  {
			  set_timer_auto_increase(AUTO_INCREASE_DURATION);
			  systemState = AUTO_UPDATE_GREEN_COUTER;
		  }
		  break;
	  case AUTO_UPDATE_GREEN_COUTER:
		  blink_led(GREEN);
		  if (modifyCycleButton == BUTTON_RELEASED)
		  {
			  systemState = MODIFY_GREEN;
		  }
		  if (is_timer_auto_increase_flagged())
		  {
			  ++duration_temp;
			  set_timer_auto_increase(AUTO_INCREASE_DURATION);
		  }
		  break;
	  case MODIFY_GREEN_PRESSED:
		  blink_led(GREEN);
		  if (selectModeButton == BUTTON_RELEASED)
		  {
			  systemState = MODIFY_YELLOW;
			  blink_led_clear();
			  duration_temp = yellow_duration;
		  }
		  break;
	  case MODIFY_YELLOW:
		  blink_led(YELLOW);
		  if (selectModeButton == BUTTON_PRESSED)
		  {
			  systemState = MODIFY_YELLOW_PRESSED;
		  }
		  if (modifyCycleButton == BUTTON_PRESSED)
		  {
			  systemState = UPDATE_YELLOW_COUNTER;
		  }
		  if (normalModeReturnButton == BUTTON_PRESSED)
		  {
			  preState = systemState;
			  systemState = NORMAL_MODE_RETURN_PRESSED;
		  }
		  break;
	  case UPDATE_YELLOW_COUNTER:
		  blink_led(YELLOW);
		  if (modifyCycleButton == BUTTON_RELEASED)
		  {
			  ++duration_temp;
			  systemState = MODIFY_YELLOW;
		  }
		  if (modifyCycleButton == BUTTON_PRESSED_MORE_THAN_1_SECOND)
		  {
			  set_timer_auto_increase(AUTO_INCREASE_DURATION);
			  systemState = AUTO_UPDATE_YELLOW_COUTER;
		  }
		  break;
	  case AUTO_UPDATE_YELLOW_COUTER:
		  blink_led(YELLOW);
		  if (modifyCycleButton == BUTTON_RELEASED)
		  {
			  systemState = MODIFY_YELLOW;
		  }
		  if (is_timer_auto_increase_flagged())
		  {
			  ++duration_temp;
			  set_timer_auto_increase(AUTO_INCREASE_DURATION);
		  }
		  break;
	  case MODIFY_YELLOW_PRESSED:
		  blink_led(YELLOW);
		  if (selectModeButton == BUTTON_RELEASED)
		  {
			  systemState = NORMAL_MODE;
			  traffic_light_reset();
		  }
		  break;
	  case NORMAL_MODE_RETURN_PRESSED:
		  switch (preState)
		  {
		  case MODIFY_RED:
			  blink_led(RED);
			  break;
		  case MODIFY_GREEN:
			  blink_led(GREEN);
			  break;
		  case MODIFY_YELLOW:
			  blink_led(YELLOW);
			  break;
		  default:
			  break;
		  }
		  if (normalModeReturnButton == BUTTON_RELEASED)
		  {
			  systemState = NORMAL_MODE;
			  switch (preState)
			  {
			  case MODIFY_RED:
				  red_duration = duration_temp;
				  break;
			  case MODIFY_GREEN:
				  green_duration = duration_temp;
				  break;
			  case MODIFY_YELLOW:
				  yellow_duration = duration_temp;
				  break;
			  default:
				  break;
			  }
			  traffic_light_reset();
		  }
		  break;
	  }

	  led7_scanning();
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED7SEG_1_Pin|LED7SEG_2_Pin|LED7SEG_3_Pin|LED7SEG_4_Pin
                          |LED7SEG_5_Pin|LED7SEG_6_Pin|LED7SEG_7_Pin|EN_7SEG1_TEN_Pin
                          |EN_7SEG1_UNIT_Pin|EN_7SEG2_TEN_Pin|EN_7SEG2_UNIT_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED1_RED_Pin|LED1_GREEN_Pin|LED1_YELLOW_Pin|LED2_RED_Pin
                          |LED2_GREEN_Pin|LED2_YELLOW_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED7SEG_1_Pin LED7SEG_2_Pin LED7SEG_3_Pin LED7SEG_4_Pin
                           LED7SEG_5_Pin LED7SEG_6_Pin LED7SEG_7_Pin EN_7SEG1_TEN_Pin
                           EN_7SEG1_UNIT_Pin EN_7SEG2_TEN_Pin EN_7SEG2_UNIT_Pin */
  GPIO_InitStruct.Pin = LED7SEG_1_Pin|LED7SEG_2_Pin|LED7SEG_3_Pin|LED7SEG_4_Pin
                          |LED7SEG_5_Pin|LED7SEG_6_Pin|LED7SEG_7_Pin|EN_7SEG1_TEN_Pin
                          |EN_7SEG1_UNIT_Pin|EN_7SEG2_TEN_Pin|EN_7SEG2_UNIT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LED1_RED_Pin LED1_GREEN_Pin LED1_YELLOW_Pin LED2_RED_Pin
                           LED2_GREEN_Pin LED2_YELLOW_Pin */
  GPIO_InitStruct.Pin = LED1_RED_Pin|LED1_GREEN_Pin|LED1_YELLOW_Pin|LED2_RED_Pin
                          |LED2_GREEN_Pin|LED2_YELLOW_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : SELECT_MODE_BTN_Pin MODIFY_CYCLE_BTN_Pin SET_VALUE_BTN_Pin */
  GPIO_InitStruct.Pin = SELECT_MODE_BTN_Pin|MODIFY_CYCLE_BTN_Pin|SET_VALUE_BTN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
uint8_t get_system_mode(enum SystemState systemState)
{
	switch (systemState)
	{
	case NORMAL_MODE:
	case NORMAL_MODE_PRESSED:
		return 1;
	case MODIFY_RED:
	case MODIFY_RED_PRESSED:
		return 2;
	case MODIFY_GREEN:
	case MODIFY_GREEN_PRESSED:
		return 3;
	case MODIFY_YELLOW:
	case MODIFY_YELLOW_PRESSED:
		return 4;
	case NORMAL_MODE_RETURN_PRESSED:
		return 0;
	}

	return 5;//invalid mode
}

void init_leds()
{
	HAL_GPIO_WritePin(EN_7SEG1_TEN_GPIO_Port, EN_7SEG1_TEN_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(EN_7SEG1_UNIT_GPIO_Port, EN_7SEG1_UNIT_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(EN_7SEG2_TEN_GPIO_Port, EN_7SEG2_TEN_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(EN_7SEG2_UNIT_GPIO_Port, EN_7SEG2_UNIT_Pin, GPIO_PIN_SET);

	HAL_GPIO_WritePin(LED1_RED_GPIO_Port, LED1_RED_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED1_GREEN_GPIO_Port, LED1_GREEN_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED1_YELLOW_GPIO_Port, LED1_YELLOW_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED2_RED_GPIO_Port, LED2_RED_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED2_GREEN_GPIO_Port, LED2_GREEN_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED2_YELLOW_GPIO_Port, LED2_YELLOW_Pin, GPIO_PIN_SET);
}

void init_timers()
{
	set_timer_btn_reading(10);
	set_timer_7seg_scan(SCANNING_DURATION);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
