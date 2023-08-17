#include "pid.h"


location_PID_InitTypedef location_PID;
location_PID_InitTypedef location_PID2;
location_PID_InitTypedef location_PID3;


increment_PID_InitTypedef increment_PID;
increment_PID_InitTypedef increment_PID2;


void PID_Init(void)
{
	//位置式PID参数初始化
	location_PID.target_val=0.0;//目标值
	location_PID.actual_val=0.0;//实际值
	location_PID.err=0.0;//定义当前偏差值
	location_PID.err_last=0.0;//定义最后一个偏差值
	location_PID.integral=0.0;//定义累积积分值
	
	location_PID.Kp=1.1;//定义比例、积分、微分系数
	location_PID.Kd=0.001;
	location_PID.Ki=0.01;
	
	//增量式PID参数初始化
	increment_PID.target_val=0.0;//目标值
	increment_PID.actual_val=0.0;//实际值
	increment_PID.err=0.0;//定义当前偏差值
	increment_PID.err_last=0.0;//定义最后一个偏差值
	increment_PID.err_next=0.0;//定义下一个偏差值
	
	increment_PID.Kp=300.0;//定义比例、积分、微分系数
	increment_PID.Kd=0.0;
	increment_PID.Ki=14.0;

	//位置式PID参数初始化
	location_PID2.target_val=0.0;//目标值
	location_PID2.actual_val=0.0;//实际值
	location_PID2.err=0.0;//定义当前偏差值
	location_PID2.err_last=0.0;//定义最后一个偏差值
	location_PID2.integral=0.0;//定义累积积分值
	
	location_PID2.Kp=1.1;//定义比例、积分、微分系数
	location_PID2.Kd=0.001;
	location_PID2.Ki=0.01;
	
	
	//位置式PID参数初始化
	location_PID3.target_val=0.0;//目标值
	location_PID3.actual_val=0.0;//实际值
	location_PID3.err=0.0;//定义当前偏差值
	location_PID3.err_last=0.0;//定义最后一个偏差值
	location_PID3.integral=0.0;//定义累积积分值
	
	location_PID3.Kp=1.8;//定义比例、积分、微分系数
	location_PID3.Kd=0.001;
	location_PID3.Ki=0.03;
	
	
	//增量式PID参数初始化
	increment_PID2.target_val=0.0;//目标值
	increment_PID2.actual_val=0.0;//实际值
	increment_PID2.err=0.0;//定义当前偏差值
	increment_PID2.err_last=0.0;//定义最后一个偏差值
	increment_PID2.err_next=0.0;//定义下一个偏差值
	
	increment_PID2.Kp=300.0;//定义比例、积分、微分系数
	increment_PID2.Kd=0.0;
	increment_PID2.Ki=14.0;
	
	
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
//位置式PID算法实现
float location_PID_realize2(float temp_val)
{
	/* 目标值只在这里参与计算，计算目标值与实际值的误差 */
 location_PID2.err=location_PID2.target_val-temp_val;
	/* 积累误差 */
 location_PID2.integral+=location_PID2.err;
	if(location_PID2.integral>=7200)location_PID2.integral=7200;
	if(location_PID2.integral<=-7200)location_PID2.integral=-7200;
	/*PID 算法实现 */
	location_PID2.actual_val=(location_PID2.Kp*location_PID2.err+
													location_PID2.Ki*location_PID2.integral+
													location_PID2.Kd*(location_PID2.err-location_PID2.err_last));
	/* 传递误差 */
	location_PID2.err_last=location_PID2.err;
	/*返回当前实际值*/
	return location_PID2.actual_val;
}

//增量式PID算法实现
float increment_PID_realize2(float temp_val)
{
	/* 目标值只在这里参与计算，计算目标值与实际值的误差 */
 increment_PID2.err=increment_PID2.target_val-temp_val;
 /*PID 算法实现 */
 float increment_val = increment_PID2.Kp*(increment_PID2.err - increment_PID2.err_next) + 
											 increment_PID2.Ki*increment_PID2.err+ 
											 increment_PID2.Kd*(increment_PID2.err - 2 * increment_PID2.err_next + increment_PID2.err_last);
 /* 累加 */
 increment_PID2.actual_val += increment_val;
 /* 传递误差 */
 increment_PID2.err_last = increment_PID2.err_next;
 increment_PID2.err_next = increment_PID2.err;
 /* 返回的值是经过 pid 运算以后的值 */
 return increment_PID2.actual_val;

}


//位置式PID算法实现
float location_PID_Turn(float temp_val)
{
	/* 目标值只在这里参与计算，计算目标值与实际值的误差 */
 location_PID3.err=location_PID3.target_val-temp_val;
	/* 积累误差 */
 location_PID3.integral+=location_PID3.err;
	if(location_PID3.integral>=20)location_PID3.integral=20;
	if(location_PID3.integral<=-20)location_PID3.integral=-20;
	/*PID 算法实现 */
	location_PID3.actual_val=(location_PID3.Kp*location_PID3.err+
													location_PID3.Ki*location_PID3.integral+
													location_PID3.Kd*(location_PID3.err-location_PID3.err_last));
	/* 传递误差 */
	location_PID3.err_last=location_PID3.err;
	/*返回当前实际值*/
	return location_PID3.actual_val;
}



