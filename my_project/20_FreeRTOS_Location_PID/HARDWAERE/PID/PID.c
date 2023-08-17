#include "pid.h"


location_PID_InitTypedef location_PID;
increment_PID_InitTypedef increment_PID;


void PID_Init(void)
{
	//位置式PID参数初始化
	location_PID.target_val=0.0;//目标值
	location_PID.actual_val=0.0;//实际值
	location_PID.err=0.0;//定义当前偏差值
	location_PID.err_last=0.0;//定义最后一个偏差值
	location_PID.integral=0.0;//定义累积积分值
	
	location_PID.Kp=2.2;//定义比例、积分、微分系数
	location_PID.Kd=0.01;
	location_PID.Ki=0;
	
	//增量式PID参数初始化
	increment_PID.target_val=0.0;//目标值
	increment_PID.actual_val=0.0;//实际值
	increment_PID.err=0.0;//定义当前偏差值
	increment_PID.err_last=0.0;//定义最后一个偏差值
	increment_PID.err_next=0.0;//定义下一个偏差值
	
	increment_PID.Kp=0.0;//定义比例、积分、微分系数
	increment_PID.Kd=0.0;
	increment_PID.Ki=0.0;
	
}


//位置式PID算法实现
float location_PID_realize(float temp_val)
{
	/* 目标值只在这里参与计算，计算目标值与实际值的误差 */
 location_PID.err=location_PID.target_val-temp_val;
	/* 积累误差 */
 location_PID.integral+=location_PID.err;
	if(location_PID.integral>=7200)location_PID.integral=7200;
	if(location_PID.integral<=-7200)location_PID.integral=-7200;
	/*PID 算法实现 */
	location_PID.actual_val=(location_PID.Kp*location_PID.err+
													location_PID.Ki*location_PID.integral+
													location_PID.Kd*(location_PID.err-location_PID.err_last));
	/* 传递误差 */
	location_PID.err_last=location_PID.err;
	/*返回当前实际值*/
	return location_PID.actual_val;
}

//增量式PID算法实现
float increment_PID_realize(float temp_val)
{
	/* 目标值只在这里参与计算，计算目标值与实际值的误差 */
 increment_PID.err=increment_PID.target_val-temp_val;
 /*PID 算法实现 */
 float increment_val = increment_PID.Kp*(increment_PID.err - increment_PID.err_next) + 
											 increment_PID.Ki*increment_PID.err+ 
											 increment_PID.Kd*(increment_PID.err - 2 * increment_PID.err_next + increment_PID.err_last);
 /* 累加 */
 increment_PID.actual_val += increment_val;
 /* 传递误差 */
 increment_PID.err_last = increment_PID.err_next;
 increment_PID.err_next = increment_PID.err;
 /* 返回的值是经过 pid 运算以后的值 */
 return increment_PID.actual_val;

}

