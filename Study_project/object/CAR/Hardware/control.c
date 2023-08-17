/* Includes -------------------------------------------------------------------------------------------------------------*/
#include "control.h"

#define pi 3.1415926

#define MAX_MOTOR_PWM 1500//定义电机最大速度占空比



/**
 * @brief      5ms定时器更新中断回调函数(所有控制代码在此处)
 * @param       htim:定时器句柄指针
 * @note        该函数在HAL_TIM_IRQHandler中会被调用
 * @retval      无
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	
	if (htim->Instance == TIM3)
	{
		
		Encode_Left=Read_Pluse(2);//读取左轮编码器数据
		Encode_Right=Read_Pluse(4);//读取右轮编码器数据
		
		Encode_Left_ALL+=Encode_Left;//左轮累计值
		Encode_Right_ALL+=Encode_Right;//右轮累计值
		
		Encode_Speed=Encode_Right+Encode_Left;//前进速度
		Encode_Spin_Speed=Encode_Left-Encode_Right;//旋转速度
		
	}
	
}

float WheelOneCircleDis=WheelDiameter*pi;//定义小车轮子行走一圈距离变量


/*@brief:根据pid调节左边电机到目标速度
 * @param:
 *        [in]int EncodeSpdL: 当前左电机编码器测速值
 *        [in]float TarSpdL:左边电机目标速度,最大速度越1.19m/s
 * @return: 返回左边电机计算后的pwm占空比
 */
int ChangeSpeedMotorL(int NowEncodeSpdL,float TarSpdL)
{
	int pwm=0;
	int bias=0;
	int TarEncodeSpdL;
//	TarEncodeSpdL=(int)((TarSpdL*ACircleEncoder)/(WheelOneCircleDis)*0.005);//根据目标速度求出目标编码器值
 	NowEncodeSpdL=NowEncodeSpdL*100;
	TarEncodeSpdL=(int)(((TarSpdL*0.005)/0.00015707963)*100);//根据目标速度求出目标编码器速度		
	bias=TarEncodeSpdL-NowEncodeSpdL;
	pwm=PositionPIDToSpd(bias,SpdPdate);
	if(pwm>MAX_MOTOR_PWM)		pwm=MAX_MOTOR_PWM;//限幅
	else if(pwm<-MAX_MOTOR_PWM)  pwm=-MAX_MOTOR_PWM;
 printf("TarEncodeSpdL=%d  NowEncodeSpdL=%d  bias=%d    ",TarEncodeSpdL,NowEncodeSpdL,bias);
	return pwm;
}

/*@brief:根据pid调节右边电机到目标速度
 * @param:
 *        [in]int NowEncodeSpdR: 当前右电机编码器测速值
 *        [in]float TarSpdR:右边电机目标速度,最大速度越1.27m/s
 * @return: 返回右边电机计算后的pwm占空比
 */
int ChangeSpeedMotorR(int NowEncodeSpdR,float TarSpdR)
{
	int pwm=0;
	int bias=0;
	int TarEncodeSpdR;
	NowEncodeSpdR=NowEncodeSpdR*100;
	TarEncodeSpdR=(int)(((TarSpdR*0.005)/0.00015707963)*100);//根据目标速度求出目标编码器速度
	bias=TarEncodeSpdR-NowEncodeSpdR;
	pwm=PositionPIDToSpd(bias,SpdPdate);
	if(pwm>MAX_MOTOR_PWM)		pwm=MAX_MOTOR_PWM;//限幅
	else if(pwm<-MAX_MOTOR_PWM)  pwm=-MAX_MOTOR_PWM;
	 printf("  TarR=%d  NowR=%d bias=%d  \r\n",TarEncodeSpdR,NowEncodeSpdR,bias);
	return pwm;
}


/*@brief:根据小车的目标距离pid调节左边电机速度
 * @param:
 *        [in]int NowEncodeLALL: 当前左电机编码器总里程
 *        [in]float TarDis:左边电机目标距离，0-10M
 * @return: 返回左边电机计算后的pwm占空比
 */
