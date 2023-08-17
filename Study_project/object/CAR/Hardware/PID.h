

#ifndef __PID_H
#define __PID_H

//����pid�ṹ��
struct _PID
{
	float kp;
	float ki;
	float kd;
};
typedef struct _PID PID;


/**********************�ⲿ��������*************************/
extern PID DisPdate;		//�������pid�����ṹ��
extern PID TraceTurnPdate;	//����ѭ��ת��pid�����ṹ��
extern PID SpdPdate;		//�����ٶ�pid�����ṹ��

/**********************�ⲿ��������*************************/
extern int PositionPID(float deviation,PID pid);
extern int PositionPID2(float deviation,PID pid);
extern int PositionPIDToSpd(float deviation,PID pid);
extern int PositionPIDToSpd2(float deviation,PID pid);




#endif



