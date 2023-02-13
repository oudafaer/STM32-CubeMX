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
#include "rtc.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
RTC_TimeTypeDef RtcTime;
RTC_DateTypeDef RtcDate;



const char LedMode1[8] = "kaishi";
const char LedMode2[11] = "chushihua";
const char LedMode3[14] = "shezhi12311111";
const char LedMode4[9] = "xianshi";




#define RXBUFFERSIZE  256     //�������ֽ���
char RxBuffer[RXBUFFERSIZE];   //��������
uint8_t aRxBuffer;			//�����жϻ���
uint8_t Uart1_Rx_Cnt = 0;		//���ջ������


/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

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
  MX_RTC_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

 HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer, 1);
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_RTCEx_RTCEventCallback(RTC_HandleTypeDef *hrtc)
{
 
	HAL_RTC_GetTime(&*hrtc,&RtcTime,RTC_FORMAT_BIN);//��ȡʱ��
  HAL_RTC_GetDate(&*hrtc,&RtcDate,RTC_FORMAT_BIN);//��ȡ����
 
  printf("time:%2d:%2d:%2d\r\n",RtcTime.Hours,RtcTime.Minutes,RtcTime.Seconds);
  printf("data:%4d.%2d.%2d\r\n",2000+RtcDate.Year,RtcDate.Month,RtcDate.Date);

}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	UNUSED(huart);
	//if(Uart1_Rx_Cnt >= 255)  //����ж�
	//{
		//Uart1_Rx_Cnt = 0;
		//memset(RxBuffer,0x00,sizeof(RxBuffer));
		//HAL_UART_Transmit(&huart1, (uint8_t *)"�������", 10,0xFFFF); 	
		//printf("�������");
	//}
	//else
	//{
		RxBuffer[Uart1_Rx_Cnt++] = aRxBuffer;   //��������ת��
	
		if((RxBuffer[Uart1_Rx_Cnt-1] == 0x0A)&&(RxBuffer[Uart1_Rx_Cnt-2] == 0x0D)) //�жϽ���λ
		{
			//HAL_UART_Transmit(&huart1, (uint8_t *)&RxBuffer, Uart1_Rx_Cnt,0xFFFF); //���յ�����Ϣ���ͳ�ȥ
			Uart1_Rx_Cnt = 0;
			if(strstr((const char *)RxBuffer,LedMode1) != NULL)
			{
				 HAL_RTC_GetTime(&hrtc, &RtcTime,  RTC_FORMAT_BIN);//����ʱ��ֵ
				 HAL_RTC_GetDate(&hrtc, &RtcDate,  RTC_FORMAT_BIN);//һ��Ҫ�ȶ�ʱ��������
				 printf(" ������RTCʵʱʱ�Ӳ���   \r\n");
				 printf(" ʵʱʱ�䣺%04d-%02d-%02d  %02d:%02d:%02d  \r\n",2000+RtcDate.Year,
				 RtcDate.Month, RtcDate.Date,RtcTime.Hours, RtcTime.Minutes, RtcTime.Seconds);//��ʾ����ʱ��
				 printf(" �����س�������ʱ�䣬������ĸC��ʼ��ʱ�� \r\n");
				 printf(" ����������ʱ�䣬��ʽ20170806120000�����س���ȷ���� \r\n");

			}
			if(strstr((const char *)RxBuffer,LedMode2) != NULL)
			{
	  	          MX_RTC_Init(); //��������c��C����ʼ��ʱ��
	  	          printf("��ʼ���ɹ���       \r\n");//��ʾ��ʼ���ɹ�
			}
			if(strlen((const char *)RxBuffer) == 16)
			{
				  RtcDate.Year =  (RxBuffer[2]-0x30)*10+RxBuffer[3]-0x30;//��0x30����ܵõ�ʮ����0~9������
				  RtcDate.Month =  (RxBuffer[4]-0x30)*10+RxBuffer[5]-0x30;
				  RtcDate.Date =  (RxBuffer[6]-0x30)*10+RxBuffer[7]-0x30;
				  RtcTime.Hours =  (RxBuffer[8]-0x30)*10+RxBuffer[9]-0x30;
				  RtcTime.Minutes =  (RxBuffer[10]-0x30)*10+RxBuffer[11]-0x30;
				  RtcTime.Seconds =  (RxBuffer[12]-0x30)*10+RxBuffer[13]-0x30;
				  if (HAL_RTC_SetTime(&hrtc,  &RtcTime, RTC_FORMAT_BIN) != HAL_OK)//������д��RTC����
				  {
					  printf("д��ʱ��ʧ�ܣ�        \r\n"); //��ʾд��ʧ��
				  }
				  else if (HAL_RTC_SetDate(&hrtc,  &RtcDate, RTC_FORMAT_BIN) != HAL_OK)//������д��RTC����
				  {
					  printf("д������ʧ�ܣ�        \r\n"); //��ʾд��ʧ��
				  }
				  else
				  {
					  printf("д��ɹ���       \r\n");//��ʾд��ɹ�
					  __HAL_RTC_SECOND_ENABLE_IT(&hrtc,RTC_IT_SEC);
					  
				  }

			}
			if(strstr((const char *)RxBuffer,LedMode4) != NULL)
			{
					  __HAL_RTC_SECOND_ENABLE_IT(&hrtc,RTC_IT_SEC);
			}
			memset(RxBuffer,0x00,sizeof(RxBuffer)); //�������
		}
	//}
	
	HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer, 1);   //�ٿ��������ж�

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