int ChangeDisSpeedMotorL(int NowEncodeLALL,float TarDis)
{
	int pwm=0;
	int bias=0;
	int TarEncodeLALL;
	TarEncodeLALL=(int)(((TarDis/WheelOneCircleDis)*ACircleEncoder)+0.5f);//根据目标距离求出目标编码器值
	bias=NowEncodeLALL-TarEncodeLALL;
	pwm=PositionPID(bias,DisPdate);
	if(pwm>MAX_MOTOR_PWM)		pwm=MAX_MOTOR_PWM;//限幅
	else if(pwm<-MAX_MOTOR_PWM)  pwm=-MAX_MOTOR_PWM;
	return pwm;
}

/*@brief:根据小车的目标距离pid调节右边电机速度
 * @param:
 *        [in]int NowEncodeRALL: 当前右电机编码器总里程
 *        [in]float TarDis:左边电机目标距离，0-10M
 * @return: 返回右边电机计算后的pwm占空比
 */
int ChangeDisSpeedMotorR(int NowEncodeRALL,float TarDis)
{
	int pwm=0;
	int bias=0;
	int TarEncodeRALL;
	TarEncodeRALL=(int)(((TarDis/WheelOneCircleDis)*ACircleEncoder)+0.5f);//根据目标距离求出目标编码器值
	bias=NowEncodeRALL-TarEncodeRALL;
	pwm=PositionPID2(bias,DisPdate);
	if(pwm>MAX_MOTOR_PWM)		pwm=MAX_MOTOR_PWM;//限幅
	else if(pwm<-MAX_MOTOR_PWM)  pwm=-MAX_MOTOR_PWM;
	return pwm;
}


/*@brief:根据循迹传感器pid调节小车转向使小车处于黑线中间
 * @param:
 *        [in]int TraceDate: 循迹传感器输出的值
 * @return: 返回调节电机速度的转向pwm
 */
int ChangeTraceTurn(int TraceDate)
{
	int pwm=0;
	int bias;
	bias=-TraceDate;
	pwm=PositionPID(bias,TraceTurnPdate);
	if(pwm>MAX_MOTOR_PWM)		pwm=MAX_MOTOR_PWM;//限幅
	else if(pwm<-MAX_MOTOR_PWM)  pwm=-MAX_MOTOR_PWM;
	return pwm;
}


/*@brief:通过PD控制器控制小车行走一定的距离
 * @param:
 *        [in]float NowEncodeLALL: 当前左轮编码器总里程
 *        [in]float NowEncodeRALL: 当前右轮编码器总里程
 *        [in]float TarDisL: 左边电机目标距离，0-10M
 *        [in]float TarDisR:右边电机目标距离，0-10M
 *@return: 行走结束返回0，否者返回1
 */
void MoveDis(int NowEncodeLALL,int NowEncodeRALL,float TarDisL,float TarDisR)
{
	int dislpwm,disrpwm;
	dislpwm=ChangeDisSpeedMotorL(NowEncodeLALL,TarDisL);
	disrpwm=ChangeDisSpeedMotorR(NowEncodeRALL,TarDisR);
	if(abs(dislpwm)<200) dislpwm=0;//防止电机转不动空耗电
	if(abs(disrpwm)<200) disrpwm=0;
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,dislpwm);   //把传参进来的PWM值送给定时器1的channel_1通道.
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,dislpwm);   //把传参进来的PWM值送给定时器1的channel_1通道.


}


/*@brief:小车速度的pid控制函数，通过速度Pi速度控制器调节，使小车最快达到设定速度
 * @param:
 *        [in]float NowEncodeSpdL: 当前左轮编码器速度值
 *        [in]float NowEncodeSpdR: 当前右轮编码器速度值
 *        [in]float TarSpdL: 左轮电机目标速度，最大速度越1.19m/s
 *        [in]float TarSpdR:右轮电机目标速度,最大速度越1.27m/s
 *@return: 行走结束返回0，否者返回1
 */
