#ifndef __PID_H__
#define __PID_H__

#include "main.h"

typedef struct
{
	 float target_val; //Ŀ��ֵ
	 float actual_val; //ʵ��ֵ
	 float err; //���嵱ǰƫ��ֵ
	 float err_next; //������һ��ƫ��ֵ
	 float err_last; //�������һ��ƫ��ֵ
	 float Kp, Ki, Kd; //������������֡�΢��ϵ��
}increment_PID_InitTypedef;


typedef struct
{
	 float target_val; //Ŀ��ֵ
	 float actual_val; //ʵ��ֵ
	 float err; //���嵱ǰƫ��ֵ
	 float err_last; //������һ��ƫ��ֵ
	 float Kp, Ki, Kd; //������������֡�΢��ϵ��
	 float integral;
}location_PID_InitTypedef;


extern location_PID_InitTypedef location_PID;
extern increment_PID_InitTypedef increment_PID;


/* �ṩ������C�ļ����õĺ��� --------------------------------------------------------------------------------------------*/
void PID_Init(void);
float location_PID_realize(float temp_val);
float increment_PID_realize(float temp_val);
void set_pid_target(float temp_val);
float get_pid_target(void);
void set_p_i_d(float p, float i, float d);

#endif

