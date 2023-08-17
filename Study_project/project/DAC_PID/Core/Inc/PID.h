#ifndef __PID_H__
#define __PID_H__
#include "main.h"

typedef struct
{
    float SetVoltage;	  	//�����趨ֵ
    float ActualVoltage;	//����ʵ��ֵ
    float err;			    //����ƫ��ֵ
    float err_last;		  	//������һ��ƫ��ֵ
    float Kp,Ki,Kd;		  	//������������֡�΢��ϵ��
    float result;		    //pid������
    float voltage;		  	//�����ѹֵ������ִ�����ı�����0-5v��ת 5-10v��ת
    float integral;		  	//�������ֵ
}pid_p; 

void PID_init( void);
float PID_realize( float v, float v_r);

#endif
