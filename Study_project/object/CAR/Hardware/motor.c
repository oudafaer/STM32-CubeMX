#include "motor.h"



/**************************************************************************
函数功能：绝对值函数
入口参数：int
返回  值：unsigned int

**************************************************************************/
int GFP_abs(int a)
{ 		   
	int temp;
	temp = a>0?a:(-a);
	return temp;
}


/**
 * 函数名:Load_Motor_PWM
 * 描述:更新PWM,并将其写定时器
 * 输入:MOTOR1_PWM-左轮电机计算得出的PWM值，MOTOR2_PWM-右轮电机计算得出的PWM值
 * 输出:无
 */
void Load_Motor_PWM(int MOTOR1_PWM,int MOTOR2_PWM)
{
  MOTOR1_PWM=(MOTOR1_PWM>0)?MOTOR1_PWM:(-MOTOR1_PWM);
	MOTOR2_PWM=(MOTOR2_PWM>0)?MOTOR2_PWM:(-MOTOR2_PWM);
	
  MOTOR1_PWM=(MOTOR1_PWM>PWM_MAX)?PWM_MAX:MOTOR1_PWM;
	MOTOR2_PWM=(MOTOR2_PWM>PWM_MAX)?PWM_MAX:MOTOR2_PWM;	
	
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,MOTOR1_PWM);   //把传参进来的PWM值送给定时器1的channel_1通道.
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,MOTOR2_PWM);   //把传参进来的PWM值送给定时器1的channel_1通道.
}


/**
 * 函数名:set_motor_enable
 * 描述:使能电机
 * 输入:无
 * 输出:无
 */
void set_motor_enable(void)
{
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);  //根据MX配置和原理图：这里需要开启的是TIM1的PWM输出通道1
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);  //开启TIM1的PWM输出通道1
}

/**
 * 函数名:set_motor_disable
 * 描述:失能电机
 * 输入:无
 * 输出:无
 */
void set_motor_disable(void)
{
	HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_4);	
}
void CarRun()	//	前进 
{
		Ain1=1,	Ain2=0;
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,2760);
		Bin1=1,	Bin2=0;
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,2700);
}

void CarBack()	//后退
{
		Ain1=0,	Ain2=1;
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,2760);
		Bin1=0,	Bin2=1;
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,2700);
}

void CarStop()	//停止
{
		Ain1=0,	Ain2=0;
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,0);
		Bin1=0,	Bin2=0;
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,0);
}

void CarTurnRight()	//右转
{
		Ain1=1,	Ain2=0;
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,2760);
		Bin1=0,	Bin2=1;
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,2700);
}

void CarTurnLeft()	//	左转
{
		Ain1=0,	Ain2=1;
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,2760);
		Bin1=1,	Bin2=0;
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,2700);
}


