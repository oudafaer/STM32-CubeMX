#include "sg09.h"

/* USER CODE BEGIN Header */
/**
  ******************************************************************************
	* @文件名  :   PWM_Init
	* @函数介绍:  初始化定时器2的通道1.2.3.4输出pwm波
	* @输入参数: 无
	* @输出参数: 无    
	* @备注:	
  *
  *
  ******************************************************************************
  */
void PWM_Init(void)
{
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_4);	
	
}
/* USER CODE END Header */

/* USER CODE BEGIN Header */
/**
  ******************************************************************************
	* @文件名  :   PWM_setValue
	* @函数介绍:  选择定时器通道输出PWM波
	* @输入参数: ch:选择的通道，angle:转动角度的值
	* @输出参数: 无      
	* @备注:这里的定时器预分频值为719，自动重装值为1999，得到周期为20ms的周期PWM波
  *
  *
  ******************************************************************************
  */
void PWM_setValue(int ch,int angle)
{
	uint16_t Value;
	Value=(int)((angle+90)*200/180)+50;
	switch (ch)
	{
		case 1: TIM2->CCR1=Value;break;
		case 2: TIM2->CCR2=Value;break;
		case 3: TIM2->CCR3=Value;break;
		case 4: TIM2->CCR4=Value;break;		
		
	}
}	
/* USER CODE END Header */



