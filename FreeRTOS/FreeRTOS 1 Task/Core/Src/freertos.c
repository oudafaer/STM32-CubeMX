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
osThreadId myLED1TaskHandle;
osThreadId myLED2TaskHandle;
osThreadId myKEYHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void LED1Task(void const * argument);
void LED2Task(void const * argument);
void KEYTask(void const * argument);

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
  /* definition and creation of myLED1Task */
  osThreadDef(myLED1Task, LED1Task, osPriorityNormal, 0, 128);
  myLED1TaskHandle = osThreadCreate(osThread(myLED1Task), NULL);

  /* definition and creation of myLED2Task */
  osThreadDef(myLED2Task, LED2Task, osPriorityNormal, 0, 128);
  myLED2TaskHandle = osThreadCreate(osThread(myLED2Task), NULL);

  /* definition and creation of myKEY */
  osThreadDef(myKEY, KEYTask, osPriorityNormal, 0, 128);
  myKEYHandle = osThreadCreate(osThread(myKEY), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_LED1Task */
/**
  * @brief  Function implementing the myLED1Task thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_LED1Task */
void LED1Task(void const * argument)
{
  /* USER CODE BEGIN LED1Task */
  /* Infinite loop */
	osThreadSuspend(NULL);
  for(;;)
  {
    
	  HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
	  osDelay(300);
  }
  /* USER CODE END LED1Task */
}

/* USER CODE BEGIN Header_LED2Task */
/**
* @brief Function implementing the myLED2Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_LED2Task */
void LED2Task(void const * argument)
{
  /* USER CODE BEGIN LED2Task */
  /* Infinite loop */
//	osThreadSuspend(NULL);
  for(;;)
  {
	  HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);
	  osDelay(300);
  }
  /* USER CODE END LED2Task */
}

/* USER CODE BEGIN Header_KEYTask */
/**
* @brief Function implementing the myKEY thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_KEYTask */
void KEYTask(void const * argument)
{
  /* USER CODE BEGIN KEYTask */
  /* Infinite loop */
	static uint8_t flag=0;
  for(;;)
  {
    if(HAL_GPIO_ReadPin(KEY0_GPIO_Port,KEY0_Pin)==0&&flag==0)
    {
    osDelay(10);//延时检测按键按下情况，防止误判                                
    if(HAL_GPIO_ReadPin(KEY0_GPIO_Port,KEY0_Pin)==0&&flag==0)
    {
    osThreadResume(myLED1TaskHandle);
    flag=1;
    }
    while(HAL_GPIO_ReadPin(KEY0_GPIO_Port,KEY0_Pin)==0) //等待按键释放
    {
    osDelay(10);
    }
    }
 
 
    if(HAL_GPIO_ReadPin(KEY0_GPIO_Port,KEY0_Pin)==0&&flag==1)
    {
    osDelay(10); //延时检测按键按下情况，防止误判  
    if(HAL_GPIO_ReadPin(KEY0_GPIO_Port,KEY0_Pin)==0&&flag==1)
    {
    osThreadSuspend(myLED1TaskHandle);
    flag=0;
    }
    while(HAL_GPIO_ReadPin(KEY0_GPIO_Port,KEY0_Pin)==0) //等待按键释放
    {
    osDelay(10);
    }
    }
    
    osDelay(1);
 
  }
  /* USER CODE END KEYTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

