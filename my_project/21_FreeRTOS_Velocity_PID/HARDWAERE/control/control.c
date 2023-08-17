#include "control.h"


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
  if (htim->Instance == TIM1) 
	{
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  if (htim->Instance == TIM4)
  {
		TIM4->SR&=~(1<<0);//清除定时器4的计时标志，执行完TIM2中断服务函数里的操作后定时器会重新计时
		
		
		Encoder_Left=-Read_Speed(2);
		Encoder_Right=Read_Speed(3);  //编码器读出来的数据就是反馈回来的电机角度.
		
		

		if(increment_PID.target_val == (GFP_abs(Encoder_Left)<5))
		{
			Motor_Rotaton(0,0);
		}
		else
		{
			Moto1=increment_PID_realize(Encoder_Left);
			Limit(&Moto1,&Moto2);  																					 //===PWM限幅
			Motor_Rotaton(Moto1,Moto2);
		}
		my_printf(1,"%.2f,%d\n",increment_PID.target_val,Encoder_Left);
  }
}

void control_Init(void)
{
	HAL_TIM_Base_Start_IT(&htim4);
}


