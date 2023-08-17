#include "My_esp8266.h"
#include "string.h"
#include "usart.h"
 
void u2_printf(char* fmt);
char esp8266_send_cmd(char *cmd,char *ack,u16 waittime); 
 
 
void esp8266_test(void)//����
{
if(esp8266_send_cmd("AT","OK",50));
 
}
 
char esp8266_send_cmd(char *cmd,char *ack,u16 waittime)//����ָ��ͼ�����
{
 
	u2_printf(cmd);
	
	if(ack&&waittime)		
	{
			while(--waittime)	
			{
				HAL_Delay(10);
				if(strstr((const char*)RxBuffer,(const char*)ack)) //����on��LED0��
				{
					Uart2_Rx_Cnt=0;
					memset(RxBuffer,0x00,sizeof(RxBuffer)); //�������	
					return 1;
		 
				}
			}
 
	}
 
	return 0;
}
 
 
void esp8266_start_trans(void)//ESP8266��ʼ��
{
	
	esp8266_send_cmd("AT+CWMODE=2","OK",50);//����ΪAPģʽ
 
	esp8266_send_cmd("AT+RST","ready",20);//����
	
	HAL_Delay(1000);       
	HAL_Delay(1000);
	HAL_Delay(1000);
	HAL_Delay(1000);
	
	esp8266_send_cmd("AT+CWSAP=\"ESP8266\",\"12345678\",1,4","OK",200);//����WiFi���ơ����룬ģʽ
	esp8266_send_cmd("AT+CIPMUX=1","OK",20);//����͸��ģʽ
	esp8266_send_cmd("AT+CIPSERVER=1,8080","OK",200);//���ö˿�8080
	esp8266_send_cmd("AT+CIPSEND","OK",50);//��ʼ��������
}
 
uint8_t esp8266_quit_trans(void)//�˳�͸��ģʽ
{
	uint8_t result=1;
	u2_printf("+++");
	HAL_Delay(1000);					
	result=esp8266_send_cmd("AT","OK",20);
	return result;
 
}
 
 
void u2_printf(char* fmt)  
{  
 
	uint8_t num=0;
  char my_ch[50]={0};
	while(*fmt!=0)
	my_ch[num++]=*fmt++;
	
	my_ch[num++]='\r';
	my_ch[num++]='\n';
	
	HAL_UART_Transmit(&huart2, (uint8_t *)my_ch,num, 0xffff);
   while(HAL_UART_GetState(&huart2) == HAL_UART_STATE_BUSY_TX);
 
}
 
 


