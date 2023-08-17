#include "key.h"

//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//注意此函数有响应优先级,KEY0>KEY1>KEY2>KEY3!!
uint8_t KEY_Scan(void)
{
	static uint8_t key_up=1; //按键按松开标志
	if(key_up && (K0==0 || K1==0 ))
	{
		HAL_Delay(10);//(10); //去抖动
		key_up=0;
		if(K0==0)  return 1;
		else if(K1==0) return 2;
	}
	else if(K0==1 &&  K1==1 ) key_up=1; 
	return 0; // 无按键按下
	
}
