#include "dht11.h"

/*
 *TIM3��ʱ��ʵ��us����ʱ
 */
void Delay_us(uint16_t delay)
{
	__HAL_TIM_DISABLE(&htim4);
	__HAL_TIM_SET_COUNTER(&htim4,0);
	__HAL_TIM_ENABLE(&htim4);
	uint16_t curCnt=0;
	while(1)
	{
		curCnt=__HAL_TIM_GET_COUNTER(&htim4);
		if(curCnt>=delay)
			break;
	}
	__HAL_TIM_DISABLE(&htim4);
}


/*
 * ����DHT11���ŷ���
 */
// ���output
void Dht11_DATA_OUT(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};

	  /*Configure GPIO pin : PB12 */
	  GPIO_InitStruct.Pin = GPIO_PIN_12;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

// ����input
void Dht11_DATA_IN(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};

	  /*Configure GPIO pin : PB12 */
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pin = GPIO_PIN_12;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}


/*
 * DHT11����
 */
//��λDHT11
void DHT11_Rst(void)
{
	Dht11_DATA_OUT();                                          //����Ϊ���
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);     //��������
	HAL_Delay(20);                                             //�ӳ�20ms
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);       //��������
	Delay_us(30);                                              //�ӳ�30us
}

//�ȴ�DHT11��Ӧ
//����ֵ��1����δ��⵽���ڣ�0�����⵽����
uint8_t DHT11_Check(void)
{
	uint8_t retry=0;
	Dht11_DATA_IN();                                           //����Ϊ����
	while(GPIO_PIN_SET==HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) && retry<100)
	{
		retry++;
		Delay_us(1);
	}
	if(retry>=100)
		return 1;
	else
		retry=0;

	while(GPIO_PIN_RESET==HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) && retry<100)
	{
		retry++;
		Delay_us(1);
	}
	if(retry>=100)
		return 1;
	return 0;
}

//��DHT11��ȡһ��λ
//����ֵ��1/0
uint8_t DHT11_Read_Bit(void)
{
	uint8_t retry=0;
	while(GPIO_PIN_SET==HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) && retry<100)
	{
		retry++;
		Delay_us(1);
	}
	retry=0;

	while(GPIO_PIN_RESET==HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) && retry<100)
	{
		retry++;
		Delay_us(1);
	}
	Delay_us(40);

	if(GPIO_PIN_SET==HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12))
		return 1;
	else
		return 0;
}

//��DHT11��ȡһ���ֽ�
//����ֵ����ȡ�����ֽ�����(8λ)
uint8_t DHT11_Read_Byte(void)
{
	uint8_t dat=0;
	for(uint8_t i=0;i<8;i++)
	{
		dat <<= 1;
		dat |= DHT11_Read_Bit();
	}
	return dat;
}

//��DHT11��ȡһ������
//humi��ʪ��ֵ��temp���¶�ֵ
//����ֵ��0����������1�����ȡʧ��
uint8_t DHT11_Read_Data(uint8_t* humi,uint8_t* temp)
{
	uint8_t buf[5];
	DHT11_Rst();
	if(DHT11_Check() == 0)
	{
		for(uint8_t i=0;i<5;i++)
			buf[i]=DHT11_Read_Byte();
		if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])
		{
			*humi=buf[0];       //����ʡ��С������
			*temp=buf[2];
		}
	}
	else
		return 1;
	return 0;
}
