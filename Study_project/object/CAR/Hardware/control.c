/* Includes -------------------------------------------------------------------------------------------------------------*/
#include "control.h"

#define pi 3.1415926

#define MAX_MOTOR_PWM 1500//����������ٶ�ռ�ձ�



/**
 * @brief      5ms��ʱ�������жϻص�����(���п��ƴ����ڴ˴�)
 * @param       htim:��ʱ�����ָ��
 * @note        �ú�����HAL_TIM_IRQHandler�лᱻ����
 * @retval      ��
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	
	if (htim->Instance == TIM3)
	{
		
		Encode_Left=Read_Pluse(2);//��ȡ���ֱ���������
		Encode_Right=Read_Pluse(4);//��ȡ���ֱ���������
		
		Encode_Left_ALL+=Encode_Left;//�����ۼ�ֵ
		Encode_Right_ALL+=Encode_Right;//�����ۼ�ֵ
		
		Encode_Speed=Encode_Right+Encode_Left;//ǰ���ٶ�
		Encode_Spin_Speed=Encode_Left-Encode_Right;//��ת�ٶ�
		
	}
	
}

float WheelOneCircleDis=WheelDiameter*pi;//����С����������һȦ�������


/*@brief:����pid������ߵ����Ŀ���ٶ�
 * @param:
 *        [in]int EncodeSpdL: ��ǰ��������������ֵ
 *        [in]float TarSpdL:��ߵ��Ŀ���ٶ�,����ٶ�Խ1.19m/s
 * @return: ������ߵ��������pwmռ�ձ�
 */
int ChangeSpeedMotorL(int NowEncodeSpdL,float TarSpdL)
{
	int pwm=0;
	int bias=0;
	int TarEncodeSpdL;
//	TarEncodeSpdL=(int)((TarSpdL*ACircleEncoder)/(WheelOneCircleDis)*0.005);//����Ŀ���ٶ����Ŀ�������ֵ
 	NowEncodeSpdL=NowEncodeSpdL*100;
	TarEncodeSpdL=(int)(((TarSpdL*0.005)/0.00015707963)*100);//����Ŀ���ٶ����Ŀ��������ٶ�		
	bias=TarEncodeSpdL-NowEncodeSpdL;
	pwm=PositionPIDToSpd(bias,SpdPdate);
	if(pwm>MAX_MOTOR_PWM)		pwm=MAX_MOTOR_PWM;//�޷�
	else if(pwm<-MAX_MOTOR_PWM)  pwm=-MAX_MOTOR_PWM;
 printf("TarEncodeSpdL=%d  NowEncodeSpdL=%d  bias=%d    ",TarEncodeSpdL,NowEncodeSpdL,bias);
	return pwm;
}

/*@brief:����pid�����ұߵ����Ŀ���ٶ�
 * @param:
 *        [in]int NowEncodeSpdR: ��ǰ�ҵ������������ֵ
 *        [in]float TarSpdR:�ұߵ��Ŀ���ٶ�,����ٶ�Խ1.27m/s
 * @return: �����ұߵ��������pwmռ�ձ�
 */
int ChangeSpeedMotorR(int NowEncodeSpdR,float TarSpdR)
{
	int pwm=0;
	int bias=0;
	int TarEncodeSpdR;
	NowEncodeSpdR=NowEncodeSpdR*100;
	TarEncodeSpdR=(int)(((TarSpdR*0.005)/0.00015707963)*100);//����Ŀ���ٶ����Ŀ��������ٶ�
	bias=TarEncodeSpdR-NowEncodeSpdR;
	pwm=PositionPIDToSpd(bias,SpdPdate);
	if(pwm>MAX_MOTOR_PWM)		pwm=MAX_MOTOR_PWM;//�޷�
	else if(pwm<-MAX_MOTOR_PWM)  pwm=-MAX_MOTOR_PWM;
	 printf("  TarR=%d  NowR=%d bias=%d  \r\n",TarEncodeSpdR,NowEncodeSpdR,bias);
	return pwm;
}


