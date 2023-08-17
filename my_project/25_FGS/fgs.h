#ifndef __FGS_H
#define __FGS_H

#include "main.h"

//�������˲������ṹ��
typedef struct
{
    float prevData; // ��ǰ��ֵ
    float p;        // ����
    float q;        // �������
    float r;        // ��Ӧ�ٶȿ���
    float kGain;    // ����������
} KalmanParams;


int firstOrderFilter(int newValue, int oldValue, float a);
int middleValueFilter(int N,int* value_buf);
int averageFilter(int N, int* input);
int moveAverageFilter(int N,int input, int* value_buf, int* sum, int* curNum);
int LAverageFilter(int input, int* data, int* flag);
float KalmanFilter(int inData, KalmanParams* params);


#endif
