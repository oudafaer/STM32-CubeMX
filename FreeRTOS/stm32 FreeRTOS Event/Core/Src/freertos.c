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
#define KEY1_EVENT (0x01 << 0)//设置事件掩码的位 0 
#define KEY2_EVENT (0x01 << 1)//设置事件掩码的位 1
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for mySendTask */
osThreadId_t mySendTaskHandle;
const osThreadAttr_t mySendTask_attributes = {
  .name = "mySendTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for myReceiveTask */
osThreadId_t myReceiveTaskHandle;
const osThreadAttr_t myReceiveTask_attributes = {
  .name = "myReceiveTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for myEvent */
osEventFlagsId_t myEventHandle;
const osEventFlagsAttr_t myEvent_attributes = {
  .name = "myEvent"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void SendTask(void *argument);
void ReceiveTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

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
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of mySendTask */
  mySendTaskHandle = osThreadNew(SendTask, NULL, &mySendTask_attributes);

  /* creation of myReceiveTask */
  myReceiveTaskHandle = osThreadNew(ReceiveTask, NULL, &myReceiveTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Create the event(s) */
  /* creation of myEvent */
  myEventHandle = osEventFlagsNew(&myEvent_attributes);

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
//    //如果 KEY2 被按下 
//    if(HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == 0) 
//    { 
//		osDelay(10);
//		if(HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == 0) 
//		{
//			printf("KEY2 down\n"); 
//			/* 触发一个事件 2 */ 
//			osEventFlagsSet(myEventHandle, KEY2_EVENT); 			
//		}

//    }
//	while(HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == 0)
//	{
//		osDelay(10);
//	}		
//    osDelay(100);
	  osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_SendTask */
/**
* @brief Function implementing the mySendTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_SendTask */
void SendTask(void *argument)
{
  /* USER CODE BEGIN SendTask */
  /* Infinite loop */
  for(;;)
  {
   //如果 KEY1 被按下 
    if(HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == 0) 
    { 
		osDelay(10);
		if(HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == 0) 
		{
			        printf("KEY1 down\r\n"); 
					/* 触发一个事件 1 */ 
					osEventFlagsSet(myEventHandle, KEY1_EVENT); 
		}

    }
	while(HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == 0)
	{
		osDelay(10);
	}
	    //如果 KEY2 被按下 
    if(HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == 0) 
    { 
		osDelay(10);
		if(HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == 0) 
		{
			printf("KEY2 down\r\n"); 
			/* 触发一个事件 2 */ 
			osEventFlagsSet(myEventHandle, KEY2_EVENT); 			
		}

    }
	while(HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == 0)
	{
		osDelay(10);
	}
    osDelay(100);

  }
  /* USER CODE END SendTask */
}

/* USER CODE BEGIN Header_ReceiveTask */
/**
* @brief Function implementing the myReceiveTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_ReceiveTask */
void ReceiveTask(void *argument)
{
  /* USER CODE BEGIN ReceiveTask */
  /* Infinite loop */
	uint32_t r_event; /* 定义一个事件接收变量 */ 
  for(;;)
  {
    /************************************************************* 
    * 等待接收事件标志 
    * 
    * 如果不设置为 osFlagsNoClear，那么在 osEventFlagsWait()返回之前， 
    * 如果满足等待条件（如果函数返回的原因不是超时），那么在事件组中设置 
    * 的 flags 中的任何位都将被清除。 
    * 如果设置为 osFlagsNoClear， 
    * 则在调用 osEventFlagsWait()时，不会更改事件组中设置的位。 
    *
    * 如果设置为 osFlagsWaitAll，则当 flags 中 
    * 的所有位都设置或指定的块时间到期时，osEventFlagsWait()才返回。 
    * 如果不设置为 osFlagsWaitAll，则当设置 flasgs 中设置的任何 
    * 一个位置 1 或指定的块时间到期时，osEventFlagsWait()都会返回。 
    * 阻塞时间由 timeout 参数指定。 
    *********************************************************/ 
    r_event = osEventFlagsWait(myEventHandle,             /* 事件对象句柄 */ 
                              KEY1_EVENT|KEY2_EVENT,    /* 接收任务感兴趣的事件 */ 
                              osFlagsWaitAll,           /* 退出时清除事件位，同时满足感兴趣的所有事件 */ 
                              osWaitForever);           /* 指定超时事件,一直等 */ 
  
    if((r_event & (KEY1_EVENT|KEY2_EVENT)) == (KEY1_EVENT|KEY2_EVENT)) 
    { 
        /* 如果接收完成并且正确 */ 
        printf ("KEY1 and KEY2 down\r\n"); 
    } 
    else 
    {
        printf ("Event Error！\r\n"); 
    }

  }
  /* USER CODE END ReceiveTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

