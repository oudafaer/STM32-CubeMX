#ifndef __ENCODER_H
#define __ENCODER_H

#include "main.h"

//������������ֱ��ʣ�����
#define RESOLUTION  11.0

//������Ƶ֮��ķֱ��� 
#define RESOLUTION_TOTAL  44.0 //RESOLUTION*4

//���ٵ���ļ��ٱ�
#define REDUCTION_RATIO  30.0

//��̥�뾶
#define WHEEL_R    3.25

//����
#define CAR_LENGTH    25.0

//����90�ľ���
#define SPIN_90_DISTANCE    0.25*3.14*9

//���־���
#define TWO_WHEEL_DISTANCE     18.0

//��������ת��
#define MOTOR_SPEED_MAX  176.0  //��λ160rpm��1s���ܵ�������53cm

//PID�ļ�������
#define PID_COMPUTATION_PERIOD  200.0//��λ��ms

#define PI 3.1415926


extern int Encoder_Left,Encoder_Right;        //���ұ��������������
extern int Add_Encoder_Left,Add_Encoder_Right;        //���ұ��������������



void Encoder_Start(void);    //����������
int Read_Speed(int TIMx);   //�ӱ�������ȡ���ת������
void Encoder_IRQHandler(void);  //���жϱ�־.
float Motp_Speed(int encoder_cnt);//��    ��: ����ʵ��ת��
long Num_Encoder_Cnt(float num);//��    ��: ����ת����Ӧ������������
int Encoder_Cnt_Location(int encoder_cnt);//��    ��: ������������Ӧ���λ��
long Location_Encoder_Cnt(int Location);//��    ��: ������λ�ƶ�Ӧ������







#endif
