#ifndef __SNAKE_H
#define __SNAKE_H

typedef enum{
	air 	= 0,	//空气
	wall 	= 1,	//墙
	head 	= 2,	//蛇头
	body 	= 3,	//蛇身
	food 	= 4		//食物
}tile;

typedef enum{
	up		= 1	,	//	上
	right	= 2	,	//	右
	down	= 3	,	//	下
	left	= 4	,	//	左
}Dir;

typedef struct{
	tile* node[128];
	
	uint8_t Head;	//头下标
	uint8_t Tail;	//尾巴下标
}Snake_Class;

void Snake_Init(void);
tile Snake_GO(uint8_t Line, uint8_t Column);
void Snake_ShowTile8x8(uint8_t Line, uint8_t Column);
Dir CDir(void);			//获取方向

#endif
