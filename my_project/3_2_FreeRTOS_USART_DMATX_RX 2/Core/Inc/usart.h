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

extern UART_HandleTypeDef huart1;

/* USER CODE BEGIN Private defines */
#define USART_DMA_TX_BUFFER_MAXIMUM			256    // DMA缓冲区大小
#define USART_DMA_RX_BUFFER_MAXIMUM			256    // DMA缓冲区大小
extern uint8_t usart1_rx_buffer[USART_DMA_RX_BUFFER_MAXIMUM]; //串口1的DMA接收缓冲区
extern uint8_t usart1_tx_buffer[USART_DMA_TX_BUFFER_MAXIMUM]; //串口1的DMA发送缓冲区
extern uint8_t usart1_rx_flag; //DMA接收成功标志 0，未接收到/1,接收到等待处理
extern uint16_t usart1_rx_len; //DMA一次空闲中断接收到的数据长度
extern uint8_t receive_u1_data[USART_DMA_RX_BUFFER_MAXIMUM];	  //DMA接收数据缓存区
/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);

/* USER CODE BEGIN Prototypes */
void UART1_TX_DMA_Send(uint8_t *buffer, uint16_t length);
void printf1(const char *format, ...);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

