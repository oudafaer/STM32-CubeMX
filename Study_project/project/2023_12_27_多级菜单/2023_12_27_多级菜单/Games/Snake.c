#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Delay.h"
#include <stdlib.h>
#include "Encoder.h"
#include "Snake.h"
#include "Snake_Data.h"
#include "Key.h"

extern uint8_t OLED_DisplayBuf[8][128];		//把OLED显存拿过来

tile Map[8][16];	//8x16地图
Snake_Class snake;	//实例化蛇

int8_t dir = 2;		//方向

void OLED_ShowTile8x8(uint8_t Line, uint8_t Column, uint8_t Tile)
{
	for (int8_t i = 0; i < 8; i++)
	{
		OLED_DisplayBuf[Line][Column * 8 + i] = (Tile_BMP8x8[Tile][i]);			//显示区块
	}
}

void Snake_ShowTile8x8(uint8_t Line, uint8_t Column)		//显示方块
{
	Line = Line % 8;
	Column = Column % 16;
	OLED_ShowTile8x8(Line, Column, Map[Line][Column]);	
}

void Map_Clear(void)	//清除地图
{
	int i, j;
	for(i=0; i<8; i++){
		for(j=0; j<16; j++){
			Map[i][j] = air;
		}
	}
}

void Map_Show(void)	//显示地图
{
	int i, j;
	for(i=0; i<8; i++){
		for(j=0; j<16; j++){
			Snake_ShowTile8x8(i, j);
		}
	}
	OLED_Update();
}

void RandFood(void)	//随机放置食物
{
	srand(rand());
	int li = rand()%8;
	int co = rand()%16;
	while(Map[li][co] == wall || Map[li][co] == head || Map[li][co] == body)
	{
		li = rand()%8;
		co = rand()%16;
	}
	Map[li][co] = food;
}

tile Snake_GO(uint8_t Line, uint8_t Column)	//判断条件
{
	Line %= 8;
	Column %= 16;
	
	if(Map[Line][Column] == air)		//如果前方为空气
	{
		*snake.node[snake.Head] = body;		//蛇头地图方块变为蛇身
		snake.Head = (snake.Head + 1) % 128;	//蛇头前进1格
		snake.node[snake.Head] = &Map[Line][Column];		//蛇头投影到地图方块
		Map[Line][Column] = head;		//地图方块变为蛇头
		
		*snake.node[snake.Tail] = air;		//消除蛇尾地图方块
		snake.Tail = (snake.Tail + 1) % 128;	//蛇尾前进1格
		
		Map_Show();		//刷新地图
		
		return air;
	}
	
	else if(Map[Line][Column] == food)		//如果前方为食物
	{
		*snake.node[snake.Head] = body;		//蛇头地图方块变为蛇身
		snake.Head = (snake.Head + 1) % 128;	//蛇头前进1格
		snake.node[snake.Head] = &Map[Line][Column];		//蛇头投影到地图方块
		Map[Line][Column] = head;		//地图方块变为蛇头
		
		RandFood();	//随机放置食物
		
		Map_Show();		//刷新地图
		
		return food;
	}
	
	else if(Map[Line][Column] == body || Map[Line][Column] == head)		//如果前方为蛇身
	{
		return body;
	}
	
	else		// if(Map[Line][Column] == wall)		//如果前方为墙
	{
		return body;
	}
	
	//return air;
}




int8_t  Snake_CoderDir(int8_t n)			//获取方向
{
	
	n += Encoder_Get();
	while(n<1 || n>4)
	{
		if(n > 4){n -= 4;}
		if(n < 1){n += 4;}
	}
	return n;
}

void Snake_Act(uint8_t Line, uint8_t Column)		//行动
{
	
		while(snake.Head - snake.Tail < 3){
			
		Delay_ms(200);
		Column += 1;
		*snake.node[snake.Head] = body;		//蛇头地图方块变为蛇身
		snake.Head = (snake.Head + 1) % 128;	//蛇头前进1格
		snake.node[snake.Head] = &Map[Line][Column];		//蛇头投影到地图方块
		Map[Line][Column] = head;		//地图方块变为蛇头
		
		Map_Show();		//刷新地图
				
	
		}
	while(1){
		if(Key_Enter_Get()) {return;}	
		dir = Snake_CoderDir(dir);
//		OLED_ShowNum(1, 1, dir, 2);
		Delay_ms(100);

		switch (dir){
		case 1:	
			Line -= 1;
			break;
		case 2:
			Column += 1;	
			break;
		case 3:
			Line += 1;	
			break;
		case 4:
			Column -= 1;
			break;
		}
		if(Snake_GO(Line, Column) == body)
		{
			switch (dir){
		case 1:	
			Line += 1;
			break;
		case 2:
			Column -= 1;	
			break;
		case 3:
			Line -= 1;	
			break;
		case 4:
			Column += 1;
			break;
		}
		}
	}
}

void Snake_Init(void)
{
	Map[4][4] = head;
	
	snake.node[0] = &Map[4][4];
	snake.Head = 0;
	snake.Tail = 0;
	
	RandFood();
	
	Map_Show();
	{
		Snake_Act(4, 4);
	}
}
