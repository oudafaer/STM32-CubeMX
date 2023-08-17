#include "pid.h"
#include "stdio.h"

pid_p pid;

//pidλ��ʽ
void PID_init()
{
//    printf("PID_init begin \n");
    pid.SetVoltage= 0.0;		  	// �趨��Ԥ�ڵ�ѹֵ
    pid.ActualVoltage= 0.0;			// adcʵ�ʵ�ѹֵ
    pid.err= 0.0;				    // ��ǰ��ʵ���������ƫ��
    pid.err_last=0.0;			    // ��һ�ε�ƫ��
    pid.voltage= 0.0;			    // ���Ƶ�ѹֵ
    pid.integral= 0.0;			  	// ����ֵ
    pid.Kp= 0.4;				    // ����ϵ��
    pid.Ki= 0.02;				    // ����ϵ��
    pid.Kd= 0.4;				    // ΢��ϵ��
//    printf("PID_init end \n");
}

float PID_realize( float v, float v_r)
{
    pid.SetVoltage = v;			// �̶���ѹֵ����
    pid.ActualVoltage = v_r;	// ʵ�ʵ�ѹ���� = ADC_Value * 3.3f/ 4096
    pid.err = pid.SetVoltage - pid.ActualVoltage;	//����ƫ��
    pid.integral += pid.err;						//�������
    pid.result = pid.Kp * pid.err + pid.Ki * pid.integral + pid.Kd * ( pid.err - pid.err_last);//λ��ʽ��ʽ
    pid.err_last = pid.err;				//��ס��һ�����
    return pid.result;
}

