#ifndef __MENU_TEST_H		//方便测试用,定义了函数,不可被重复包含;
#define __MENU_TEST_H

#define		WORD_H 		16				//字高word height

#include "Snake.h" 


//void (*run_func)(void);


/*移植模板*/
void Hello(void)
{
	OLED_Clear();
	OLED_ShowImage(0, 0, 128, 64, Wallpaper);
	OLED_ShowString(0, 48, "  Hello World!  ", OLED_8X16);
	OLED_ReverseArea(0, 48, 128, 16);
	OLED_Update();
	
	
	while(1)
	{
		
		
		
		
		
		if(Key_Enter_Get()) {return;}	
	}
}

void Setting(void)
{
	OLED_Clear();
	OLED_ShowImage(0, 0, 128, 64, Wallpaper);
	OLED_ShowString(0, 48, "Function undeveloped  ", 6);	//功能未开发,敬请期待
	OLED_ShowString(0, 56, "     coming soon!     ", 6);	
	OLED_ReverseArea(0, 48, 128, 16);
	OLED_Update();
	
	
	while(1)
	{
		
		
		
		
		
		if(Key_Enter_Get()) {return;}	
	}
}

void Information(void)
{
	int16_t Angle = 350;
	while(1)
	{
		OLED_Clear();
		
		OLED_ShowImage(88, 8, 32, 32, goutou);
		OLED_Spin(88+16, 8+16, 16, Angle);
		Angle += 2;
		Angle %= 360;
		
		OLED_ShowString(2, 0, "Menu V1.0", OLED_8X16);
		OLED_ShowString(2, 16, " ", OLED_8X16);
		OLED_ShowString(2, 32, "By Adam", OLED_8X16);
		OLED_ShowString(2, 48, "bili_6616647349", OLED_8X16);
		
		OLED_Update();
		if(Key_Enter_Get()) {return;}	
	}
}

/**********************************************************/

void run_option_class(struct option_class* option)		//第一版菜单函数,无动画
{
	
	int8_t Catch_i = 1;	//选中
	int8_t Show_i = 0; 	//显示起始下标
	int8_t Cursor_i = 0; 	//光标位置
	int8_t Max = 0;		//条目数量
	int8_t temp = 0;
	
	while(option[Max].Name[0] != '.') Max++;	//获取条目数量,如果文件名开头为'.'则为结尾
	
	while(1)
	{
		OLED_Clear();
		
		temp = Encoder_Get();		//获取按键事件
		Cursor_i += temp;
		Catch_i += temp;
		
		if(Catch_i < 0) Catch_i = 0;		//限制选中下标
		if(Catch_i > Max) Catch_i = Max;
		
		if(Cursor_i < 0) Cursor_i = 0;		//限制光标位置
		if(Cursor_i > 3) Cursor_i = 3;
		if(Cursor_i > Max) Cursor_i = Max;
		
		Show_i = Catch_i - Cursor_i;	//计算显示起始下标
		
		for(int8_t i = 0; i < 4; i++)
		{	
			if(Show_i + i > Max ) break;
			OLED_ShowString(0, i* WORD_H, option[Show_i + i].Name, OLED_8X16);
		}
		
		OLED_ReverseArea(0, Cursor_i* WORD_H, 116, WORD_H);	//显示光标
		
		
		if(Key_Enter_Get())		//获取按键标志位
		{
			/*如果功能不为空则执行功能,否则返回*/
			if(option[Catch_i].func) option[Catch_i].func();
			else {return;}
		}
		
		OLED_ShowNum(116, 56, Catch_i, 2, OLED_6X8);		//右下角显示选中下标;
		OLED_Update();
	}
}

/**********************************************************/

void run_play1_option_class(struct option_class* option)	//添加动画, 版本1, 硬动画, 跟手;
{
	//int8_t Catch_i_temp = 1;	//选中
	int8_t Cursor_i_temp = 0; 	//光标位置
	int8_t D = 0, Cursor_i_d0 = 0, Cursor_i_d1 = 0; //起点//终点
	
	int8_t Catch_i = 1;	//选中
	int8_t Show_i = 0; 	//显示起始下标
	int8_t Cursor_i = 0; 	//光标位置
	int8_t Max = 0;		//条目数量
	int8_t Incident = 0;
	
	while(option[Max].Name[0] != '.') {Max++;}	//获取条目数量,如果文件名开头为'.'则为结尾
	
	while(1)
	{
		OLED_Clear();
		
		Incident = Encoder_Get();		//获取按键事件//询问
		if(Incident)		//如果有按键事件
		{
			Cursor_i += Incident;
			Catch_i += Incident;
			
			if(Catch_i < 0) {Catch_i = 0;}		//限制选中下标
			if(Catch_i > Max) {Catch_i = Max;}
			
			if(Cursor_i < 0) {Cursor_i = 0;}		//限制光标位置
			if(Cursor_i > 3) {Cursor_i = 3;}
			if(Cursor_i > Max) {Cursor_i = Max;}
			
		}
		Show_i = Catch_i - Cursor_i;	//计算显示起始下标

		for(int8_t i = 0; i < 4; i++)
		{	
			if(Show_i > Max ) {break;}
			OLED_ShowString(0, i* WORD_H, option[Show_i + i].Name, OLED_8X16);
		}
		
		if(Incident)		//如果有按键事件
		{
			D = Incident*4;
			Cursor_i_d0 = Cursor_i_temp * WORD_H;
			Cursor_i_d1 = Cursor_i * WORD_H;
			Cursor_i_temp = Cursor_i;
		}
		
		if(Cursor_i_d0 == Cursor_i_d1) {D = 0;}	//Cursor_i_d0加上变化量,直到Cursor_i_d0 = Cursor_i_d1;
		Cursor_i_d0 += D;
		
		OLED_ReverseArea(0, Cursor_i_d0, 96, 16);	//显示光标
		
		
		if(Key_Enter_Get())		//获取按键
		{
			/*如果功能不为空则执行功能,否则返回*/
			if(option[Catch_i].func) {option[Catch_i].func();}
			else {return;}
		}
		
		//OLED_ShowSignedNum(104, 06, Cursor_i_temp, 3, OLED_6X8);		//右下角显示选中下标;
		//OLED_ShowSignedNum(104, 16, Cursor_i, 3, OLED_6X8);		//右下角显示选中下标;
//		OLED_ShowSignedNum(104, 26, D, 3, OLED_6X8);		//右下角显示选中下标;
//		OLED_ShowSignedNum(104, 36, Cursor_i_d0, 3, OLED_6X8);		//右下角显示选中下标;
//		OLED_ShowSignedNum(104, 46, Cursor_i_d1, 3, OLED_6X8);		//右下角显示选中下标;
//		OLED_ShowSignedNum(104, 56, Catch_i, 3, OLED_6X8);		//右下角显示选中下标;
		OLED_Update();
	}
}

#endif
