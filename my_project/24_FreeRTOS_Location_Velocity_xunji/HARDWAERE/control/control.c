#include "control.h"


//串级oid期望速度值
int location_increment_target_val;
int location_increment_target_val2;
int PID_sd=0;//小车差速PID控制器的PWM输出值
uint8_t Stop_flag;
/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM8) 
	{
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  if (htim->Instance == TIM3)
  {
		TIM3->SR&=~(1<<0);//清除定时器4的计时标志，执行完TIM2中断服务函数里的操作后定时器会重新计时
		
		Encoder_Left=-Read_Speed(2);
		Encoder_Right=Read_Speed(4);  //编码器读出来的数据就是反馈回来的电机角度.
		
		Add_Encoder_Left+=Encoder_Left;
		Add_Encoder_Right+=Encoder_Right;
		
		Add_Encoder_Left=(Add_Encoder_Left+Add_Encoder_Right)/2;
		Add_Encoder_Right=(Add_Encoder_Left+Add_Encoder_Right)/2;
		
		
		
		
		Moto1=location_PID_realize(Add_Encoder_Left);
		Moto2=location_PID_realize2(Add_Encoder_Right);
		
		read_sensor();	
		PID_sd=-location_PID_Turn(error);	
		V_Limit(&Moto1,&Moto2,location_increment_target_val+PID_sd,location_increment_target_val2-PID_sd);
		
		if((GFP_abs(Add_Encoder_Left-location_PID.target_val)<3) ||(GFP_abs(Add_Encoder_Right-location_PID2.target_val)<3) )
		{
			Motor_Rotaton(0,0);
			Motor_Stop();
		}
		else
		{
//		Moto1=increment_PID_realize(Encoder_Left);	
			//速度环的期望值是位置环的输出
			increment_PID.target_val=Moto1;
			increment_PID2.target_val=Moto2;
			Moto1=increment_PID_realize(Encoder_Left);
			Moto2=increment_PID_realize2(Encoder_Right);
			Limit(&Moto1,&Moto2);
			Motor_Rotaton(Moto1,Moto2);
		}
		
		
		my_printf(1,"%.2f,%d,%.2f,%d\n",increment_PID.target_val,Encoder_Left,location_PID.target_val,Add_Encoder_Left);
		
  	
	}
}

void control_Init(void)
{
	HAL_TIM_Base_Start_IT(&htim3);
}


