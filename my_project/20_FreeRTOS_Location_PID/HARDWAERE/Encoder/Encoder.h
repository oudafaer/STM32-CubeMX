#ifndef __ENCODER_H
#define __ENCODER_H

#include "main.h"

//编码器的物理分辨率，线数
#define RESOLUTION  11.0

//经过倍频之后的分辨率 
#define RESOLUTION_TOTAL  44.0 //RESOLUTION*4

//减速电机的减速比
#define REDUCTION_RATIO  30.0

//轮胎半径
#define WHEEL_R    3.25

//车长
#define CAR_LENGTH    25.0

//自旋90的距离
#define SPIN_90_DISTANCE    0.25*3.14*9

//俩轮距离
#define TWO_WHEEL_DISTANCE     18.0

//电机的最大转速
#define MOTOR_SPEED_MAX  176.0  //单位160rpm，1s能跑的最大距离53cm

//PID的计算周期
#define PID_COMPUTATION_PERIOD  200.0//单位是ms

#define PI 3.1415926


extern int Encoder_Left,Encoder_Right;        //左右编码器的脉冲计数
extern int Add_Encoder_Left,Add_Encoder_Right;        //左右编码器的脉冲计数



void Encoder_Start(void);    //开启编码器
int Read_Speed(int TIMx);   //从编码器读取电机转速数据
void Encoder_IRQHandler(void);  //清中断标志.
float Motp_Speed(int encoder_cnt);//功    能: 计算实际转速
long Num_Encoder_Cnt(float num);//功    能: 计算转数对应编码器脉冲数
int Encoder_Cnt_Location(int encoder_cnt);//功    能: 计算脉冲数对应电机位移
long Location_Encoder_Cnt(int Location);//功    能: 计算电机位移对应脉冲数







#endif
