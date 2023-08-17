/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;

/* USER CODE BEGIN Private defines */
	#define USART_REC_LEN  			100  	//�����������ֽ��� 200
#define USART_DMA_TX_BUFFER_MAXIMUM			256    // DMA��������С
#define USART_DMA_RX_BUFFER_MAXIMUM			256    // DMA��������С
#define RXBUFFERSIZE   1 //�����С
extern uint8_t usart1_rx_buffer[USART_DMA_RX_BUFFER_MAXIMUM]; //����1��DMA���ջ�����
extern uint8_t usart1_tx_buffer[USART_DMA_TX_BUFFER_MAXIMUM]; //����1��DMA���ͻ�����
extern uint8_t usart1_rx_flag; //DMA���ճɹ���־ 0��δ���յ�/1,���յ��ȴ�����
extern uint16_t usart1_rx_len; //DMAһ�ο����жϽ��յ������ݳ���
extern uint8_t receive_u1_data[USART_DMA_RX_BUFFER_MAXIMUM];	  //DMA�������ݻ�����

#define EN_USART2_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
extern uint8_t usart2_rx_buffer[USART_DMA_RX_BUFFER_MAXIMUM]; //����1��DMA���ջ�����
extern uint8_t usart2_tx_buffer[USART_DMA_TX_BUFFER_MAXIMUM]; //����1��DMA���ͻ�����
extern uint8_t usart2_rx_flag; //DMA���ճɹ���־ 0��δ���յ�/1,���յ��ȴ�����
extern uint16_t usart2_rx_len; //DMAһ�ο����жϽ��յ������ݳ���
extern uint8_t receive_u2_data[USART_DMA_RX_BUFFER_MAXIMUM];	  //DMA�������ݻ�����
extern uint8_t aRxBuffer2[RXBUFFERSIZE];//HAL��USART����Buffer

extern uint8_t usart3_rx_buffer[USART_DMA_RX_BUFFER_MAXIMUM]; //����1��DMA���ջ�����
extern uint8_t usart3_tx_buffer[USART_DMA_TX_BUFFER_MAXIMUM]; //����1��DMA���ͻ�����
extern uint8_t usart3_rx_flag; //DMA���ճɹ���־ 0��δ���յ�/1,���յ��ȴ�����
extern uint16_t usart3_rx_len; //DMAһ�ο����жϽ��յ������ݳ���
extern uint8_t receive_u3_data[USART_DMA_RX_BUFFER_MAXIMUM];	  //DMA�������ݻ�����

extern uint8_t usart4_rx_buffer[USART_DMA_RX_BUFFER_MAXIMUM]; //����1��DMA���ջ�����
extern uint8_t usart4_tx_buffer[USART_DMA_TX_BUFFER_MAXIMUM]; //����1��DMA���ͻ�����
extern uint8_t usart4_rx_flag; //DMA���ճɹ���־ 0��δ���յ�/1,���յ��ȴ�����
extern uint16_t usart4_rx_len; //DMAһ�ο����жϽ��յ������ݳ���
extern uint8_t receive_u4_data[USART_DMA_RX_BUFFER_MAXIMUM];	  //DMA�������ݻ�����

extern uint8_t usart5_rx_buffer[USART_DMA_RX_BUFFER_MAXIMUM]; //����1��DMA���ջ�����
extern uint8_t usart5_tx_buffer[USART_DMA_TX_BUFFER_MAXIMUM]; //����1��DMA���ͻ�����
extern uint8_t usart5_rx_flag; //DMA���ճɹ���־ 0��δ���յ�/1,���յ��ȴ�����
extern uint16_t usart5_rx_len; //DMAһ�ο����жϽ��յ������ݳ���
extern uint8_t receive_u5_data[USART_DMA_RX_BUFFER_MAXIMUM];	  //DMA�������ݻ�����
/* USER CODE END Private defines */

void MX_UART4_Init(void);
void MX_UART5_Init(void);
void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);
void MX_USART3_UART_Init(void);

/* USER CODE BEGIN Prototypes */
void UART1_TX_DMA_Send(uint8_t *buffer, uint16_t length);
void printf1(const char *format, ...);
void printf2(char *format, ...);
void printf3(char *format, ...);
void printf4(char *format, ...);
void printf5(char *format, ...);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

