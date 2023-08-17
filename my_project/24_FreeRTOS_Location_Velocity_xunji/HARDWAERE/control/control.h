#ifndef __control_H__
#define __control_H__

#include "main.h"

extern int location_increment_target_val;
extern int location_increment_target_val2;
extern uint8_t Stop_flag;

/* 提供给其他C文件调用的函数 --------------------------------------------------------------------------------------------*/
void control_Init(void);


#endif

