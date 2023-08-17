#include "control.h"


//����oid�����ٶ�ֵ
int location_increment_target_val;


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
		Encoder_Left=-Read_Speed(2);
		Encoder_Right=Read_Speed(3);  //�����������������ݾ��Ƿ��������ĵ���Ƕ�.
		
		Add_Encoder_Left+=Encoder_Left;
		Add_Encoder_Right+=Encoder_Right;
		
		Moto1=location_PID_realize(Add_Encoder_Left);
		V_Limit(&Moto1,&Moto2,location_increment_target_val);
		
		if(GFP_abs(Add_Encoder_Left-location_PID.target_val)<3)
		{
			Motor_Rotaton(0,0);
		}
		else
		{
//				Moto1=increment_PID_realize(Encoder_Left);	
			//�ٶȻ�������ֵ��λ�û������
			increment_PID.target_val=Moto1;
			Moto1=increment_PID_realize(Encoder_Left);
			Limit(&Moto1,&Moto2);
			Motor_Rotaton(Moto1,Moto2);
		}
		my_printf(1,"%.2f,%d,%.2f,%d\n",increment_PID.target_val,Encoder_Left,location_PID.target_val,Add_Encoder_Left);
		
  	TIM4->SR&=~(1<<0);//�����ʱ��4�ļ�ʱ��־��ִ����TIM2�жϷ�������Ĳ�����ʱ�������¼�ʱ
	}
}

void control_Init(void)
{
	HAL_TIM_Base_Start_IT(&htim4);
}


