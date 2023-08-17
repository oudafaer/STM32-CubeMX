#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "main.h"

void Encoder_Start(void);    //开启编码器
int Read_Pluse(int TIMx);   //从编码器读取电机转速数据
void Encoder_IRQHandler(void);  //清中断标志.



#endif

