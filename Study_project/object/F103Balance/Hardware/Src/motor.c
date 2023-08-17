#include "motor.h"

void Motor_Start(void)     //Motor控制所连接的PB12~15初始化在main()函数MX中执行了.
{
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);  //根据MX配置和原理图：这里需要开启的是TIM1的PWM输出通道1
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);  //开启TIM1的PWM输出通道1
}

void Stop(float angle,float voltage)
{
	if(angle>40 || angle<-40 || voltage<11.1)
	{
		Ain1=0;
		Ain2=0;
		Bin1=0;
		Bin2=0;
	}
}


void Motor_Run(int MotorA,int MotorB)
{
	//1.研究正负号，对应正反转
	if(MotorA>0)	Ain1=1,Ain2=0;//正转
	else 				Ain1=0,Ain2=1;//反转
	//2.研究PWM值
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,GFP_abs(MotorA));   //把传参进来的PWM值送给定时器1的channel_1通道.
	
	if(MotorB>0)	Bin1=1,Bin2=0;
	else 				Bin1=0,Bin2=1;	
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,GFP_abs(MotorB));
}


int GFP_abs(int a)
{
	int temp;
	temp=a>0?a:-a;
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



