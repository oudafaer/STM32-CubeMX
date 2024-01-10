#include "menu.h" 
#include "menu_test.h"
#include <string.h>
//

/**********************************************************/

void tools_option(void)
{
	struct option_class option[] = {
		{"<<<"},
		{"TIM", },	//6-1 定时器定时中断
		{"IC", },		//6-6 输入捕获模式测频率
		{"PWM_Out", },			//6-3 PWM驱动LED呼吸灯
		{"PWM_In", },			//6-7 PWMI模式测频率占空比
		{"Encoder", },	//6-8 编码器接口测速
		{"ADC", },				//8-2 DMA+AD多通道
		{"Serial_SR_HEX", },	//9-3 串口收发HEX数据包
		{"Serial_SR_UTF-8", },	//9-4 串口收发文本数据包
		{"SPI_RW_W25Q64", },	//11-2 硬件SPI读写W25Q64
		{"Oscillograph", },		//示波器
		{".."}
	};
	
	run_play_option_class(option);
}

void games_option(void)
{
	struct option_class option[] = {
		{"<<<"},
		{"Snake", Snake_Init},		//贪吃蛇
		{"Snake II", Snake_Init},	//贪吃蛇2
		{"Snake III", Snake_Init},	//贪吃蛇3
		{"Snake IV", Snake_Init},	//贪吃蛇4
		{"Snake V", Snake_Init},	//贪吃蛇5
		{"Snake VI", Snake_Init},	//贪吃蛇6
		{"Snake VII", Snake_Init},	//贪吃蛇7
		{"Snake VIII", Snake_Init},	//贪吃蛇8
		{"Snake IX", Snake_Init},	//贪吃蛇9
		{"Snake X", Snake_Init},	//贪吃蛇10
		{"Conway", },				//康威生命游戏,元胞自动机
		{".."}
	};
	
	run_play_option_class(option);
}

void main_menu(void)
{
	struct option_class option[] = {
		{"<<<"},
		{"Tools", tools_option},
		{"Games", games_option},
		{"Setting", Setting},		//设置
		{"Information", Information},		//信息
		{"Say Hello", Hello},
		{".."}
	};
	
	run_play_option_class(option);
}

/**********************************************************/

void menu_Init(void)
{
	main_menu();
}	


void run_play_option_class(struct option_class* option)	//添加动画
{
	int8_t Catch_i = 1;		//选中下标
	int8_t Show_i = 0; 		//显示起始下标
	int8_t Cursor_i = 0;	//光标下标
	int8_t Max = 0;			//选项数量
	int8_t Incident = 0;	//编码器事件
	
	while(option[Max].Name[0] != '.') {Max++;}	//获取条目数量,如果文件名开头为'.'则为结尾;
	
	int8_t Speed = 8;																		//光标动画速度的倒数;
	static float Cursor_len_d0 = 0, Cursor_len_d1 = 0, Cursor_i_d0 = 0, Cursor_i_d1 = 0; 	//光标位置和长度的起点终点
	
	int8_t Show_d = 0, Show_i_temp = 6;			//显示动画相关;
	
	while(1)
	{
		OLED_Clear();
		
		Incident = Encoder_Get();		//获取按键事件//轮询;
		if(Incident)					//如果有按键事件;
		{
			Cursor_i += Incident;		//更新下标
			Catch_i += Incident;
			
			if(Catch_i < 0) {Catch_i = 0;}			//限制选中下标
			if(Catch_i > Max) {Catch_i = Max;}
			
			if(Cursor_i < 0) {Cursor_i = 0;}		//限制光标位置
			if(Cursor_i > 3) {Cursor_i = 3;}
			if(Cursor_i > Max) {Cursor_i = Max;}
		}
		
		/**********************************************************/
		/*显示相关*/
		
		Show_i = Catch_i - Cursor_i;				//计算显示起始下标
		
		if(0)		//加显示动画
		{
			if(Show_i - Show_i_temp)					//如果下标有偏移
			{
				Show_d = (Show_i - Show_i_temp) * WORD_H;	//
				Show_i_temp = Show_i;
			}
			if(Show_d) {Show_d /= 2;}				//变化量 1.26较平滑1.21
			
			/*如果菜单向下移动,Show_d = -16往0移动期间由于显示字符串函数不支持Y坐标为负数,跳过了打印,所以首行是空的,所以在首行打印Show_i - ((Show_d)/WORD_H)的选项名字,达到覆盖效果;((Show_d)/WORD_H)代替0,兼容Show_d <= -16的情况(菜单开始动画)*/
			if(Show_d < 0) {OLED_ShowString(2, 0, option[Show_i - ((Show_d)/WORD_H)].Name, OLED_8X16);}
			/*如果菜单向上移动,Show_d = 16往0移动期间首行是空的,所以在首行打印Show_i - 1的选项名字,达到覆盖效果;*/
			//if(Show_d > 0) {OLED_ShowString(2, 0, option[Show_i - 1].Name, OLED_8X16);}
		}
		for(int8_t i = 0; i < 6; i++)
		{	
			if(Show_i + i > Max ) {break;}			
			
			OLED_ShowString(2, (i* WORD_H)+Show_d, option[Show_i + i].Name, OLED_8X16);		//显示名字
			//OLED_DrawLine(0, (i* WORD_H)+Show_d+15, 96, (i* WORD_H)+Show_d+15);			//加行线
		}
		
		/**********************************************************/
		/*光标相关*/
		
		if(0)//加光标动画
		{
			Cursor_i_d1 = Cursor_i * WORD_H;					//轮询光标目标位置
			Cursor_len_d1 = strlen(option[Catch_i].Name) * 8 + 4;	//轮询光标目标宽度
			
			/*计算此次循环光标位置*/
			if((Cursor_i_d1 - Cursor_i_d0) > 1) {Cursor_i_d0 += (Cursor_i_d1 - Cursor_i_d0) / Speed + 1;}		//如果当前位置不是目标位置,当前位置向目标位置移动 它们之间距离乘速度的倒数;
			else if((Cursor_i_d1 - Cursor_i_d0) < -1) {Cursor_i_d0 += (Cursor_i_d1 - Cursor_i_d0) / Speed - 1;}
			else {Cursor_i_d0 = Cursor_i_d1;}
			
			/*计算此次循环光标宽度*/
			if((Cursor_len_d1 - Cursor_len_d0) > 1) {Cursor_len_d0 += (Cursor_len_d1 - Cursor_len_d0) / Speed + 1;}
			else if((Cursor_len_d1 - Cursor_len_d0) < -1) {Cursor_len_d0 += (Cursor_len_d1 - Cursor_len_d0) / Speed - 1;}
			else {Cursor_len_d0 = Cursor_len_d1;}
		}
		else {Cursor_i_d0 = Cursor_i * WORD_H; Cursor_len_d0 = 128;}
		
		//显示光标
		//OLED_DrawRectangle(0, Cursor_i_d0, Cursor_len_d0, 16, 0);			//矩形光标
		OLED_ReverseArea(0, Cursor_i_d0, Cursor_len_d0, WORD_H);			//反相光标
		//OLED_ShowString(Cursor_len_d0, Cursor_i_d0+6, "<-", OLED_6X8);	//尾巴光标
		
		/**********************************************************/
		
		if(Key_Enter_Get())		//获取按键
		{
			/*如果功能不为空则执行功能,否则返回*/
			if(option[Catch_i].func) {option[Catch_i].func();}
			else {return;}
		}
		
		OLED_ShowNum(116, 56, Catch_i, 2, OLED_6X8);		//右下角显示选中下标;
		OLED_Update();
	}
}

/**********************************************************/


