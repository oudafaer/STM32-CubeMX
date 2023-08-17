/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId Init_TaskHandle;
osThreadId LED_TaskHandle;
osThreadId LCD_TaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void Init_Function(void const * argument);
void LED_Function(void const * argument);
void LCD_Function(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of Init_Task */
  osThreadDef(Init_Task, Init_Function, osPriorityHigh, 0, 128);
  Init_TaskHandle = osThreadCreate(osThread(Init_Task), NULL);

  /* definition and creation of LED_Task */
  osThreadDef(LED_Task, LED_Function, osPriorityIdle, 0, 128);
  LED_TaskHandle = osThreadCreate(osThread(LED_Task), NULL);

  /* definition and creation of LCD_Task */
  osThreadDef(LCD_Task, LCD_Function, osPriorityNormal, 0, 128);
  LCD_TaskHandle = osThreadCreate(osThread(LCD_Task), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_Init_Function */
/**
  * @brief  Function implementing the Init_Task thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Init_Function */
void Init_Function(void const * argument)
{
  /* USER CODE BEGIN Init_Function */
  /* Infinite loop */
  for(;;)
  {
		TFTLCD_Init();
		LCD_Clear(GREEN);
		LCD_ShowString(30,40,210,24,24,(uint8_t*)"WHAT A DASDA");
		vTaskDelete(NULL);
    osDelay(1);
  }
  /* USER CODE END Init_Function */
}

/* USER CODE BEGIN Header_LED_Function */
/**
* @brief Function implementing the LED_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_LED_Function */
void LED_Function(void const * argument)
{
  /* USER CODE BEGIN LED_Function */
  /* Infinite loop */
  for(;;)
  {
		HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
    osDelay(500);
  }
  /* USER CODE END LED_Function */
}

/* USER CODE BEGIN Header_LCD_Function */
/**
* @brief Function implementing the LCD_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_LCD_Function */
void LCD_Function(void const * argument)
{
  /* USER CODE BEGIN LCD_Function */
  /* Infinite loop */
  for(;;)
  {
		
    osDelay(1);
  }
  /* USER CODE END LCD_Function */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

