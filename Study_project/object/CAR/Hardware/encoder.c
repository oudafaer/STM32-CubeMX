#include "encoder.h"

/*htim2��htim4�����tim.c���Ѿ�������ˡ�
������ԭ��:ÿ�����A���B��ֱ���ĳ����ʱ��������channelȥ�ɼ������ֵ�1��0,AB��λ��90��(����)���Ը��������ź��ĸ����ĸ������жϷ���,
����ÿ���ź����������Ķ��ټ����������ֵ��ܳ��Ϳ��������ǰ���ߵľ���;����ټ��϶�ʱ���Ļ������Լ�����ٶȡ�
��ʱ�ɼ����ı�����������û�и���ë��,��˱�����ģʽ�Ķ�ʱ������ʱ�������˲�FPֵ.*/

void Encoder_Start(void)   //��������������. ����������ʼ��HAL_TIM_Encoder_Init()��HAL_TIM_Encoder_MspInit()��main()�����е��õ�MX_TIM2_Init()�С�
{
	__HAL_TIM_SET_COUNTER(&htim2,0);   //�ô��κ����ñ������ĳ�ʼֵΪ0(�漰����ת����Ҫ)
	__HAL_TIM_SET_COUNTER(&htim4,0);

	HAL_TIM_Encoder_Start_IT(&htim2,TIM_CHANNEL_ALL);   //�������������ж�ģʽ,������ʱ��ͨ��TI1��TI2��ÿ���������������źŲɼ�ͨ��.
	HAL_TIM_Encoder_Start_IT(&htim4,TIM_CHANNEL_ALL);

	HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_ALL);  //��������������
	HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_ALL);
	
}


//��ȡ����������ֵ
int Read_Pluse(int TIMx)
{
	int Encoder_Value = 0;
	switch(TIMx)
	{
		case 2: 
			Encoder_Value =(short) __HAL_TIM_GET_COUNTER(&htim2);     //�����������������ֵ
			__HAL_TIM_SET_COUNTER(&htim2,0);                   //����֮��Ҫ����,�Ա��´μ�����ȡ.����ÿ����������ֵ��0,ֱ���õ�λʱ��Ļ��Ϳ��Եó��ٶ���Ϣ��.��Ҫ�鷳��Ҫ��ȥ��ֵ��.
			break;

		case 4: 
			Encoder_Value =(short) __HAL_TIM_GET_COUNTER(&htim4);
			__HAL_TIM_SET_COUNTER(&htim4,0);
			break;
		
		default:
			Encoder_Value = 0;
	}	
	return Encoder_Value;
}

void Encoder_IRQHandler(void)   //�˴�ֻ�����жϱ�־,ʵ�ʲ�û������������.
{
	HAL_TIM_IRQHandler(&htim2);   //IRQHandler()����ֻ�����жϱ�־,ʵ��ISR�жϷ�������Ǹú�����ȥ������Ӧ��callback()����ʵ�ֵ�.
	HAL_TIM_IRQHandler(&htim4);   //��������ҪISR������Զ�����Ӧ��callback()��������,��Ϊϵͳ�е�callback()��__weak�����Ŀպ���.
}


