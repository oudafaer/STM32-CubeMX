/**
  ******************************************************************************
  * @�ļ��� ��track.c
  * @�ļ�˵�������ļ�Ϊ����ѭ����PID������غ���
  ******************************************************************************/
#include "pid.h"


#define MAX_MOTOR_PWM 1500//����������ٶ�ռ�ձ�

//�������pid�����ṹ�壬����������PID����
PID DisPdate=
{
	0.3,		//��ֵ����ֵkp  ����600
	0,			//��ֵ����ֵki
	0		//��ֵ΢��ֵkd  0.8
};	

//�����ٶ�pid�����ṹ��
PID SpdPdate=
{
	1.08,		//��ֵ����ֵ kp -80
	0.065,		//��ֵ����ֵ ki -10
	 0.001			//��ֵ΢��ֵ kd
};	

//����ѭ��ת��pid�����ṹ��
PID TraceTurnPdate=
{
	0.11,			//��ֵ����ֵkp 60
	0.01,			  //��ֵ����ֵki
	0			  //��ֵ΢��ֵkd -45
};


/*@brief: λ��ʽPID������,ע�⣺���ں������о�̬�����ʿ���һ��ֻ��ʹ��һ��PID������
 * @param:
 *        [in] float deviation: ��Ŀ��ֵ��ƫ��
 *        [in] _PID pid: λ��ʽpid�Ĳ���
 * @return: ����ռ�ձȵ�һ��������
 */




int PositionPID(float deviation,PID pid)
{
	float Position_KP=pid.kp,Position_KI=pid.ki,Position_KD=pid.kd;
	int Pwm;
	static float Bias,Integral_bias,Last_Bias;
	Bias=deviation;                            		         //����ƫ��
	Integral_bias+=Bias;	                                 //���ƫ��Ļ���
	Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias); //λ��ʽPID������
	Last_Bias=Bias;                                      	 //������һ��ƫ�� 
	return Pwm;    
}




/*@brief: λ��ʽPID������,ע�⣺���ں������о�̬�����ʿ���һ��ֻ��ʹ��һ��PID������
 * @param:
 *        [in] float deviation: ��Ŀ��ֵ��ƫ��
 *        [in] _PID pid: λ��ʽpid�Ĳ���
 * @return: ����ռ�ձȵ�һ��������
 */



int PositionPID2(float deviation,PID pid)
{
	float Position_KP=pid.kp,Position_KI=pid.ki,Position_KD=pid.kd;
	int Pwm;
	static float Bias,Integral_bias,Last_Bias;
	Bias=deviation;                         		         //����ƫ��
	Integral_bias+=Bias;	                                 //���ƫ��Ļ���
	Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias); //λ��ʽPID������
	Last_Bias=Bias;                                      	 //������һ��ƫ�� 
	return Pwm;    
}


/*@brief: Ϊ�ٶ�pidʹ��λ��ʽPID���������Ի���ֵ�����޷�,ע�⣺���ں������о�̬�����ʿ���һ��ֻ��ʹ��һ��PID������
 * @param:
 *        [in] float deviation: ��Ŀ��ֵ��ƫ��
 *        [in] _PID pid: λ��ʽpid�Ĳ���
 * @return: ����ռ�ձȵ�һ��������
 */
int PositionPIDToSpd(float deviation,PID pid)
{
	float Position_KP=pid.kp,Position_KI=pid.ki,Position_KD=pid.kd;
	int Pwm;
	static float Bias,Integral_bias,Last_Bias,pwmKI=0;
	Bias=deviation;                         		         //����ƫ��
	Integral_bias+=Bias;	                                 //���ƫ��Ļ���
	pwmKI=Position_KI*Integral_bias;
	if(pwmKI>MAX_MOTOR_PWM) Integral_bias=MAX_MOTOR_PWM/Position_KI;
	Pwm=Position_KP*Bias+pwmKI+Position_KD*(Bias-Last_Bias);       //λ��ʽPID������
	Last_Bias=Bias;                                      	 //������һ��ƫ�� 
	return Pwm;    
}




/*@brief: Ϊ�ٶ�pidʹ��λ��ʽPID���������Ի���ֵ�����޷�,ע�⣺���ں������о�̬�����ʿ���һ��ֻ��ʹ��һ��PID������
 * @param:
 *        [in] float deviation: ��Ŀ��ֵ��ƫ��
 *        [in] _PID pid: λ��ʽpid�Ĳ���
 * @return: ����ռ�ձȵ�һ��������
 */
int PositionPIDToSpd2(float deviation,PID pid)
{
	float Position_KP=pid.kp,Position_KI=pid.ki,Position_KD=pid.kd;
	int Pwm;
	static float Bias,Integral_bias,Last_Bias,pwmKI=0;
	Bias=deviation;                         		         //����ƫ��
	Integral_bias+=Bias;	                                 //���ƫ��Ļ���
	pwmKI=Position_KI*Integral_bias;
	if(pwmKI>MAX_MOTOR_PWM) Integral_bias=MAX_MOTOR_PWM/Position_KI;
	Pwm=Position_KP*Bias+pwmKI+Position_KD*(Bias-Last_Bias);       //λ��ʽPID������
	Last_Bias=Bias;                                      	 //������һ��ƫ�� 
	return Pwm;    
}





