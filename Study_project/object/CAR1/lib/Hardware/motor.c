#include "motor.h"

void Motor_Start(void)     //Motor���������ӵ�PB12~15��ʼ����main()����MX��ִ����.
{
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);  //����MX���ú�ԭ��ͼ��������Ҫ��������TIM1��PWM���ͨ��1
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);  //����TIM1��PWM���ͨ��1
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
	//1.�о������ţ���Ӧ����ת
	if(MotorA>0)	Ain1=1,Ain2=0;//��ת
	else 				Ain1=0,Ain2=1;//��ת
	//2.�о�PWMֵ
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,GFP_abs(MotorA));   //�Ѵ��ν�����PWMֵ�͸���ʱ��1��channel_1ͨ��.
	
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




/*�޷�����:����PWM���󳬹����Ļ�е����*/
void Limit(int *motoA,int *motoB)
{
	if(*motoA>PWM_MAX)  *motoA=PWM_MAX;
	if(*motoA<PWM_MIN)  *motoA=PWM_MIN;
	
	if(*motoB>PWM_MAX)  *motoB=PWM_MAX;
	if(*motoB<PWM_MIN)  *motoB=PWM_MIN;
}



