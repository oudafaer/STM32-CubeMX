#ifndef __DS18B20_H
#define __DS18B20_H 

#include "main.h"

#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2))
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr))
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum))

#define GPIOA_ODR_Addr    (GPIOA_BASE+12)
#define GPIOB_ODR_Addr    (GPIOB_BASE+12)
#define GPIOC_ODR_Addr    (GPIOC_BASE+12)
#define GPIOD_ODR_Addr    (GPIOD_BASE+12)
#define GPIOE_ODR_Addr    (GPIOE_BASE+12)
#define GPIOF_ODR_Addr    (GPIOF_BASE+12)
#define GPIOG_ODR_Addr    (GPIOG_BASE+12)

#define GPIOA_IDR_Addr    (GPIOA_BASE+8)
#define GPIOB_IDR_Addr    (GPIOB_BASE+8)
#define GPIOC_IDR_Addr    (GPIOC_BASE+8)
#define GPIOD_IDR_Addr    (GPIOD_BASE+8)
#define GPIOE_IDR_Addr    (GPIOE_BASE+8)
#define GPIOF_IDR_Addr    (GPIOF_BASE+8)
#define GPIOG_IDR_Addr    (GPIOG_BASE+8)

#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)

//IO��������
#define	DS18B20_DQ_OUT PBout(12) //���ݶ˿�
#define	DS18B20_DQ_IN  PBin(12)  //���ݶ˿�
   	
uint8_t DS18B20_Init(void);			//��ʼ��DS18B20
short DS18B20_Get_Temp(void);		//��ȡ�¶�
void DS18B20_Start(void);			//��ʼ�¶�ת��
void DS18B20_Write_Byte(uint8_t dat);//д��һ���ֽ�
uint8_t DS18B20_Read_Byte(void);	//����һ���ֽ�
uint8_t DS18B20_Read_Bit(void);		//����һ��λ
uint8_t DS18B20_Check(void);		//����Ƿ����DS18B20
void DS18B20_Rst(void);				//��λDS18B20
#endif