/*@brief:����С����Ŀ�����pid������ߵ���ٶ�
 * @param:
 *        [in]int NowEncodeLALL: ��ǰ���������������
 *        [in]float TarDis:��ߵ��Ŀ����룬0-10M
 * @return: ������ߵ��������pwmռ�ձ�
 */
int ChangeDisSpeedMotorL(int NowEncodeLALL,float TarDis)
{
	int pwm=0;
	int bias=0;
	int TarEncodeLALL;
	TarEncodeLALL=(int)(((TarDis/WheelOneCircleDis)*ACircleEncoder)+0.5f);//����Ŀ��������Ŀ�������ֵ
	bias=NowEncodeLALL-TarEncodeLALL;
	pwm=PositionPID(bias,DisPdate);
	if(pwm>MAX_MOTOR_PWM)		pwm=MAX_MOTOR_PWM;//�޷�
	else if(pwm<-MAX_MOTOR_PWM)  pwm=-MAX_MOTOR_PWM;
	return pwm;
}

/*@brief:����С����Ŀ�����pid�����ұߵ���ٶ�
 * @param:
 *        [in]int NowEncodeRALL: ��ǰ�ҵ�������������
 *        [in]float TarDis:��ߵ��Ŀ����룬0-10M
 * @return: �����ұߵ��������pwmռ�ձ�
 */
int ChangeDisSpeedMotorR(int NowEncodeRALL,float TarDis)
{
	int pwm=0;
	int bias=0;
	int TarEncodeRALL;
	TarEncodeRALL=(int)(((TarDis/WheelOneCircleDis)*ACircleEncoder)+0.5f);//����Ŀ��������Ŀ�������ֵ
	bias=NowEncodeRALL-TarEncodeRALL;
	pwm=PositionPID2(bias,DisPdate);
	if(pwm>MAX_MOTOR_PWM)		pwm=MAX_MOTOR_PWM;//�޷�
	else if(pwm<-MAX_MOTOR_PWM)  pwm=-MAX_MOTOR_PWM;
	return pwm;
}


/*@brief:����ѭ��������pid����С��ת��ʹС�����ں����м�
 * @param:
 *        [in]int TraceDate: ѭ�������������ֵ
 * @return: ���ص��ڵ���ٶȵ�ת��pwm
 */
int ChangeTraceTurn(int TraceDate)
{
	int pwm=0;
	int bias;
	bias=-TraceDate;
	pwm=PositionPID(bias,TraceTurnPdate);
	if(pwm>MAX_MOTOR_PWM)		pwm=MAX_MOTOR_PWM;//�޷�
	else if(pwm<-MAX_MOTOR_PWM)  pwm=-MAX_MOTOR_PWM;
	return pwm;
}


/*@brief:ͨ��PD����������С������һ���ľ���
 * @param:
 *        [in]float NowEncodeLALL: ��ǰ���ֱ����������
 *        [in]float NowEncodeRALL: ��ǰ���ֱ����������
 *        [in]float TarDisL: ��ߵ��Ŀ����룬0-10M
 *        [in]float TarDisR:�ұߵ��Ŀ����룬0-10M
 *@return: ���߽�������0�����߷���1
 */
void MoveDis(int NowEncodeLALL,int NowEncodeRALL,float TarDisL,float TarDisR)
{
	int dislpwm,disrpwm;
	dislpwm=ChangeDisSpeedMotorL(NowEncodeLALL,TarDisL);
	disrpwm=ChangeDisSpeedMotorR(NowEncodeRALL,TarDisR);
	if(abs(dislpwm)<200) dislpwm=0;//��ֹ���ת�����պĵ�
	if(abs(disrpwm)<200) disrpwm=0;
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,dislpwm);   //�Ѵ��ν�����PWMֵ�͸���ʱ��1��channel_1ͨ��.
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,dislpwm);   //�Ѵ��ν�����PWMֵ�͸���ʱ��1��channel_1ͨ��.


}


