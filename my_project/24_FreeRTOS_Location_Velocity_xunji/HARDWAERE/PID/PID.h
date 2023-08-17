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


typedef struct
{
	float Turn_Kp;//ת����ٻ���Kp
	float Turn_Ki;//ת����ٻ���Ki
	float Turn_Kd;//ת����ٻ���Kd
	
}PID_InitTypedef;
extern PID_InitTypedef PID;


extern location_PID_InitTypedef location_PID;
extern increment_PID_InitTypedef increment_PID;
extern location_PID_InitTypedef location_PID2;
extern increment_PID_InitTypedef increment_PID2;

/* �ṩ������C�ļ����õĺ��� --------------------------------------------------------------------------------------------*/
void PID_Init(void);
float location_PID_realize(float temp_val);
float increment_PID_realize(float temp_val);

float location_PID_realize2(float temp_val);
float increment_PID_realize2(float temp_val);

float location_PID_Turn(float temp_val);


#endif

