#include "VOFA.h"

/*
 * 解析出RxBuffer中的数据
 * 返回解析得到的数据
 */
float Get_Data(void)
{
	
    uint8_t data_Start_Num = 0; // 记录数据位开始的地方
    uint8_t data_End_Num = 0; // 记录数据位结束的地方
    uint8_t data_Num = 0; // 记录数据位数
    uint8_t minus_Flag = 0; // 判断是不是负数
    float data_return = 0; // 解析得到的数据
    for(uint8_t i=0;i<200;i++) // 查找等号和感叹号的位置
    {
        if(RxBuffer[i] == '=') data_Start_Num = i + 1; // +1是直接定位到数据起始位
        if(RxBuffer[i] == '!')
        {
            data_End_Num = i - 1;
            break;
        }
    }
    if(RxBuffer[data_Start_Num] == '-') // 如果是负数
    {
        data_Start_Num += 1; // 后移一位到数据位
        minus_Flag = 1; // 负数flag
    }
    data_Num = data_End_Num - data_Start_Num + 1;
    if(data_Num == 6) // 数据共4位
    {
        data_return = (RxBuffer[data_Start_Num]-48)  + (RxBuffer[data_Start_Num+2]-48)*0.1f +
                (RxBuffer[data_Start_Num+3]-48)*0.01f+(RxBuffer[data_Start_Num+4]-48)*0.001f+(RxBuffer[data_Start_Num+5]-48)*0.0001f;
    }
    else if(data_Num == 7) // 数据共5位
    {
        data_return = (RxBuffer[data_Start_Num]-48)*10 + (RxBuffer[data_Start_Num+1]-48) + (RxBuffer[data_Start_Num+3]-48)*0.1f +
                (RxBuffer[data_Start_Num+4]-48)*0.01f+(RxBuffer[data_Start_Num+5]-48)*0.001f+(RxBuffer[data_Start_Num+6]-48)*0.0001f;
    }
    else if(data_Num == 8) // 数据共6位
    {
        data_return = (RxBuffer[data_Start_Num]-48)*100 + (RxBuffer[data_Start_Num+1]-48)*10 + (RxBuffer[data_Start_Num+2]-48) +
                (RxBuffer[data_Start_Num+4]-48)*0.1f + (RxBuffer[data_Start_Num+5]-48)*0.01f+(RxBuffer[data_Start_Num+6]-48)*0.001f+(RxBuffer[data_Start_Num+7]-48)*0.0001f;
    }
    else if(data_Num == 9) // 数据共6位
    {
        data_return = (RxBuffer[data_Start_Num]-48)*1000 + (RxBuffer[data_Start_Num+1]-48)*100 + (RxBuffer[data_Start_Num+2]-48)*10 +(RxBuffer[data_Start_Num+3]-48)+
                (RxBuffer[data_Start_Num+5]-48)*0.1f + (RxBuffer[data_Start_Num+6]-48)*0.01f+(RxBuffer[data_Start_Num+7]-48)*0.001f+(RxBuffer[data_Start_Num+8]-48)*0.0001f;
    }		
    if(minus_Flag == 1)  data_return = -data_return;
		
    return data_return;
}

/*
 * 根据串口信息进行PID调参
 */
void USART_PID_Adjust(void)
{
    float data_Get = Get_Data(); // 存放接收到的数据

		if(RxBuffer[0]=='P' && RxBuffer[1]=='1') // P1
				location_PID.Kp=data_Get;//定义比例、积分、微分系数           
		else if(RxBuffer[0]=='I' && RxBuffer[1]=='1') // I1
				location_PID.Ki=data_Get;//定义比例、积分、微分系数     
		else if(RxBuffer[0]=='D' && RxBuffer[1]=='1') // D1
				location_PID.Ki=data_Get;//定义比例、积分、微分系数   
		else if((RxBuffer[0]=='S' && RxBuffer[1]=='p') && RxBuffer[2]=='e') //目标1	
				location_PID.target_val=data_Get;
		
		else if(RxBuffer[0]=='P' && RxBuffer[1]=='2') // P2
				increment_PID.Kp=data_Get;
		else if(RxBuffer[0]=='I' && RxBuffer[1]=='2') // I2
				increment_PID.Ki=data_Get;
		else if(RxBuffer[0]=='D' && RxBuffer[1]=='2') // D2
				increment_PID.Kd=data_Get;
		else if((RxBuffer[0]=='P' && RxBuffer[1]=='o') && RxBuffer[2]=='s') //目标2
			 increment_PID.target_val=data_Get;
		
		else if((RxBuffer[0]=='R' && RxBuffer[1]=='E') && RxBuffer[2]=='S') //复位
			HAL_NVIC_SystemReset();          // 复位系统

}



