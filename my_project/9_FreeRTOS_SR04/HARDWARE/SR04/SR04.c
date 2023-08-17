#include "sr04.h"


float distant;      //��������
uint32_t measure_Buf[3] = {0};   //��Ŷ�ʱ������ֵ������
uint8_t  measure_Cnt = 0;    //״̬��־λ
uint32_t high_time;   //������ģ�鷵�صĸߵ�ƽʱ��


void SR04_GetData(void)
{
	switch (measure_Cnt)
	{
		case 0:
		 TRIG_H;												//�����������źţ����һ��30us�ķ���
		 delay_us(30);
		 TRIG_L;
			measure_Cnt++;
			__HAL_TIM_SET_CAPTUREPOLARITY(&htim3, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);	//���ò���ʽ 
			HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);																							//�������벶��       ����: __HAL_TIM_ENABLE(&htim3);                                                                                    		
			break;
		case 3:
			high_time = measure_Buf[1]- measure_Buf[0];    //�ߵ�ƽʱ��
				my_printf(1,"\r\n----�ߵ�ƽʱ��-%d-us----\r\n",high_time);							
			distant=(high_time*0.034)/2;  //��λcm
				my_printf(1,"\r\n-������Ϊ-%.2f-cm-\r\n",distant);          
			measure_Cnt = 0;  //��ձ�־λ
					TIM3->CNT=0;     //��ռ�ʱ������
			break;
				
	}
}

 
//===============================================�жϻص�����
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)//
{
	
	if(TIM3 == htim->Instance)// �жϴ������жϵĶ�ʱ��ΪTIM3
	{
		switch(measure_Cnt)
		{
			case 1:
				measure_Buf[0] = HAL_TIM_ReadCapturedValue(&htim3,TIM_CHANNEL_1);//��ȡ��ǰ�Ĳ���ֵ.
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim3,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);  //����Ϊ�½��ز���
				measure_Cnt++;                                            
				break;              
			case 2:
				measure_Buf[1] = HAL_TIM_ReadCapturedValue(&htim3,TIM_CHANNEL_1);//��ȡ��ǰ�Ĳ���ֵ.
				HAL_TIM_IC_Stop_IT(&htim3,TIM_CHANNEL_1); //ֹͣ����   ����: __HAL_TIM_DISABLE(&htim5);
				measure_Cnt++;  
                         
		}
	
	}
	
}
