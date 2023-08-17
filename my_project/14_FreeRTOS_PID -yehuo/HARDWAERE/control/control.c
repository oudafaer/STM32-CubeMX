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
  if (htim->Instance == TIM3)
  {
		TIM3->SR&=~(1<<0);//�����ʱ��3�ļ�ʱ��־��ִ����TIM2�жϷ�������Ĳ�����ʱ�������¼�ʱ
		Value=location_PID_realize(location_PID.actual_val);
		
		
		//���Բ���ʹ�ã�����Ҫʱ���PID_ASSISTANT_EN����ע�͵��ͺ�
		#if defined (PID_ASSISTANT_EN)
		int temp = Value;    // ��λ����Ҫ����������ת��һ��
		set_computer_value(SEND_FACT_CMD,CURVES_CH1,&temp,1);
		temp=location_PID.target_val;
		set_computer_value(SEND_TARGET_CMD,CURVES_CH1,&temp,1);
		#endif
		
  }
}

void control_Init(void)
{
	HAL_TIM_Base_Start_IT(&htim3);
	HAL_TIM_Base_Start_IT(&htim4);
}


