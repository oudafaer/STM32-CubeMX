#include "control.h"





int Speed_UP(int encoder_left,int encoder_right,int target)
{  
	static float Speed,Encoder_Least,Encoder;
	static float Encoder_Integral;
	//=============速度PI控制器=======================//	
	Encoder_Least =(Encoder_Left+Encoder_Right);//-target;                    //===获取最新速度偏差==测量速度（左右编码器之和）-目标速度 
	Encoder *= 0.8;		                                                //===一阶低通滤波器       
	Encoder += Encoder_Least*0.2;	                                    //===一阶低通滤波器    
	Encoder_Integral +=Encoder;                                       //===积分出位移 积分时间：10ms
	Encoder_Integral=Encoder_Integral-target;                       //===接收遥控器数据，控制前进后退
	if(Encoder_Integral>10000)  	Encoder_Integral=10000;             //===积分限幅
	if(Encoder_Integral<-10000)		Encoder_Integral=-10000;            //===积分限幅	
	Speed=Encoder*Speed_UP_KP+Encoder_Integral*Speed_UP_KD;        //===速度控制	
	if(pitch<-40||pitch>40) 			Encoder_Integral=0;     						//===电机关闭后清除积分
	return Speed;
}



int Turn_UP(int gyro_Z, int RC)
{
	int PWM_out;
		/*转向约束*/
	if(RC==0)Turn_UP_Kd=Turn_UP_Kd;//若无左右转向指令，则开启转向约束
	else Turn_UP_Kd=0;//若左右转向指令接收到，则去掉转向约束
	
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
			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);								 //===得到陀螺仪数据
			MPU_DMP_Get_Data(&pitch,&roll,&yaw);										 //===得到欧拉角（姿态角）的数据
		//1.采集编码器数据&MPU6050角度信息。
			Encoder_Left=-Read_Speed(2);
			Encoder_Right=Read_Speed(3);  //编码器读出来的数据就是反馈回来的电机角度.
		
		
			Target_Speed=Target_Speed>SPEED_Y?SPEED_Y:(Target_Speed<-SPEED_Y?(-SPEED_Y):Target_Speed);//限幅
			Turn_Speed=Turn_Speed>SPEED_Z?SPEED_Z:(Turn_Speed<-SPEED_Z?(-SPEED_Z):Turn_Speed);//限幅( (20*100) * 100)
		

	
		//2.将数据压入闭环控制中，计算出控制输出量。
			Speed_Pwm=Speed_UP(Encoder_Left,Encoder_Right,Target_Speed);       //===速度环PID控制
			Turn_Pwm =Turn_UP(gyroz,Turn_Speed);        //===转向环PID控制
			Moto1=-Speed_Pwm-Turn_Pwm;                 //===计算左轮电机最终PWM
			Moto2=-Speed_Pwm+Turn_Pwm;                 //===计算右轮电机最终PWM
			Limit(&Moto1,&Moto2);  																					 //===PWM限幅
			Stop(pitch,12);																 //===检查角度以及电压是否正常
			Motor_Run(Moto1,Moto2);                                    //===赋值给PWM寄存器
		
	}
}


