#ifndef __HUIDU_H__
#define __HUIDU_H__

#include "main.h"

#define R4  	PAin(4)
#define R3  	PAin(5)
#define R2  	PAin(6)
#define R1  	PAin(7)
#define L1  	PBin(0)
#define L2  	PBin(1)
#define L3  	PCin(0)
#define L4  	PCin(1)


void read_sensor(void);
extern int error;//巡线偏差
extern int jiansu;//小车基础速度的标志变量，jiansu越小时，基础速度越大


#endif

