#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Encoder.h"
#include "Key.h"
#include "OLED.h"
#include "menu.h"


int main(void)
{
	OLED_Init();
	Encoder_Init();
	Key_Init();
	
	main_menu();
	
	while(1)
	{
		OLED_ShowImage(0, 0, 128, 64, Wallpaper);
		OLED_Update();
		
		if(Key_Enter_Get())
		{
			main_menu();
		}	
	}
}
