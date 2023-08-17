#include "sr04.h"


float distant;      //测量距离
uint32_t measure_Buf[3] = {0};   //存放定时器计数值的数组
uint8_t  measure_Cnt = 0;    //状态标志位
uint32_t high_time;   //超声波模块返回的高电平时间


void SR04_GetData(void)
{
	switch (measure_Cnt)
	{
		case 0:
		 TRIG_H;												//超声波启动信号，输出一个30us的方波
		 delay_us(30);
		 TRIG_L;
			measure_Cnt++;
			__HAL_TIM_SET_CAPTUREPOLARITY(&htim3, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);	//设置捕获方式 
			HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);																							//启动输入捕获       或者: __HAL_TIM_ENABLE(&htim3);                                                                                    		
			break;
		case 3:
			high_time = measure_Buf[1]- measure_Buf[0];    //高电平时间
				my_printf(1,"\r\n----高电平时间-%d-us----\r\n",high_time);							
			distant=(high_time*0.034)/2;  //单位cm
				my_printf(1,"\r\n-检测距离为-%.2f-cm-\r\n",distant);          
			measure_Cnt = 0;  //清空标志位
					TIM3->CNT=0;     //清空计时器计数
			break;
				
	}
}

 
//===============================================中断回调函数
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)//
{
	
	if(TIM3 == htim->Instance)// 判断触发的中断的定时器为TIM3
	{
		switch(measure_Cnt)
		{
			case 1:
				measure_Buf[0] = HAL_TIM_ReadCapturedValue(&htim3,TIM_CHANNEL_1);//获取当前的捕获值.
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim3,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);  //设置为下降沿捕获
				measure_Cnt++;                                            
				break;              
			case 2:
				measure_Buf[1] = HAL_TIM_ReadCapturedValue(&htim3,TIM_CHANNEL_1);//获取当前的捕获值.
				HAL_TIM_IC_Stop_IT(&htim3,TIM_CHANNEL_1); //停止捕获   或者: __HAL_TIM_DISABLE(&htim5);
				measure_Cnt++;  
                         
		}
	
	}
	
}