void MoveSpeed(int NowEncodeSpdL,int NowEncodeSpdR,float TarSpdL,float TarSpdR)
{
	int spdlpwm,spdrpwm;
	spdlpwm=ChangeSpeedMotorL(NowEncodeSpdL,TarSpdL);
	spdrpwm=ChangeSpeedMotorR(NowEncodeSpdR,TarSpdR);
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,1750+spdlpwm);   //把传参进来的PWM值送给定时器1的channel_1通道.
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,1800+spdrpwm);   //把传参进来的PWM值送给定时器1的channel_1通道.

	
	printf("L:%d R: %d\r\n",spdlpwm,spdrpwm);
}

/*@brief: 让小车根据循迹黑线走
 *@param:
 *        [in]TraceDate: 循迹传感器输出的值
 *        [in]TarSpeed:循迹的目标速度,速度大小0-1.14m/s
 *@return: 到达目标点返回1，否则返回0
 */
void TraceMove(int TraceDate,float TarSpeed)
{
	int turnpwm=0;
//	int spdpwml=0,spdpwmr=0;

//	
//	turnpwm=ChangeTraceTurn(TraceDate);//转向PID  turnpwm偏左为正，偏右为负
//	printf("turnpwm=%d\r\n",turnpwm);
//	spdpwml=ChangeSpeedMotorL(Encode_Left,TarSpeed);
//	spdpwmr=ChangeSpeedMotorR(Encode_Right,TarSpeed);
//		
//	
//	pwmr=turnpwm+spdpwmr;
//	if(pwmr>MAX_MOTOR_PWM)		pwmr=MAX_MOTOR_PWM;//限幅
//	else if(pwmr<-MAX_MOTOR_PWM)  pwmr=-MAX_MOTOR_PWM;
//	pwml=-turnpwm+spdpwml;
//	if(pwml>MAX_MOTOR_PWM)		pwml=MAX_MOTOR_PWM;//限幅
//	else if(pwml<-MAX_MOTOR_PWM)  pwml=-MAX_MOTOR_PWM;
  if(turnpwm>0)
	{
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,2500+turnpwm);   //设置右电机占空比
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,2570);   
	}
		
	else if(turnpwm<0)
	{
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,2500);				//设置右电机占空比
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,2570-turnpwm);			//设置左电机占空比
	
	}
	else if(turnpwm==0)
	{
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,2500);				//设置右电机占空比
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,2570);   
	
	}
	
}


/*@brief: 根据目标距离循迹行驶，当行驶目标距离后停止循迹
 *@param:
 *        [in]TraceDate: 循迹传感器输出的值
 *        [in]TarDis:小车行驶的目标距离,输出范围0-10M
 *@return: 到达目标点返回1，否则返回0
 */


void TraceMoveWithDis(int TraceDate,float TarDis)
{
	int turnpwm=0;
	int spdlpwm,spdrpwm;
	int pwml=0,pwmr=0;
	
	turnpwm=ChangeTraceTurn(TraceDate);
	
	spdlpwm=ChangeDisSpeedMotorL(Encode_Left_ALL,TarDis);
	spdrpwm=ChangeDisSpeedMotorR(Encode_Right_ALL,TarDis);
		
	pwmr=turnpwm+spdrpwm;
	if(pwmr>MAX_MOTOR_PWM)		pwmr=MAX_MOTOR_PWM;//限幅
	else if(pwmr<-MAX_MOTOR_PWM)  pwmr=-MAX_MOTOR_PWM;
	pwml=-turnpwm+spdlpwm;
	if(pwml>MAX_MOTOR_PWM)		pwml=MAX_MOTOR_PWM;//限幅
	else if(pwml<-MAX_MOTOR_PWM)  pwml=-MAX_MOTOR_PWM;
	
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,pwmr);				//设置电机1占空比
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,pwml);				//设置电机2占空比

				
}