/*@brief:С���ٶȵ�pid���ƺ�����ͨ���ٶ�Pi�ٶȿ��������ڣ�ʹС�����ﵽ�趨�ٶ�
 * @param:
 *        [in]float NowEncodeSpdL: ��ǰ���ֱ������ٶ�ֵ
 *        [in]float NowEncodeSpdR: ��ǰ���ֱ������ٶ�ֵ
 *        [in]float TarSpdL: ���ֵ��Ŀ���ٶȣ�����ٶ�Խ1.19m/s
 *        [in]float TarSpdR:���ֵ��Ŀ���ٶ�,����ٶ�Խ1.27m/s
 *@return: ���߽�������0�����߷���1
 */
void MoveSpeed(int NowEncodeSpdL,int NowEncodeSpdR,float TarSpdL,float TarSpdR)
{
	int spdlpwm,spdrpwm;
	spdlpwm=ChangeSpeedMotorL(NowEncodeSpdL,TarSpdL);
	spdrpwm=ChangeSpeedMotorR(NowEncodeSpdR,TarSpdR);
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,1750+spdlpwm);   //�Ѵ��ν�����PWMֵ�͸���ʱ��1��channel_1ͨ��.
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,1800+spdrpwm);   //�Ѵ��ν�����PWMֵ�͸���ʱ��1��channel_1ͨ��.

	
	printf("L:%d R: %d\r\n",spdlpwm,spdrpwm);
}

/*@brief: ��С������ѭ��������
 *@param:
 *        [in]TraceDate: ѭ�������������ֵ
 *        [in]TarSpeed:ѭ����Ŀ���ٶ�,�ٶȴ�С0-1.14m/s
 *@return: ����Ŀ��㷵��1�����򷵻�0
 */
void TraceMove(int TraceDate,float TarSpeed)
{
	int turnpwm=0;
//	int spdpwml=0,spdpwmr=0;

//	
//	turnpwm=ChangeTraceTurn(TraceDate);//ת��PID  turnpwmƫ��Ϊ����ƫ��Ϊ��
//	printf("turnpwm=%d\r\n",turnpwm);
//	spdpwml=ChangeSpeedMotorL(Encode_Left,TarSpeed);
//	spdpwmr=ChangeSpeedMotorR(Encode_Right,TarSpeed);
//		
//	
//	pwmr=turnpwm+spdpwmr;
//	if(pwmr>MAX_MOTOR_PWM)		pwmr=MAX_MOTOR_PWM;//�޷�
//	else if(pwmr<-MAX_MOTOR_PWM)  pwmr=-MAX_MOTOR_PWM;
//	pwml=-turnpwm+spdpwml;
//	if(pwml>MAX_MOTOR_PWM)		pwml=MAX_MOTOR_PWM;//�޷�
//	else if(pwml<-MAX_MOTOR_PWM)  pwml=-MAX_MOTOR_PWM;
  if(turnpwm>0)
	{
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,2500+turnpwm);   //�����ҵ��ռ�ձ�
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,2570);   
	}
		
	else if(turnpwm<0)
	{
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,2500);				//�����ҵ��ռ�ձ�
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,2570-turnpwm);			//��������ռ�ձ�
	
	}
	else if(turnpwm==0)
	{
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,2500);				//�����ҵ��ռ�ձ�
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,2570);   
	
	}
	
}


/*@brief: ����Ŀ�����ѭ����ʻ������ʻĿ������ֹͣѭ��
 *@param:
 *        [in]TraceDate: ѭ�������������ֵ
 *        [in]TarDis:С����ʻ��Ŀ�����,�����Χ0-10M
 *@return: ����Ŀ��㷵��1�����򷵻�0
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
	if(pwmr>MAX_MOTOR_PWM)		pwmr=MAX_MOTOR_PWM;//�޷�
	else if(pwmr<-MAX_MOTOR_PWM)  pwmr=-MAX_MOTOR_PWM;
	pwml=-turnpwm+spdlpwm;
	if(pwml>MAX_MOTOR_PWM)		pwml=MAX_MOTOR_PWM;//�޷�
	else if(pwml<-MAX_MOTOR_PWM)  pwml=-MAX_MOTOR_PWM;
	
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,pwmr);				//���õ��1ռ�ձ�
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,pwml);				//���õ��2ռ�ձ�

				
}


