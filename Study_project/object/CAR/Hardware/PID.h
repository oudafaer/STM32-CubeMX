

#ifndef __PID_H
#define __PID_H

//定义pid结构体
struct _PID
{
	float kp;
	float ki;
	float kd;
};
typedef struct _PID PID;


/**********************外部变量声明*************************/
extern PID DisPdate;		//定义距离pid参数结构体
extern PID TraceTurnPdate;	//定义循迹转向pid参数结构体
extern PID SpdPdate;		//定义速度pid参数结构体

/**********************外部函数声明*************************/
extern int PositionPID(float deviation,PID pid);
extern int PositionPID2(float deviation,PID pid);
extern int PositionPIDToSpd(float deviation,PID pid);
extern int PositionPIDToSpd2(float deviation,PID pid);




#endif



