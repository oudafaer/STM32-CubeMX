/**
  ******************************************************************************
  * @文件名 ：track.c
  * @文件说明：此文件为关于循迹车PID控制相关函数
  ******************************************************************************/
#include "pid.h"


#define MAX_MOTOR_PWM 1500//定义电机最大速度占空比

//定义距离pid参数结构体，在这里设置PID参数
PID DisPdate=
{
	0.3,		//赋值比例值kp  波动600
	0,			//赋值积分值ki
	0		//赋值微分值kd  0.8
};	

//定义速度pid参数结构体
PID SpdPdate=
{
	1.08,		//赋值比例值 kp -80
	0.065,		//赋值积分值 ki -10
	 0.001			//赋值微分值 kd
};	

//定义循迹转向pid参数结构体
PID TraceTurnPdate=
{
	0.11,			//赋值比例值kp 60
	0.01,			  //赋值积分值ki
	0			  //赋值微分值kd -45
};


/*@brief: 位置式PID控制器,注意：由于函数中有静态变量故控制一个只能使用一个PID控制器
 * @param:
 *        [in] float deviation: 和目标值得偏差
 *        [in] _PID pid: 位置式pid的参数
 * @return: 调节占空比的一个整形数
 */




int PositionPID(float deviation,PID pid)
{
	float Position_KP=pid.kp,Position_KI=pid.ki,Position_KD=pid.kd;
	int Pwm;
	static float Bias,Integral_bias,Last_Bias;
	Bias=deviation;                            		         //计算偏差
	Integral_bias+=Bias;	                                 //求出偏差的积分
	Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias); //位置式PID控制器
	Last_Bias=Bias;                                      	 //保存上一次偏差 
	return Pwm;    
}




/*@brief: 位置式PID控制器,注意：由于函数中有静态变量故控制一个只能使用一个PID控制器
 * @param:
 *        [in] float deviation: 和目标值得偏差
 *        [in] _PID pid: 位置式pid的参数
 * @return: 调节占空比的一个整形数
 */



int PositionPID2(float deviation,PID pid)
{
	float Position_KP=pid.kp,Position_KI=pid.ki,Position_KD=pid.kd;
	int Pwm;
	static float Bias,Integral_bias,Last_Bias;
	Bias=deviation;                         		         //计算偏差
	Integral_bias+=Bias;	                                 //求出偏差的积分
	Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias); //位置式PID控制器
	Last_Bias=Bias;                                      	 //保存上一次偏差 
	return Pwm;    
}


/*@brief: 为速度pid使用位置式PID控制器，对积分值进行限幅,注意：由于函数中有静态变量故控制一个只能使用一个PID控制器
 * @param:
 *        [in] float deviation: 和目标值得偏差
 *        [in] _PID pid: 位置式pid的参数
 * @return: 调节占空比的一个整形数
 */
int PositionPIDToSpd(float deviation,PID pid)
{
	float Position_KP=pid.kp,Position_KI=pid.ki,Position_KD=pid.kd;
	int Pwm;
	static float Bias,Integral_bias,Last_Bias,pwmKI=0;
	Bias=deviation;                         		         //计算偏差
	Integral_bias+=Bias;	                                 //求出偏差的积分
	pwmKI=Position_KI*Integral_bias;
	if(pwmKI>MAX_MOTOR_PWM) Integral_bias=MAX_MOTOR_PWM/Position_KI;
	Pwm=Position_KP*Bias+pwmKI+Position_KD*(Bias-Last_Bias);       //位置式PID控制器
	Last_Bias=Bias;                                      	 //保存上一次偏差 
	return Pwm;    
}




/*@brief: 为速度pid使用位置式PID控制器，对积分值进行限幅,注意：由于函数中有静态变量故控制一个只能使用一个PID控制器
 * @param:
 *        [in] float deviation: 和目标值得偏差
 *        [in] _PID pid: 位置式pid的参数
 * @return: 调节占空比的一个整形数
 */
int PositionPIDToSpd2(float deviation,PID pid)
{
	float Position_KP=pid.kp,Position_KI=pid.ki,Position_KD=pid.kd;
	int Pwm;
	static float Bias,Integral_bias,Last_Bias,pwmKI=0;
	Bias=deviation;                         		         //计算偏差
	Integral_bias+=Bias;	                                 //求出偏差的积分
	pwmKI=Position_KI*Integral_bias;
	if(pwmKI>MAX_MOTOR_PWM) Integral_bias=MAX_MOTOR_PWM/Position_KI;
	Pwm=Position_KP*Bias+pwmKI+Position_KD*(Bias-Last_Bias);       //位置式PID控制器
	Last_Bias=Bias;                                      	 //保存上一次偏差 
	return Pwm;    
}





