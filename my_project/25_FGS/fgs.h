#ifndef __FGS_H
#define __FGS_H

#include "main.h"

//卡尔曼滤波参数结构体
typedef struct
{
    float prevData; // 先前数值
    float p;        // 误差方差
    float q;        // 控制误差
    float r;        // 响应速度控制
    float kGain;    // 卡尔曼增益
} KalmanParams;


int firstOrderFilter(int newValue, int oldValue, float a);
int middleValueFilter(int N,int* value_buf);
int averageFilter(int N, int* input);
int moveAverageFilter(int N,int input, int* value_buf, int* sum, int* curNum);
int LAverageFilter(int input, int* data, int* flag);
float KalmanFilter(int inData, KalmanParams* params);


#endif
