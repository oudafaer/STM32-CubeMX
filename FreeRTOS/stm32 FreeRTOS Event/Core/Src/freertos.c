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
#define KEY1_EVENT (0x01 << 0)//�����¼������λ 0 
#define KEY2_EVENT (0x01 << 1)//�����¼������λ 1
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
//    //��� KEY2 ������ 
//    if(HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == 0) 
//    { 
//		osDelay(10);
//		if(HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == 0) 
//		{
//			printf("KEY2 down\n"); 
//			/* ����һ���¼� 2 */ 
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
   //��� KEY1 ������ 
    if(HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == 0) 
    { 
		osDelay(10);
		if(HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == 0) 
		{
			        printf("KEY1 down\r\n"); 
					/* ����һ���¼� 1 */ 
					osEventFlagsSet(myEventHandle, KEY1_EVENT); 
		}

    }
	while(HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == 0)
	{
		osDelay(10);
	}
	    //��� KEY2 ������ 
    if(HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == 0) 
    { 
		osDelay(10);
		if(HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == 0) 
		{
			printf("KEY2 down\r\n"); 
			/* ����һ���¼� 2 */ 
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
	uint32_t r_event; /* ����һ���¼����ձ��� */ 
  for(;;)
  {
    /************************************************************* 
    * �ȴ������¼���־ 
    * 
    * ���������Ϊ osFlagsNoClear����ô�� osEventFlagsWait()����֮ǰ�� 
    * �������ȴ�����������������ص�ԭ���ǳ�ʱ������ô���¼��������� 
    * �� flags �е��κ�λ����������� 
    * �������Ϊ osFlagsNoClear�� 
    * ���ڵ��� osEventFlagsWait()ʱ����������¼��������õ�λ�� 
    *
    * �������Ϊ osFlagsWaitAll���� flags �� 
    * ������λ�����û�ָ���Ŀ�ʱ�䵽��ʱ��osEventFlagsWait()�ŷ��ء� 
    * ���������Ϊ osFlagsWaitAll�������� flasgs �����õ��κ� 
    * һ��λ�� 1 ��ָ���Ŀ�ʱ�䵽��ʱ��osEventFlagsWait()���᷵�ء� 
    * ����ʱ���� timeout ����ָ���� 
    *********************************************************/ 
    r_event = osEventFlagsWait(myEventHandle,             /* �¼������� */ 
                              KEY1_EVENT|KEY2_EVENT,    /* �����������Ȥ���¼� */ 
                              osFlagsWaitAll,           /* �˳�ʱ����¼�λ��ͬʱ�������Ȥ�������¼� */ 
                              osWaitForever);           /* ָ����ʱ�¼�,һֱ�� */ 
  
    if((r_event & (KEY1_EVENT|KEY2_EVENT)) == (KEY1_EVENT|KEY2_EVENT)) 
    { 
        /* ���������ɲ�����ȷ */ 
        printf ("KEY1 and KEY2 down\r\n"); 
    } 
    else 
    {
        printf ("Event Error��\r\n"); 
    }

  }
  /* USER CODE END ReceiveTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

