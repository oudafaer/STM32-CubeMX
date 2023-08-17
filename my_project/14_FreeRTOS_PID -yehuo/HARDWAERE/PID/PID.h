#ifndef __PID_H__
#define __PID_H__

#include "main.h"

typedef struct
{
	 float target_val; //目标值
	 float actual_val; //实际值
	 float err; //定义当前偏差值
	 float err_next; //定义下一个偏差值
	 float err_last; //定义最后一个偏差值
	 float Kp, Ki, Kd; //定义比例、积分、微分系数
}increment_PID_InitTypedef;


typedef struct
{
	 float target_val; //目标值
	 float actual_val; //实际值
	 float err; //定义当前偏差值
	 float err_last; //定义上一个偏差值
	 float Kp, Ki, Kd; //定义比例、积分、微分系数
	 float integral;
}location_PID_InitTypedef;


extern location_PID_InitTypedef location_PID;
extern increment_PID_InitTypedef increment_PID;


/* 提供给其他C文件调用的函数 --------------------------------------------------------------------------------------------*/
void PID_Init(void);
float location_PID_realize(float temp_val);
float increment_PID_realize(float temp_val);
void set_pid_target(float temp_val);
float get_pid_target(void);
void set_p_i_d(float p, float i, float d);

#endif

