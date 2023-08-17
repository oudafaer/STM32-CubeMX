#include "control.h"





int Speed_UP(int encoder_left,int encoder_right,int target)
{  
	static float Speed,Encoder_Least,Encoder;
	static float Encoder_Integral;
	//=============�ٶ�PI������=======================//	
	Encoder_Least =(Encoder_Left+Encoder_Right);//-target;                    //===��ȡ�����ٶ�ƫ��==�����ٶȣ����ұ�����֮�ͣ�-Ŀ���ٶ� 
	Encoder *= 0.8;		                                                //===һ�׵�ͨ�˲���       
	Encoder += Encoder_Least*0.2;	                                    //===һ�׵�ͨ�˲���    
	Encoder_Integral +=Encoder;                                       //===���ֳ�λ�� ����ʱ�䣺10ms
	Encoder_Integral=Encoder_Integral-target;                       //===����ң�������ݣ�����ǰ������
	if(Encoder_Integral>10000)  	Encoder_Integral=10000;             //===�����޷�
	if(Encoder_Integral<-10000)		Encoder_Integral=-10000;            //===�����޷�	
	Speed=Encoder*Speed_UP_KP+Encoder_Integral*Speed_UP_KD;        //===�ٶȿ���	
	if(pitch<-40||pitch>40) 			Encoder_Integral=0;     						//===����رպ��������
	return Speed;
}



int Turn_UP(int gyro_Z, int RC)
{
	int PWM_out;
		/*ת��Լ��*/
	if(RC==0)Turn_UP_Kd=Turn_UP_Kd;//��������ת��ָ�����ת��Լ��
	else Turn_UP_Kd=0;//������ת��ָ����յ�����ȥ��ת��Լ��
	
	PWM_out=Turn_UP_Kd*gyro_Z + Turn_UP_KP*RC;
	return PWM_out;

}

void  Get_RC()
{
	if((Fore==0)&&(Back==0))Target_Speed=0;
	if(Fore==1)Target_Speed--;
	if(Back==1)Target_Speed++;
	
	
	if((Left==0)&&(Right==0))Turn_Speed=0;
	if(Left==1)Turn_Speed+=30;
	if(Right==1)Turn_Speed-=30;
	
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch(GPIO_Pin)
	{
		case GPIO_PIN_5:
			
			LedFlash(50);
			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);								 //===�õ�����������
			MPU_DMP_Get_Data(&pitch,&roll,&yaw);										 //===�õ�ŷ���ǣ���̬�ǣ�������
		//1.�ɼ�����������&MPU6050�Ƕ���Ϣ��
			Encoder_Left=-Read_Speed(2);
			Encoder_Right=Read_Speed(3);  //�����������������ݾ��Ƿ��������ĵ���Ƕ�.
		
		
			Target_Speed=Target_Speed>SPEED_Y?SPEED_Y:(Target_Speed<-SPEED_Y?(-SPEED_Y):Target_Speed);//�޷�
			Turn_Speed=Turn_Speed>SPEED_Z?SPEED_Z:(Turn_Speed<-SPEED_Z?(-SPEED_Z):Turn_Speed);//�޷�( (20*100) * 100)
		

	
		//2.������ѹ��ջ������У�����������������
			Speed_Pwm=Speed_UP(Encoder_Left,Encoder_Right,Target_Speed);       //===�ٶȻ�PID����
			Turn_Pwm =Turn_UP(gyroz,Turn_Speed);        //===ת��PID����
			Moto1=-Speed_Pwm-Turn_Pwm;                 //===�������ֵ������PWM
			Moto2=-Speed_Pwm+Turn_Pwm;                 //===�������ֵ������PWM
			Limit(&Moto1,&Moto2);  																					 //===PWM�޷�
			Stop(pitch,12);																 //===���Ƕ��Լ���ѹ�Ƿ�����
			Motor_Run(Moto1,Moto2);                                    //===��ֵ��PWM�Ĵ���
		
	}
}


