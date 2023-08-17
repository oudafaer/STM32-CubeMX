#include "motor.h"


int 	Moto1=0,Moto2=0;												 //������������ո��������PWM



void Motor_Start(void)     //Motor���������ӵ�PB12~15��ʼ����main()����MX��ִ����.
{
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);  //����MX���ú�ԭ��ͼ��������Ҫ��������TIM1��PWM���ͨ��1
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);  //����TIM1��PWM���ͨ��1
}

/**************************************************************************
�������ܣ���ֵ��PWM�Ĵ���
��ڲ���������PWM������PWM
����  ֵ����
**************************************************************************/
void Motor_Rotaton(int MotorA,int MotorB)
{
	//�ж������ţ���Ӧ����ת
	if(MotorA>0)	Ain1=1,Ain2=0;//��ת
	else 				Ain1=0,Ain2=1;//��ת
	//2.�о�PWMֵ
	if(MotorA)
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,GFP_abs(MotorA)+Dead_Voltage);   //�Ѵ��ν�����PWMֵ�͸���ʱ��1��channel_1ͨ��.
	else
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,0);   //�Ѵ��ν�����PWMֵ�͸���ʱ��1��channel_1ͨ��.
	
	
	
	if(MotorB>0)	Bin1=1,Bin2=0;
	else 				Bin1=0,Bin2=1;	
	if(MotorB)
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,GFP_abs(MotorB)+Dead_Voltage);
	else 
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,0);	
}

/**************************************************************************
�������ܣ�����ֵ����
��ڲ�����int
����  ֵ��unsigned int

**************************************************************************/
int GFP_abs(int a)
{ 		   
	int temp;
	temp = a>0?a:(-a);
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

//����pid�����ٶ��޷�
void V_Limit(int *motoA,int *motoB,int max)
{
	if(*motoA>max)  *motoA=max;
	if(*motoA<-max)  *motoA=-max;
	
	if(*motoB>max)  *motoB=max;
	if(*motoB<-max)  *motoB=-max;
}


/**
 * ������:set_motor_disable
 * ����:ʧ�ܵ��
 * ����:��
 * ���:��
 */
void Motor_Stop(void)
{
	Motor_Rotaton(0,0);
	HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_4);	
}

/**
 * ������:set_motor_disable
 * ����:С��ת��
 * ����:ת��Ƕȣ���ת90����ת90��ԭ��ת180
 * ���:��
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
