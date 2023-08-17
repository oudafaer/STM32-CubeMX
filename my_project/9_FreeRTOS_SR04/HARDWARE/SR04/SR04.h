#ifndef __SR04_H
#define __SR04_H

#include "main.h"


#define TRIG_H  HAL_GPIO_WritePin(Trig_GPIO_Port,Trig_Pin,GPIO_PIN_SET)
#define TRIG_L  HAL_GPIO_WritePin(Trig_GPIO_Port,Trig_Pin,GPIO_PIN_RESET)
 
void SR04_GetData(void);
 
#endif


