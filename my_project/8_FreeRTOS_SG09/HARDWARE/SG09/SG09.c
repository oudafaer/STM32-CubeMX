#include "sg09.h"

/* USER CODE BEGIN Header */
/**
  ******************************************************************************
	* @�ļ���  :   PWM_Init
	* @��������:  ��ʼ����ʱ��2��ͨ��1.2.3.4���pwm��
	* @�������: ��
	* @�������: ��    
	* @��ע:	
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
	* @�ļ���  :   PWM_setValue
	* @��������:  ѡ��ʱ��ͨ�����PWM��
	* @�������: ch:ѡ���ͨ����angle:ת���Ƕȵ�ֵ
	* @�������: ��      
	* @��ע:����Ķ�ʱ��Ԥ��ƵֵΪ719���Զ���װֵΪ1999���õ�����Ϊ20ms������PWM��
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



