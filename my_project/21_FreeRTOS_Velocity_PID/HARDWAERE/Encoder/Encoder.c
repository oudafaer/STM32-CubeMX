#include "Encoder.h"


int Encoder_Left,Encoder_Right;        //���ұ��������������
int Add_Encoder_Left=0,Add_Encoder_Right=0;        //���ұ��������������




/*htim2��htim3�����tim.c���Ѿ�������ˡ�
������ԭ��:ÿ�����A���B��ֱ���ĳ����ʱ��������channelȥ�ɼ������ֵ�1��0,AB��λ��90��(����)���Ը��������ź��ĸ����ĸ������жϷ���,
����ÿ���ź����������Ķ��ټ����������ֵ��ܳ��Ϳ��������ǰ���ߵľ���;����ټ��϶�ʱ���Ļ������Լ�����ٶȡ�
��ʱ�ɼ����ı�����������û�и���ë��,��˱�����ģʽ�Ķ�ʱ������ʱ�������˲�FPֵ.*/
void Encoder_Start(void)   //��������������. ����������ʼ��HAL_TIM_Encoder_Init()��HAL_TIM_Encoder_MspInit()��main()�����е��õ�MX_TIM2_Init()�С�
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
/**************************************************************************
��    ��: ����ʵ��ת��
��    ��: encoder_cnt����������
����  ֵ: ����ת�� rpm
**************************************************************************/
float Motp_Speed(int encoder_cnt)
{
	float temp;
	temp=encoder_cnt*(1000/PID_COMPUTATION_PERIOD)/(RESOLUTION_TOTAL*REDUCTION_RATIO);
	return temp;
}
/**************************************************************************
��    ��: ����ת����Ӧ������������
��    ��: num��ת����ppr����������ratio�����ٱ�
�� �� ֵ: ��������� 
**************************************************************************/
long Num_Encoder_Cnt(float num)
{
    return (num*RESOLUTION_TOTAL*REDUCTION_RATIO);                               /* 4��Ƶ */       
}
/**************************************************************************
��    ��: ������������Ӧ���λ��
��    ��: encoder_cnt����������
�� �� ֵ: λ�ƣ����ף�
**************************************************************************/
int Encoder_Cnt_Location(int encoder_cnt)
{
	return ((encoder_cnt*(WHEEL_R*2*PI))/(RESOLUTION_TOTAL*REDUCTION_RATIO));
}
/**************************************************************************
��    ��: ������λ�ƶ�Ӧ������
��    ��:	λ�ƣ����ף�
�� �� ֵ: ��������
**************************************************************************/
long Location_Encoder_Cnt(int Location)
{
	return (Motp_Speed(Location/(2*PI*WHEEL_R)));
}

/**************************************************************************
��    ��: ����ת�ٶ�Ӧ������������
��    ��: rpm��ת�٣�ppr����������ratio�����ٱȣ�cnt_time������ʱ��(ms)
�� �� ֵ: ��������� 
**************************************************************************/
long Rpm_Encoder_Cnt(float rpm)
{
    return (rpm*RESOLUTION_TOTAL*REDUCTION_RATIO)/(1000/PID_COMPUTATION_PERIOD);            /* 4��Ƶ */       
}





