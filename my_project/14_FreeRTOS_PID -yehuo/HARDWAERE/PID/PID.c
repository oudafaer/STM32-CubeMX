#include "pid.h"


location_PID_InitTypedef location_PID;
increment_PID_InitTypedef increment_PID;


void PID_Init(void)
{
	//λ��ʽPID������ʼ��
	location_PID.target_val=200.0;//Ŀ��ֵ
	location_PID.actual_val=0.0;//ʵ��ֵ
	location_PID.err=0.0;//���嵱ǰƫ��ֵ
	location_PID.err_last=0.0;//�������һ��ƫ��ֵ
	location_PID.integral=0.0;//�����ۻ�����ֵ
	
	location_PID.Kp=0.6;//������������֡�΢��ϵ��
	location_PID.Kd=0.0;
	location_PID.Ki=0.1;
	
	
	//���Բ���ʹ�ã�����Ҫʱ���PID_ASSISTANT_EN����ע�͵��ͺ�
	#if defined(PID_ASSISTANT_EN)
  float pid_temp[3] = {location_PID.Kp, location_PID.Ki, location_PID.Kd};
  set_computer_value(SEND_P_I_D_CMD, CURVES_CH1, pid_temp, 3);     // ��ͨ�� 1 ���� P I D ֵ
  #endif
	

	
	
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
	/*PID �㷨ʵ�� */
	location_PID.actual_val=(location_PID.Kp*location_PID.err+
													location_PID.Ki*location_PID.integral+
													location_PID.Kd*(location_PID.err-location_PID.err_last));
	/* ������� */
	location_PID.err=location_PID.err_last;
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

/**
  * @brief  ����Ŀ��ֵ
  * @param  val		Ŀ��ֵ
	*	@note 	��
  * @retval ��
  */
void set_pid_target(float temp_val)
{
  location_PID.target_val = temp_val;    // ���õ�ǰ��Ŀ��ֵ
}

/**
  * @brief  ��ȡĿ��ֵ
  * @param  ��
	*	@note 	��
  * @retval Ŀ��ֵ
  */
float get_pid_target(void)
{
  return location_PID.target_val;    // ��ȡ��ǰ��Ŀ��ֵ
}

/**
  * @brief  ���ñ��������֡�΢��ϵ��
  * @param  p������ϵ�� P
  * @param  i������ϵ�� i
  * @param  d��΢��ϵ�� d
	*	@note 	��
  * @retval ��
  */
void set_p_i_d(float p, float i, float d)
{
  	location_PID.Kp = p;    // ���ñ���ϵ�� P
		location_PID.Ki = i;    // ���û���ϵ�� I
		location_PID.Kd = d;    // ����΢��ϵ�� D
}




