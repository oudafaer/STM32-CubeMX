/* Define to prevent recursive inclusion --------------------------------------------------------------------------------*/
#ifndef __CONTROL_H
#define	__CONTROL_H

/* Includes -------------------------------------------------------------------------------------------------------------*/
#include "main.h"


/***************外部变量声明***************/
extern long int Temp_POS;//定义小车目标位置变量
extern int ReadEncode;
extern uint16_t adc1,adc2,adc_m;
extern uint8_t END_FLAG;

#define ENCODER_TIM_PERIOD (uint16_t)(65535)   //不可大于65535 因为F103的定时器是16位的。


/***********************编码器参数定义**************************/

#define ACircleLeftEncode 1320	//一圈1320
#define ACircleRightEncode 1320	//一圈1320
#define ACircleEncoder ACircleLeftEncode 


/***************关于车子的参数****************/
#define WheelDiameter 0.066 //定义小车轮子直径,6.6cm
#define CarWidth 0.194		//定义小车两个轮子间距，19.4cm



/***************关于赛道的参数****************/
#define Rode_L 1000		//定义轨道长度，单位厘米
#define Rode_Cilcle 47  //定义小车走完一趟所用的圈数



/***************外部函数声明***************/
extern void MoveSpeed(int NowEncodeSpdL,int NowEncodeSpdR,float TarSpdL,float TarSpdR);//控制小车根据目标速度PID调节当前速度
extern void MoveDis(int NowEncodeLALL,int NowEncodeRALL,float TarDisL,float TarDisR);//控制小车根据目标距离PID调节当前速度
extern void TraceMove(int TraceDate,float TarSpeed);//控制小车循迹函数
extern void TraceMoveWithDis(int TraceDate,float TarDis);//根据目标距离循迹行驶，当行驶目标距离后停止循迹


#endif /* __MYCONFIG_H */

/*****************************************************END OF FILE*********************************************************/	
