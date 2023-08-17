#include "motor.h"



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


/**
 * ������:Load_Motor_PWM
 * ����:����PWM,������д��ʱ��
 * ����:MOTOR1_PWM-���ֵ������ó���PWMֵ��MOTOR2_PWM-���ֵ������ó���PWMֵ
 * ���:��
 */
void Load_Motor_PWM(int MOTOR1_PWM,int MOTOR2_PWM)
{
  MOTOR1_PWM=(MOTOR1_PWM>0)?MOTOR1_PWM:(-MOTOR1_PWM);
	MOTOR2_PWM=(MOTOR2_PWM>0)?MOTOR2_PWM:(-MOTOR2_PWM);
	
  MOTOR1_PWM=(MOTOR1_PWM>PWM_MAX)?PWM_MAX:MOTOR1_PWM;
	MOTOR2_PWM=(MOTOR2_PWM>PWM_MAX)?PWM_MAX:MOTOR2_PWM;	
	
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,MOTOR1_PWM);   //�Ѵ��ν�����PWMֵ�͸���ʱ��1��channel_1ͨ��.
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,MOTOR2_PWM);   //�Ѵ��ν�����PWMֵ�͸���ʱ��1��channel_1ͨ��.
}


/**
 * ������:set_motor_enable
 * ����:ʹ�ܵ��
 * ����:��
 * ���:��
 */
void set_motor_enable(void)
{
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);  //����MX���ú�ԭ��ͼ��������Ҫ��������TIM1��PWM���ͨ��1
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);  //����TIM1��PWM���ͨ��1
}

/**
 * ������:set_motor_disable
 * ����:ʧ�ܵ��
 * ����:��
 * ���:��
 */
void set_motor_disable(void)
{
	HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_4);	
}
void CarRun()	//	ǰ�� 
{
		Ain1=1,	Ain2=0;
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,2760);
		Bin1=1,	Bin2=0;
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,2700);
}

void CarBack()	//����
{
		Ain1=0,	Ain2=1;
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,2760);
		Bin1=0,	Bin2=1;
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,2700);
}

void CarStop()	//ֹͣ
{
		Ain1=0,	Ain2=0;
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,0);
		Bin1=0,	Bin2=0;
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,0);
}

void CarTurnRight()	//��ת
{
		Ain1=1,	Ain2=0;
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,2760);
		Bin1=0,	Bin2=1;
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,2700);
}

void CarTurnLeft()	//	��ת
{
		Ain1=0,	Ain2=1;
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,2760);
		Bin1=1,	Bin2=0;
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,2700);
}


