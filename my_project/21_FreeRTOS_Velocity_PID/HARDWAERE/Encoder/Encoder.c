#include "Encoder.h"


int Encoder_Left,Encoder_Right;        //左右编码器的脉冲计数
int Add_Encoder_Left=0,Add_Encoder_Right=0;        //左右编码器的脉冲计数




/*htim2和htim3句柄在tim.c中已经定义过了。
编码器原理:每个电机A相和B相分别用某个定时器的两个channel去采集编码轮的1和0,AB相位差90度(正交)可以根据两个信号哪个先哪个后来判断方向,
根据每个信号脉冲数量的多少及整个编码轮的周长就可以算出当前行走的距离;如果再加上定时器的话还可以计算出速度。
有时采集到的编码脉冲难免没有干扰毛刺,因此编码器模式的定时器配置时可设置滤波FP值.*/
void Encoder_Start(void)   //启动两个编码器. 而编码器初始化HAL_TIM_Encoder_Init()和HAL_TIM_Encoder_MspInit()在main()函数中调用的MX_TIM2_Init()中。
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
/**************************************************************************
功    能: 计算实际转速
输    入: encoder_cnt：脉冲数；
返回  值: 车轮转速 rpm
**************************************************************************/
float Motp_Speed(int encoder_cnt)
{
	float temp;
	temp=encoder_cnt*(1000/PID_COMPUTATION_PERIOD)/(RESOLUTION_TOTAL*REDUCTION_RATIO);
	return temp;
}
/**************************************************************************
功    能: 计算转数对应编码器脉冲数
输    入: num：转数；ppr：码盘数；ratio：减速比
返 回 值: 电机脉冲数 
**************************************************************************/
long Num_Encoder_Cnt(float num)
{
    return (num*RESOLUTION_TOTAL*REDUCTION_RATIO);                               /* 4倍频 */       
}
/**************************************************************************
功    能: 计算脉冲数对应电机位移
输    入: encoder_cnt：脉冲数；
返 回 值: 位移（厘米）
**************************************************************************/
int Encoder_Cnt_Location(int encoder_cnt)
{
	return ((encoder_cnt*(WHEEL_R*2*PI))/(RESOLUTION_TOTAL*REDUCTION_RATIO));
}
/**************************************************************************
功    能: 计算电机位移对应脉冲数
输    入:	位移（厘米）
返 回 值: 脉冲数；
**************************************************************************/
long Location_Encoder_Cnt(int Location)
{
	return (Motp_Speed(Location/(2*PI*WHEEL_R)));
}

/**************************************************************************
功    能: 计算转速对应编码器脉冲数
输    入: rpm：转速；ppr：码盘数；ratio：减速比；cnt_time：计数时间(ms)
返 回 值: 电机脉冲数 
**************************************************************************/
long Rpm_Encoder_Cnt(float rpm)
{
    return (rpm*RESOLUTION_TOTAL*REDUCTION_RATIO)/(1000/PID_COMPUTATION_PERIOD);            /* 4倍频 */       
}





