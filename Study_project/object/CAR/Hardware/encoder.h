#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "main.h"

void Encoder_Start(void);    //����������
int Read_Pluse(int TIMx);   //�ӱ�������ȡ���ת������
void Encoder_IRQHandler(void);  //���жϱ�־.



#endif

