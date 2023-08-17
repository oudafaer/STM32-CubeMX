#ifndef __KEY_H
#define __KEY_H

#include "main.h"

#define K0  PEin(4)
#define K1  PEin(3)
#define K2  PEin(2)

#define KEY0_NUM 1 //KEY0 按下
#define KEY1_NUM 2 //KEY1 按下

uint8_t KEY_Scan(void); //按键扫描函数

#endif
