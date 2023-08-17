#include "encoder.h"


void Encoder_Start(void)
{
	__HAL_TIM_SET_COUNTER(&htim2,0);   //�ô��κ����ñ������ĳ�ʼֵΪ0(�漰����ת����Ҫ)
	__HAL_TIM_SET_COUNTER(&htim3,0);

	HAL_TIM_Encoder_Start_IT(&htim2,TIM_CHANNEL_ALL);   //�������������ж�ģʽ,������ʱ��ͨ��TI1��TI2��ÿ���������������źŲɼ�ͨ��.
	HAL_TIM_Encoder_Start_IT(&htim3,TIM_CHANNEL_ALL);

	HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_ALL);  //��������������
	HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_ALL);
}

//��ȡ����������ֵ
int Read_Speed(int TIMx)
{
	int Encoder_Value = 0;
	switch(TIMx)
	{
		case 2: 
			Encoder_Value =(short) __HAL_TIM_GET_COUNTER(&htim2);     //�����������������ֵ
			__HAL_TIM_SET_COUNTER(&htim2,0);                   //����֮��Ҫ����,�Ա��´μ�����ȡ.����ÿ����������ֵ��0,ֱ���õ�λʱ��Ļ��Ϳ��Եó��ٶ���Ϣ��.��Ҫ�鷳��Ҫ��ȥ��ֵ��.
			break;

		case 3: 
			Encoder_Value =(short) __HAL_TIM_GET_COUNTER(&htim3);
			__HAL_TIM_SET_COUNTER(&htim3,0);
			break;
		
		default:
			Encoder_Value = 0;
	}	
	return Encoder_Value;
}

void Encoder_IRQHandler(void)   //�˴�ֻ�����жϱ�־,ʵ�ʲ�û������������.
{
	HAL_TIM_IRQHandler(&htim2);   //IRQHandler()����ֻ�����жϱ�־,ʵ��ISR�жϷ�������Ǹú�����ȥ������Ӧ��callback()����ʵ�ֵ�.
	HAL_TIM_IRQHandler(&htim3);   //��������ҪISR������Զ�����Ӧ��callback()��������,��Ϊϵͳ�е�callback()��__weak�����Ŀպ���.
}

