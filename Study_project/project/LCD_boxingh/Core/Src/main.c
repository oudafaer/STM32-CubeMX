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
#include "adc.h"
#include "dac.h"
#include "dma.h"
#include "usart.h"
#include "gpio.h"
#include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32_dsp.h"
#include "table_fft.h"
#include "math.h"
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

/* USER CODE BEGIN PV */

#define NPT 1024 //采样次数
#define PI2 6.28318530717959

void lcd_huadian(uint16_t a,uint16_t b,uint16_t color);//画点函数
void lcd_huaxian(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);//画线函数
void window(void);//主界面
void clear_point(uint16_t mode);//更新显示屏当前列
void InitBufInArray(void);//正弦波输出缓存
void sinout(void);//正弦波输出
void GetPowerMag(void);//FFT变换，输出频率

int long fftin [NPT];//FFT输入
int long fftout[NPT];//FFT输出
uint32_t FFT_Mag[NPT/2]={0};//幅频特性
uint16_t magout[NPT];//模拟正弦波输出缓存区

uint16_t table[15] ={16,32,48,64,80,96,112,128,144,160,176,192,208,224,240};//标点横坐标
uint16_t currentadc;//实时采样数据
uint16_t adcx[NPT];//adc数值缓存
uint32_t adcmax;//采样最大值和最小值
uint32_t adcmin;
uint8_t adc_flag=0;//采样结束标志
uint8_t key_flag=0;//按键扫描标志
uint8_t  show_flag=1;//更新暂停标志
uint16_t T=2000;//定时器2重载值，不能小于PWM的Pluse值
uint16_t pre=36;//定时器2预分频值
uint32_t fre;//采样频率 kHz
uint16_t F;//波形频率

uint16_t V=660;//纵坐标单位刻度 mv/div
uint16_t temp=0;//幅值最大的频率成分
uint16_t t=0;
uint16_t key;//按键值


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/**********************************************************
简介：画点函数，反转Y坐标
***********************************************************/
void lcd_huadian(uint16_t a,uint16_t b,uint16_t color)
{							    
	LCD_Fast_DrawPoint(a,240-b,color);
}

/**********************************************************
简介：画线函数，反转Y坐标
***********************************************************/
void lcd_huaxian(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
	LCD_DrawLine(x1,240-y1,x2,240-y2);
}
/**********************************************************
简介：主界面绘制
***********************************************************/
void window(void)
{
	uint16_t x,i;
	static uint16_t h; 
	
	POINT_COLOR=GREEN;	  
	LCD_ShowString(5,8,200,24,24,"OSC-DWY");
	
	POINT_COLOR=GRAY;
	LCD_ShowString(190,13,200,16,16,"mV/div");	
	LCD_ShowString(260,5,200,16,16,"max(mv):");
	LCD_ShowString(260,45,200,16,16,"min(mv):");
	LCD_ShowString(260,85,200,16,16,"vpp(mv):");
	LCD_ShowString(260,165,200,16,16,"f(Hz):");
	LCD_ShowString(260,200,200,16,16,"OSR:");  //采样率	
	LCD_ShowString(304,220,200,16,16,"Hz");
	
	POINT_COLOR=BRRED;
	LCD_ShowString(100,13,200,16,16,"IN:PA6");
	
	POINT_COLOR=BLUE;
	LCD_ShowNum(150,13,V,4,16);//mv/div
	
	POINT_COLOR=WHITE;			
	lcd_huaxian(0,0,0,200);
	lcd_huaxian(256,0,256,200);
	lcd_huaxian(0,0,256,0);		
	lcd_huaxian(0,200,256,200);
	
	for(x=0;x<256;x++)
	{
		lcd_huadian(x,100,WHITE);
		if(x == table[h])	
		{
			lcd_huaxian(x,1,x,3);
			lcd_huaxian(x,101,x,103);
			lcd_huaxian(x,199,x,197);
			h++;
			if(h>=16) h=0;
		}	
		if(x==128) 
		{
			lcd_huaxian(x,1,x,199);
			for(i=10;i<200;i+=10)
			{
				lcd_huaxian(125,i,127,i);
			}
		}
	}
	
	POINT_COLOR=MAGENTA;	
	LCD_ShowString(260,128,200,16,16,"ing...");
}

