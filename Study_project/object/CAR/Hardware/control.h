/* Define to prevent recursive inclusion --------------------------------------------------------------------------------*/
#ifndef __CONTROL_H
#define	__CONTROL_H

/* Includes -------------------------------------------------------------------------------------------------------------*/
#include "main.h"


/***************�ⲿ��������***************/
extern long int Temp_POS;//����С��Ŀ��λ�ñ���
extern int ReadEncode;
extern uint16_t adc1,adc2,adc_m;
extern uint8_t END_FLAG;

#define ENCODER_TIM_PERIOD (uint16_t)(65535)   //���ɴ���65535 ��ΪF103�Ķ�ʱ����16λ�ġ�


/***********************��������������**************************/

#define ACircleLeftEncode 1320	//һȦ1320
#define ACircleRightEncode 1320	//һȦ1320
#define ACircleEncoder ACircleLeftEncode 


/***************���ڳ��ӵĲ���****************/
#define WheelDiameter 0.066 //����С������ֱ��,6.6cm
#define CarWidth 0.194		//����С���������Ӽ�࣬19.4cm



/***************���������Ĳ���****************/
#define Rode_L 1000		//���������ȣ���λ����
#define Rode_Cilcle 47  //����С������һ�����õ�Ȧ��



/***************�ⲿ��������***************/
extern void MoveSpeed(int NowEncodeSpdL,int NowEncodeSpdR,float TarSpdL,float TarSpdR);//����С������Ŀ���ٶ�PID���ڵ�ǰ�ٶ�
extern void MoveDis(int NowEncodeLALL,int NowEncodeRALL,float TarDisL,float TarDisR);//����С������Ŀ�����PID���ڵ�ǰ�ٶ�
extern void TraceMove(int TraceDate,float TarSpeed);//����С��ѭ������
extern void TraceMoveWithDis(int TraceDate,float TarDis);//����Ŀ�����ѭ����ʻ������ʻĿ������ֹͣѭ��


#endif /* __MYCONFIG_H */

/*****************************************************END OF FILE*********************************************************/	
