#include "encoder.h"


void Encoder_Start(void)
{
	__HAL_TIM_SET_COUNTER(&htim2,0);   //用带参宏设置编码器的初始值为0(涉及正反转的需要)
	__HAL_TIM_SET_COUNTER(&htim3,0);

	HAL_TIM_Encoder_Start_IT(&htim2,TIM_CHANNEL_ALL);   //开启编码器的中断模式,两个定时器通道TI1和TI2是每个编码器的两个信号采集通道.
	HAL_TIM_Encoder_Start_IT(&htim3,TIM_CHANNEL_ALL);

	HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_ALL);  //开启两个编码器
	HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_ALL);
}

//获取编码器计数值
int Read_Speed(int TIMx)
{
	int Encoder_Value = 0;
	switch(TIMx)
	{
		case 2: 
			Encoder_Value =(short) __HAL_TIM_GET_COUNTER(&htim2);     //保存编码器计数器的值
			__HAL_TIM_SET_COUNTER(&htim2,0);                   //保存之后要清零,以便下次继续读取.另外每次清零后采样值减0,直接用单位时间的话就可以得出速度信息了.不要麻烦还要减去初值了.
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

void Encoder_IRQHandler(void)   //此处只是清中断标志,实际并没有做其他操作.
{
	HAL_TIM_IRQHandler(&htim2);   //IRQHandler()函数只是清中断标志,实际ISR中断服务程序是该函数又去调用相应的callback()函数实现的.
	HAL_TIM_IRQHandler(&htim3);   //因此如果需要ISR则必须自定义相应的callback()函数才行,因为系统中的callback()是__weak声明的空函数.
}

