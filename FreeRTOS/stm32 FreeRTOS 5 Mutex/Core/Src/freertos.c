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
osThreadId defaultTaskHandle;
osThreadId myLowTaskHandle;
osThreadId myMidTaskHandle;
osThreadId myHighTaskHandle;
osMutexId myMuSemHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void LowTask(void const * argument);
void MidTask(void const * argument);
void HighTask(void const * argument);

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
  /* Create the mutex(es) */
  /* definition and creation of myMuSem */
  osMutexDef(myMuSem);
  myMuSemHandle = osMutexCreate(osMutex(myMuSem));

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
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of myLowTask */
  osThreadDef(myLowTask, LowTask, osPriorityIdle, 0, 128);
  myLowTaskHandle = osThreadCreate(osThread(myLowTask), NULL);

  /* definition and creation of myMidTask */
  osThreadDef(myMidTask, MidTask, osPriorityIdle, 0, 128);
  myMidTaskHandle = osThreadCreate(osThread(myMidTask), NULL);

  /* definition and creation of myHighTask */
  osThreadDef(myHighTask, HighTask, osPriorityIdle, 0, 128);
  myHighTaskHandle = osThreadCreate(osThread(myHighTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_LowTask */
/**
* @brief Function implementing the myLowTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_LowTask */
void LowTask(void const * argument)
{
  /* USER CODE BEGIN LowTask */
  /* Infinite loop */
  static uint32_t i; 
  osStatus xReturn;
  /* Infinite loop */
  for(;;)
  {
    printf("LowPriority_Task Get Mutex\r\n");
    //获取互斥量 MuxSem,没获取到则一直等待 
    xReturn = osMutexWait(myMuSemHandle,     /* 互斥量句柄 */ 
                          osWaitForever);   /* 等待时间 */
    if(osOK == xReturn) 
    {
        printf("LowPriority_Task Runing\r\n"); 
    }
    
    for(i = 0; i < 2000000; i++) 
    { //模拟低优先级任务占用互斥量 
        taskYIELD();//发起任务调度 
    } 
    
    printf("LowPriority_Task Release Mutex\r\n"); 
    xReturn = osMutexRelease(myMuSemHandle);//给出互斥量 
    
    osDelay(1000);
  }

  /* USER CODE END LowTask */
}

/* USER CODE BEGIN Header_MidTask */
/**
* @brief Function implementing the myMidTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_MidTask */
void MidTask(void const * argument)
{
  /* USER CODE BEGIN MidTask */
  /* Infinite loop */
  for(;;)
  {
    printf("MidPriority_Task Runing\r\n"); 
    osDelay(1000);
  }
  /* USER CODE END MidTask */
}

/* USER CODE BEGIN Header_HighTask */
/**
* @brief Function implementing the myHighTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_HighTask */
void HighTask(void const * argument)
{
  /* USER CODE BEGIN HighTask */
  osStatus xReturn;
  /* Infinite loop */
  for(;;)
  {
    printf("HighPriority_Task Get Mutex\r\n"); 
    //获取互斥量 MuxSem,没获取到则一直等待 
    xReturn = osMutexWait(myMuSemHandle,     /* 互斥量句柄 */ 
                          osWaitForever);   /* 等待时间 */
    if(osOK == xReturn) 
    {
        printf("HighPriority_Task Runing\r\n"); 
    }
  
    printf("HighPriority_Task Release Mutex\r\n"); 
    xReturn = osMutexRelease(myMuSemHandle);//给出互斥量

    osDelay(1000);
  }

  /* USER CODE END HighTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

