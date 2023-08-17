#ifndef __MOTOR_H
#define __MOTOR_H

#include "main.h"


void Motor_Start(void); 
void Stop(float angle,float voltage);
void Motor_Run(int MotorA,int MotorB);
int GFP_abs(int a);
void Limit(int *motoA,int *motoB);


#endif

