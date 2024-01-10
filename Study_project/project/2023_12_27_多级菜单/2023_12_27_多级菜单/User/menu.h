#ifndef __MENU_H
#define __MENU_H

 

#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Encoder.h"
#include "Key.h"

//选项类
struct option_class{
	char Name[16];			//显示字符串
	void (*func)(void);		//函数指针
};

struct menu_class{
	uint8_t N[16];						//选项数量
	struct option_class* ption_list;	//选项列表
};

void run_play_option_class(struct option_class* option);	//添加动画

void run_option_class(struct option_class* menu);
void menu_Init(void);
	
/**********************************************************/

void main_menu(void);
void tools_option(void);
void games_option(void);

/**********************************************************/

#endif