/******************************************************************
函数名称:clear_point()
函数功能:循环更新波形
参数说明:mode 波形模式选择 1——连线模式，0——打点模式
备    注:波形的显示可采用打点方式和绘制线方式
*******************************************************************/
void clear_point(uint16_t mode)
{
	uint16_t x,i,past_vol,pre_vol;
	static uint16_t h; 
	
	POINT_COLOR=BLUE;
	fre=72000000/T/pre;//更新采样频率
	LCD_ShowNum(261,220,fre,5,16);//更新采样率显示
	
	for(x=0;x<256;x++)
	{	
		POINT_COLOR=BLACK;	//按列清除
		if(x!=128)	//y轴不进行列清除
			lcd_huaxian(x,4,x,196);
		
		//绘制坐标
		POINT_COLOR=WHITE;
		lcd_huaxian(0,0,0,200);
		lcd_huadian(x,100,WHITE);
		if(x == table[h])	
		{
			lcd_huaxian(x,101,x,103);
			h++;
			if(h>=15) h=0;
		}	
		if(x==128) 
		{
			lcd_huaxian(x,1,x,199);
			for(i=10;i<200;i+=10)
			{
				lcd_huaxian(125,i,127,i);
			}
		}
		
		pre_vol = 50+adcx[x]/4096.0*100;

		//波形更新
		if(mode==1)
		{
			POINT_COLOR=YELLOW;
			if(x>0&&x<255&&x!=128)	//去除第一个，最后一个以及y轴上点的绘制
				lcd_huaxian(x,past_vol,x+1,pre_vol);
		}
		else
			lcd_huadian(x,pre_vol,YELLOW);

		past_vol = pre_vol;
	}
	
}
/******************************************************************
函数名称:GetPowerMag()
函数功能:计算各次谐波幅值
参数说明:
备　　注:先将lBufOutArray分解成实部(X)和虚部(Y)，然后计算幅值(sqrt(X*X+Y*Y)
*******************************************************************/
void GetPowerMag(void)
{
    float X,Y,Mag,magmax;//实部，虚部，各频率幅值，最大幅值
    u16 i;
	
	//调用自cr4_fft_1024_stm32
	cr4_fft_1024_stm32(fftout, fftin, NPT);	
	
    for(i=1; i<NPT/2; i++)
    {
		X = (fftout[i] << 16) >> 16;	//低16位存实部
		Y = (fftout[i] >> 16);			//高16位存虚部
		
		Mag = sqrt(X * X + Y * Y); 		//计算模值
		FFT_Mag[i]=Mag;					//存入缓存，用于输出查验
		//获取最大频率分量及其幅值
		if(Mag > magmax)
		{
			magmax = Mag;
			temp = i;
		}
    }
	F=(u16)(temp*(fre*1.0/NPT));	//FFT所得实际频率f=点数i*(采样频率F/总采样点数N)
//	if(T==1000)		F=(u32)((double)temp/NPT*1000  );	
//	if(T==100)		F=(u32)((double)temp/NPT*10010 );
//	if(T==10)		F=(u32)((double)temp/NPT*100200);
//	if(T==2)		F=(u32)((double)temp/NPT*249760);
	
	LCD_ShowNum(260,180,F,5,16);		
//		LCD_ShowNum(280,200,temp,4,16);					
//		LCD_ShowNum(280,220,(u32)(magmax*2.95),5,16);			
}
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	adc_flag=1;
	HAL_ADC_Stop_DMA(&hadc1);
	
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint16_t i;
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
  MX_FSMC_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  MX_DAC_Init();
  /* USER CODE BEGIN 2 */
  /* Configure the system clock */
  /* USER CODE END 2 */
	TFTLCD_Init();
	HAL_ADC_Start_DMA(&hadc1,(uint32_t*)adcx,1024);
	HAL_Delay(100);
	LCD_Clear(BLACK);
	window();
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
		while(!adc_flag)
		{
			HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
			HAL_Delay(500);
		}
		adc_flag=0;
		
		//获取最大最小值
		adcmax=adcx[1];
		adcmin=adcx[1];
		for(i=0;i<NPT;i++)
		{
			fftin[i] = 0;
			fftin[i] = adcx[i] << 16;
			
			if(adcx[i] >= adcmax)
			{			
				adcmax = adcx[i];
			}			
			if(adcx[i] <= adcmin)
			{			
				adcmin = adcx[i];
			}						
		}
		POINT_COLOR=BLUE;
		GetPowerMag();
		
		adcmax=adcmax*0.8;   //0.8 ≈ 3300/4096	
		adcmin=adcmin*0.8;
		
		LCD_ShowNum(270,25,adcmax,4,16);	//显示最大值
		LCD_ShowNum(270,65,adcmin,4,16);	//显示最小值
		LCD_ShowNum(270,105,adcmax-adcmin,4,16);	//显示幅值
		
		clear_point(1);    //更新显示屏当前列，采用连线绘制
		
		HAL_Delay(100);
		HAL_ADC_Start_DMA(&hadc1,(uint32_t*)adcx,1024);
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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

