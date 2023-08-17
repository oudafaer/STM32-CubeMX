#include "control.h"

float Value= 0.0;

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
  if (htim->Instance == TIM3)
  {
		TIM3->SR&=~(1<<0);//清除定时器3的计时标志，执行完TIM2中断服务函数里的操作后定时器会重新计时
		Value=location_PID_realize(location_PID.actual_val);
		
		my_printf(1,"%.4f,%.4f\n",location_PID.target_val,Value);
		
  }

  if (htim->Instance == TIM4)
  {
		TIM4->SR&=~(1<<0);//清除定时器4的计时标志，执行完TIM2中断服务函数里的操作后定时器会重新计时

		
  }
}

void control_Init(void)
{
	HAL_TIM_Base_Start_IT(&htim3);
	HAL_TIM_Base_Start_IT(&htim4);
	
}


