#include "pid.h"


location_PID_InitTypedef location_PID;
location_PID_InitTypedef location_PID2;
location_PID_InitTypedef location_PID3;


increment_PID_InitTypedef increment_PID;
increment_PID_InitTypedef increment_PID2;


void PID_Init(void)
{
	//λ��ʽPID������ʼ��
	location_PID.target_val=0.0;//Ŀ��ֵ
	location_PID.actual_val=0.0;//ʵ��ֵ
	location_PID.err=0.0;//���嵱ǰƫ��ֵ
	location_PID.err_last=0.0;//�������һ��ƫ��ֵ
	location_PID.integral=0.0;//�����ۻ�����ֵ
	
	location_PID.Kp=1.1;//������������֡�΢��ϵ��
	location_PID.Kd=0.001;
	location_PID.Ki=0.01;
	
	//����ʽPID������ʼ��
	increment_PID.target_val=0.0;//Ŀ��ֵ
	increment_PID.actual_val=0.0;//ʵ��ֵ
	increment_PID.err=0.0;//���嵱ǰƫ��ֵ
	increment_PID.err_last=0.0;//�������һ��ƫ��ֵ
	increment_PID.err_next=0.0;//������һ��ƫ��ֵ
	
	increment_PID.Kp=300.0;//������������֡�΢��ϵ��
	increment_PID.Kd=0.0;
	increment_PID.Ki=14.0;

	//λ��ʽPID������ʼ��
	location_PID2.target_val=0.0;//Ŀ��ֵ
	location_PID2.actual_val=0.0;//ʵ��ֵ
	location_PID2.err=0.0;//���嵱ǰƫ��ֵ
	location_PID2.err_last=0.0;//�������һ��ƫ��ֵ
	location_PID2.integral=0.0;//�����ۻ�����ֵ
	
	location_PID2.Kp=1.1;//������������֡�΢��ϵ��
	location_PID2.Kd=0.001;
	location_PID2.Ki=0.01;
	
	
	//λ��ʽPID������ʼ��
	location_PID3.target_val=0.0;//Ŀ��ֵ
	location_PID3.actual_val=0.0;//ʵ��ֵ
	location_PID3.err=0.0;//���嵱ǰƫ��ֵ
	location_PID3.err_last=0.0;//�������һ��ƫ��ֵ
	location_PID3.integral=0.0;//�����ۻ�����ֵ
	
	location_PID3.Kp=1.8;//������������֡�΢��ϵ��
	location_PID3.Kd=0.001;
	location_PID3.Ki=0.03;
	
	
	//����ʽPID������ʼ��
	increment_PID2.target_val=0.0;//Ŀ��ֵ
	increment_PID2.actual_val=0.0;//ʵ��ֵ
	increment_PID2.err=0.0;//���嵱ǰƫ��ֵ
	increment_PID2.err_last=0.0;//�������һ��ƫ��ֵ
	increment_PID2.err_next=0.0;//������һ��ƫ��ֵ
	
	increment_PID2.Kp=300.0;//������������֡�΢��ϵ��
	increment_PID2.Kd=0.0;
	increment_PID2.Ki=14.0;
	
	
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
//λ��ʽPID�㷨ʵ��
float location_PID_realize2(float temp_val)
{
	/* Ŀ��ֵֻ�����������㣬����Ŀ��ֵ��ʵ��ֵ����� */
 location_PID2.err=location_PID2.target_val-temp_val;
	/* ������� */
 location_PID2.integral+=location_PID2.err;
	if(location_PID2.integral>=7200)location_PID2.integral=7200;
	if(location_PID2.integral<=-7200)location_PID2.integral=-7200;
	/*PID �㷨ʵ�� */
	location_PID2.actual_val=(location_PID2.Kp*location_PID2.err+
													location_PID2.Ki*location_PID2.integral+
													location_PID2.Kd*(location_PID2.err-location_PID2.err_last));
	/* ������� */
	location_PID2.err_last=location_PID2.err;
	/*���ص�ǰʵ��ֵ*/
	return location_PID2.actual_val;
}

//����ʽPID�㷨ʵ��
float increment_PID_realize2(float temp_val)
{
	/* Ŀ��ֵֻ�����������㣬����Ŀ��ֵ��ʵ��ֵ����� */
 increment_PID2.err=increment_PID2.target_val-temp_val;
 /*PID �㷨ʵ�� */
 float increment_val = increment_PID2.Kp*(increment_PID2.err - increment_PID2.err_next) + 
											 increment_PID2.Ki*increment_PID2.err+ 
											 increment_PID2.Kd*(increment_PID2.err - 2 * increment_PID2.err_next + increment_PID2.err_last);
 /* �ۼ� */
 increment_PID2.actual_val += increment_val;
 /* ������� */
 increment_PID2.err_last = increment_PID2.err_next;
 increment_PID2.err_next = increment_PID2.err;
 /* ���ص�ֵ�Ǿ��� pid �����Ժ��ֵ */
 return increment_PID2.actual_val;

}


//λ��ʽPID�㷨ʵ��
float location_PID_Turn(float temp_val)
{
	/* Ŀ��ֵֻ�����������㣬����Ŀ��ֵ��ʵ��ֵ����� */
 location_PID3.err=location_PID3.target_val-temp_val;
	/* ������� */
 location_PID3.integral+=location_PID3.err;
	if(location_PID3.integral>=20)location_PID3.integral=20;
	if(location_PID3.integral<=-20)location_PID3.integral=-20;
	/*PID �㷨ʵ�� */
	location_PID3.actual_val=(location_PID3.Kp*location_PID3.err+
													location_PID3.Ki*location_PID3.integral+
													location_PID3.Kd*(location_PID3.err-location_PID3.err_last));
	/* ������� */
	location_PID3.err_last=location_PID3.err;
	/*���ص�ǰʵ��ֵ*/
	return location_PID3.actual_val;
}



