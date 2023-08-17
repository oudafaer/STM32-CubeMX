#ifndef __DHT11_H
#define __DHT11_H

#include "main.h"


/* USER CODE BEGIN PM */
void Delay_us(uint16_t delay);                   //ͨ��TIM3��ʱ��΢�뼶��ʱ
void Dht11_DATA_OUT(void);                       //�������ݽ�����Ϊ���
void Dht11_DATA_IN(void);                        //�������ݽ�����Ϊ����
void DHT11_Rst(void);                            //��λDHT11
uint8_t DHT11_Check(void);                       //DHT11״̬����
uint8_t DHT11_Read_Bit(void);                    //��DHT11һλ����
uint8_t DHT11_Read_Byte(void);                   //��DHT11һ�ֽ�����
uint8_t DHT11_Read_Data(uint8_t* humi,uint8_t* temp);     //DHT11������ʾ
/* USER CODE END PM */

#endif

