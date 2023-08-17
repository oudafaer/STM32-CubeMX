#include "pid.h"


location_PID_InitTypedef location_PID;
increment_PID_InitTypedef increment_PID;


void PID_Init(void)
{
	//λ��ʽPID������ʼ��
	location_PID.target_val=0.0;//Ŀ��ֵ
	location_PID.actual_val=0.0;//ʵ��ֵ
	location_PID.err=0.0;//���嵱ǰƫ��ֵ
	location_PID.err_last=0.0;//�������һ��ƫ��ֵ
	location_PID.integral=0.0;//�����ۻ�����ֵ
	
	location_PID.Kp=2.2;//������������֡�΢��ϵ��
	location_PID.Kd=0.01;
	location_PID.Ki=0;
	
	//����ʽPID������ʼ��
	increment_PID.target_val=0.0;//Ŀ��ֵ
	increment_PID.actual_val=0.0;//ʵ��ֵ
	increment_PID.err=0.0;//���嵱ǰƫ��ֵ
	increment_PID.err_last=0.0;//�������һ��ƫ��ֵ
	increment_PID.err_next=0.0;//������һ��ƫ��ֵ
	
	increment_PID.Kp=0.0;//������������֡�΢��ϵ��
	increment_PID.Kd=0.0;
	increment_PID.Ki=0.0;
	
}


//λ��ʽPID�㷨ʵ��
float location_PID_realize(float temp_val)
{
	/* Ŀ��ֵֻ�����������㣬����Ŀ��ֵ��ʵ��ֵ����� */
 location_PID.err=location_PID.target_val-temp_val;
	/* ������� */
 location_PID.integral+=location_PID.err;
	if(location_PID.integral>=7200)location_PID.integral=7200;
	if(location_PID.integral<=-7200)location_PID.integral=-7200;
	/*PID �㷨ʵ�� */
	location_PID.actual_val=(location_PID.Kp*location_PID.err+
													location_PID.Ki*location_PID.integral+
													location_PID.Kd*(location_PID.err-location_PID.err_last));
	/* ������� */
	location_PID.err_last=location_PID.err;
	/*���ص�ǰʵ��ֵ*/
	return location_PID.actual_val;
}

//����ʽPID�㷨ʵ��
float increment_PID_realize(float temp_val)
{
	/* Ŀ��ֵֻ�����������㣬����Ŀ��ֵ��ʵ��ֵ����� */
 increment_PID.err=increment_PID.target_val-temp_val;
 /*PID �㷨ʵ�� */
 float increment_val = increment_PID.Kp*(increment_PID.err - increment_PID.err_next) + 
											 increment_PID.Ki*increment_PID.err+ 
											 increment_PID.Kd*(increment_PID.err - 2 * increment_PID.err_next + increment_PID.err_last);
 /* �ۼ� */
 increment_PID.actual_val += increment_val;
 /* ������� */
 increment_PID.err_last = increment_PID.err_next;
 increment_PID.err_next = increment_PID.err;
 /* ���ص�ֵ�Ǿ��� pid �����Ժ��ֵ */
 return increment_PID.actual_val;

}

