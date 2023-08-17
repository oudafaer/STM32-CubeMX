#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "main.h"


#define PWM_MAX  7200
#define PWM_MIN  -7200

#define  PWMA  TIM1->CCR1        /* PA8 */
#define  PWMB  TIM1->CCR4        /* PA11 */

#define Dead_Voltage 180


#define Ain1  PBout(12)
#define Ain2  PBout(13)
#define Bin1  PBout(14)
#define Bin2  PBout(15)

typedef enum
{
	LEFT_90,
	RIGHT_90,
	SPIN_180
	
}Trun_Choose;
extern int 	Moto1,Moto2;												 //计算出来的最终赋给电机的PWM



/* 提供给其他C文件调用的函数 --------------------------------------------------------------------------------------------*/
void Motor_Start(void);
void Motor_Stop(void);
void Motor_Rotaton(int MotorA,int MotorB);
int GFP_abs(int a);


void Limit(int *motoA,int *motoB);
void V_Limit(int *motoA,int *motoB,int max);


int GFP_abs(int a);
void Car_Spin(Trun_Choose Direction);


#endif

