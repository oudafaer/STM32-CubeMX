#include "motor.h"


int 	Moto1=0,Moto2=0;												 //计算出来的最终赋给电机的PWM



void Motor_Start(void)     //Motor控制所连接的PB12~15初始化在main()函数MX中执行了.
{
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);  //根据MX配置和原理图：这里需要开启的是TIM1的PWM输出通道1
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);  //开启TIM1的PWM输出通道1
}

/**************************************************************************
函数功能：赋值给PWM寄存器
入口参数：左轮PWM、右轮PWM
返回  值：无
**************************************************************************/
void Motor_Rotaton(int MotorA,int MotorB)
{
	//判断正负号，对应正反转
	if(MotorA>0)	Ain1=1,Ain2=0;//正转
	else 				Ain1=0,Ain2=1;//反转
	//2.研究PWM值
	if(MotorA)
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,GFP_abs(MotorA)+Dead_Voltage);   //把传参进来的PWM值送给定时器1的channel_1通道.
	else
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,0);   //把传参进来的PWM值送给定时器1的channel_1通道.
	
	
	
	if(MotorB>0)	Bin1=1,Bin2=0;
	else 				Bin1=0,Bin2=1;	
	if(MotorB)
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,GFP_abs(MotorB)+Dead_Voltage);
	else 
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,0);	
}

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
/*限幅函数:避免PWM过大超过马达的机械极限*/
void Limit(int *motoA,int *motoB)
{
	if(*motoA>PWM_MAX)  *motoA=PWM_MAX;
	if(*motoA<PWM_MIN)  *motoA=PWM_MIN;
	
	if(*motoB>PWM_MAX)  *motoB=PWM_MAX;
	if(*motoB<PWM_MIN)  *motoB=PWM_MIN;
}

//串级pid期望速度限幅
void V_Limit(int *motoA,int *motoB,int max)
{
	if(*motoA>max)  *motoA=max;
	if(*motoA<-max)  *motoA=-max;
	
	if(*motoB>max)  *motoB=max;
	if(*motoB<-max)  *motoB=-max;
}


/**
 * 函数名:set_motor_disable
 * 描述:失能电机
 * 输入:无
 * 输出:无
 */
void Motor_Stop(void)
{
	Motor_Rotaton(0,0);
	HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_4);	
}

/**
 * 函数名:set_motor_disable
 * 描述:小车转向
 * 输入:转向角度：左转90、右转90、原地转180
 * 输出:无
 */
void Car_Spin(Trun_Choose Direction)
{
	Motor_Start();
	if(LEFT_90==Direction)
	{
		Motor_Rotaton(-3000,3000);
		HAL_Delay(600);
		
	}
	else if(RIGHT_90==Direction)
	{
		Motor_Rotaton(3000,-3000);
		HAL_Delay(600);
	}
	else if(SPIN_180==Direction)
	{
		Motor_Rotaton(3000,-3000);
		HAL_Delay(1100);
	}	
	Motor_Stop();
}
