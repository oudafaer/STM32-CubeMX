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
uint16_t ADC_Value=0,ADC_Volt=0;
uint8_t str_buff[64];
uint8_t adc_mark=0;
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
osThreadId ADC_TaskHandle;
osThreadId Init_TaskHandle;
osThreadId LED_TaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void ADC_Function(void const * argument);
void Init_Function(void const * argument);
void LED_Function(void const * argument);

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
  /* definition and creation of ADC_Task */
  osThreadDef(ADC_Task, ADC_Function, osPriorityNormal, 0, 256);
  ADC_TaskHandle = osThreadCreate(osThread(ADC_Task), NULL);

  /* definition and creation of Init_Task */
  osThreadDef(Init_Task, Init_Function, osPriorityHigh, 0, 128);
  Init_TaskHandle = osThreadCreate(osThread(Init_Task), NULL);

  /* definition and creation of LED_Task */
  osThreadDef(LED_Task, LED_Function, osPriorityIdle, 0, 128);
  LED_TaskHandle = osThreadCreate(osThread(LED_Task), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_ADC_Function */
/**
  * @brief  Function implementing the ADC_Task thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_ADC_Function */
void ADC_Function(void const * argument)
{
	uint16_t angle_get;										//角度值保存														
  uint16_t volage_get;										//电压值保存			
  /* USER CODE BEGIN ADC_Function */
  /* Infinite loop */
  for(;;)
  {
		HAL_Delay(500);
		volage_get = ADC_Get_Average(1);							//读取电压值	   						
		volage_get = volage_get*3.3*100/4096;					//转换电压，扩大100倍					
		angle_get = ADC_Get_Average(0);					        //读取ADC值    			
		my_printf(1,"电压值（A1）：%d.%d,采样值（A0):%d\r\n",volage_get/100,volage_get%100,angle_get);
		
  }
  /* USER CODE END ADC_Function */
}

/* USER CODE BEGIN Header_Init_Function */
/**
* @brief Function implementing the Init_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Init_Function */
void Init_Function(void const * argument)
{
  /* USER CODE BEGIN Init_Function */
  /* Infinite loop */
  for(;;)
  {
		taskENTER_CRITICAL(); //进入临界区
		vTaskDelete(NULL);
		
		HAL_ADCEx_Calibration_Start(&hadc1);					//校准ADC1	
		
    osDelay(1);
		taskEXIT_CRITICAL();            //退出临界区
		
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
//	osThreadSuspend(LED_TaskHandle);
  /* Infinite loop */
  for(;;)
  {

		HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_5);
		HAL_Delay(600);
  }
  /* USER CODE END LED_Function */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */



/* USER CODE END Application */

