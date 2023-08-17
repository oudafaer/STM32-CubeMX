#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "main.h"


#define PWM_MAX  7200


#define  PWMA  TIM1->CCR1        /* PA8 */
#define  PWMB  TIM1->CCR4        /* PA11 */




#define Ain1  PBout(12)
#define Ain2  PBout(13)
#define Bin1  PBout(14)
#define Bin2  PBout(15)


/* �ṩ������C�ļ����õĺ��� --------------------------------------------------------------------------------------------*/
void Load_Motor_PWM(int MOTOR1_PWM,int MOTOR2_PWM);
void set_motor_enable(void);
void set_motor_disable(void);
int GFP_abs(int a);

void CarRun(void);	//	ǰ�� 
void CarBack(void);	//����
void CarStop(void);	//ֹͣ
void CarTurnRight(void);	//��ת
void CarTurnLeft(void);	//	��ת




#endif

