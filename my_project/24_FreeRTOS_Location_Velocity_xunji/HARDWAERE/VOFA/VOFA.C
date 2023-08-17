#include "VOFA.h"

/*
 * ������RxBuffer�е�����
 * ���ؽ����õ�������
 */
float Get_Data(void)
{
	
    uint8_t data_Start_Num = 0; // ��¼����λ��ʼ�ĵط�
    uint8_t data_End_Num = 0; // ��¼����λ�����ĵط�
    uint8_t data_Num = 0; // ��¼����λ��
    uint8_t minus_Flag = 0; // �ж��ǲ��Ǹ���
    float data_return = 0; // �����õ�������
    for(uint8_t i=0;i<200;i++) // ���ҵȺź͸�̾�ŵ�λ��
    {
        if(RxBuffer[i] == '=') data_Start_Num = i + 1; // +1��ֱ�Ӷ�λ��������ʼλ
        if(RxBuffer[i] == '!')
        {
            data_End_Num = i - 1;
            break;
        }
    }
    if(RxBuffer[data_Start_Num] == '-') // ����Ǹ���
    {
        data_Start_Num += 1; // ����һλ������λ
        minus_Flag = 1; // ����flag
    }
    data_Num = data_End_Num - data_Start_Num + 1;
    if(data_Num == 6) // ���ݹ�4λ
    {
        data_return = (RxBuffer[data_Start_Num]-48)  + (RxBuffer[data_Start_Num+2]-48)*0.1f +
                (RxBuffer[data_Start_Num+3]-48)*0.01f+(RxBuffer[data_Start_Num+4]-48)*0.001f+(RxBuffer[data_Start_Num+5]-48)*0.0001f;
    }
    else if(data_Num == 7) // ���ݹ�5λ
    {
        data_return = (RxBuffer[data_Start_Num]-48)*10 + (RxBuffer[data_Start_Num+1]-48) + (RxBuffer[data_Start_Num+3]-48)*0.1f +
                (RxBuffer[data_Start_Num+4]-48)*0.01f+(RxBuffer[data_Start_Num+5]-48)*0.001f+(RxBuffer[data_Start_Num+6]-48)*0.0001f;
    }
    else if(data_Num == 8) // ���ݹ�6λ
    {
        data_return = (RxBuffer[data_Start_Num]-48)*100 + (RxBuffer[data_Start_Num+1]-48)*10 + (RxBuffer[data_Start_Num+2]-48) +
                (RxBuffer[data_Start_Num+4]-48)*0.1f + (RxBuffer[data_Start_Num+5]-48)*0.01f+(RxBuffer[data_Start_Num+6]-48)*0.001f+(RxBuffer[data_Start_Num+7]-48)*0.0001f;
    }
    else if(data_Num == 9) // ���ݹ�6λ
    {
        data_return = (RxBuffer[data_Start_Num]-48)*1000 + (RxBuffer[data_Start_Num+1]-48)*100 + (RxBuffer[data_Start_Num+2]-48)*10 +(RxBuffer[data_Start_Num+3]-48)+
                (RxBuffer[data_Start_Num+5]-48)*0.1f + (RxBuffer[data_Start_Num+6]-48)*0.01f+(RxBuffer[data_Start_Num+7]-48)*0.001f+(RxBuffer[data_Start_Num+8]-48)*0.0001f;
    }		
    if(minus_Flag == 1)  data_return = -data_return;
		
    return data_return;
}

/*
 * ���ݴ�����Ϣ����PID����
 */
void USART_PID_Adjust(void)
{
    float data_Get = Get_Data(); // ��Ž��յ�������

		if(RxBuffer[0]=='P' && RxBuffer[1]=='1') // P1
				location_PID.Kp=data_Get;//������������֡�΢��ϵ��           
		else if(RxBuffer[0]=='I' && RxBuffer[1]=='1') // I1
				location_PID.Ki=data_Get;//������������֡�΢��ϵ��     
		else if(RxBuffer[0]=='D' && RxBuffer[1]=='1') // D1
				location_PID.Ki=data_Get;//������������֡�΢��ϵ��   
		else if((RxBuffer[0]=='S' && RxBuffer[1]=='p') && RxBuffer[2]=='e') //Ŀ��1	
				location_PID.target_val=data_Get;
		
		else if(RxBuffer[0]=='P' && RxBuffer[1]=='2') // P2
				increment_PID.Kp=data_Get;
		else if(RxBuffer[0]=='I' && RxBuffer[1]=='2') // I2
				increment_PID.Ki=data_Get;
		else if(RxBuffer[0]=='D' && RxBuffer[1]=='2') // D2
				increment_PID.Kd=data_Get;
		else if((RxBuffer[0]=='P' && RxBuffer[1]=='o') && RxBuffer[2]=='s') //Ŀ��2
			 increment_PID.target_val=data_Get;
		
		else if((RxBuffer[0]=='R' && RxBuffer[1]=='E') && RxBuffer[2]=='S') //��λ
			HAL_NVIC_SystemReset();          // ��λϵͳ

}


