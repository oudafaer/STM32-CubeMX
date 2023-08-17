/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "adc.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "oled.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "led.h"
#include "Encoder.h"
#include "motor.h"
#include "control.h"
	
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

//电压参数
extern float BatteryVoltage;  	

//串口参数
extern uint8_t Uart2_Data;  //串口2接收缓存量
extern uint8_t Fore,Back,Left,Right; //遥控运动参数



//MPU6050参数
extern float pitch,roll,yaw; 				//欧拉角(姿态角)
extern short aacx,aacy,aacz;			   //加速度传感器原始数据
extern short gyrox,gyroy,gyroz;			//陀螺仪原始数据

//电机参数
extern int PWM_MAX,PWM_MIN;      //PWM限幅变量
extern int Moto1,Moto2;	  


//编码器参数
extern int   Encoder_Left,Encoder_Right;         		 //左右编码器的脉冲计数



//PID期望参数



extern float Mechanical_angle;  //期望角度
extern int Target_Speed;//期望速度（俯仰）。用于控制小车前进后退及其速度。
extern float Turn_Speed;		//期望速度（偏航）


//PID系数参数
extern float Position_KP;
extern float Position_KI;
extern float Position_KD; 

extern float Incremental_KP;
extern float Incremental_KI;
extern float Incremental_KD;   /* 增量式PID系数 */

extern float Speed_UP_KP;               // 小车速度环PI参数
extern float Speed_UP_KD;

extern float Turn_UP_Kd;                   //转向环KP、KD
extern float Turn_UP_KP;



//三个PID环输出参数
extern int Balance_Pwm,Speed_Pwm,Turn_Pwm; //三环PWM输出变量

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */


//位带操作,实现51类似的GPIO控制功能
//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 


//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
 


//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入



//Ex_NVIC_Config专用定义
#define GPIO_A 0
#define GPIO_B 1
#define GPIO_C 2
#define GPIO_D 3
#define GPIO_E 4
#define GPIO_F 5
#define GPIO_G 6 

#define FTIR   1  //下降沿触发
#define RTIR   2  //上升沿触发




//JTAG模式设置定义
#define JTAG_SWD_DISABLE   0X02
#define SWD_ENABLE         0X01
#define JTAG_SWD_ENABLE    0X00	






/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
int fgetc(FILE *f);
int fputc(int ch, FILE *f);




/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define USB_PLUGIN_Pin GPIO_PIN_13
#define USB_PLUGIN_GPIO_Port GPIOC
#define LED_Pin GPIO_PIN_14
#define LED_GPIO_Port GPIOC
#define KEY_Pin GPIO_PIN_15
#define KEY_GPIO_Port GPIOC
#define VOLTAGE_Pin GPIO_PIN_0
#define VOLTAGE_GPIO_Port GPIOB
#define CCD_VAL_Pin GPIO_PIN_1
#define CCD_VAL_GPIO_Port GPIOB
#define AIN2_Pin GPIO_PIN_12
#define AIN2_GPIO_Port GPIOB
#define AIN1_Pin GPIO_PIN_13
#define AIN1_GPIO_Port GPIOB
#define BIN1_Pin GPIO_PIN_14
#define BIN1_GPIO_Port GPIOB
#define BIN2_Pin GPIO_PIN_15
#define BIN2_GPIO_Port GPIOB
#define PWMB_Pin GPIO_PIN_8
#define PWMB_GPIO_Port GPIOA
#define PWMA_Pin GPIO_PIN_11
#define PWMA_GPIO_Port GPIOA
#define MPU_EXTI_Pin GPIO_PIN_5
#define MPU_EXTI_GPIO_Port GPIOB
#define MPU_EXTI_EXTI_IRQn EXTI9_5_IRQn
#define OLED_SCL_Pin GPIO_PIN_8
#define OLED_SCL_GPIO_Port GPIOB
#define OLED_SDA_Pin GPIO_PIN_9
#define OLED_SDA_GPIO_Port GPIOB



//电机正反转驱动端口
#define Ain1 PBout(14)   
#define Ain2 PBout(15)
#define Bin1 PBout(13)
#define Bin2 PBout(12)
#define SPEED_Y 100 //俯仰(前后)最大设定速度
#define SPEED_Z 80//偏航(左右)最大设定速度 





/* USER CODE BEGIN Private defines */



/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
