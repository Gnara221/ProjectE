#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "LED.h"

int main(void)
{
	LED_Init();
	Key_Init();
	OLED_Init();
	int i = 0;
	


	
	while(1)
	{
		for (int i = 1;i <= 4; i++)
	{
		for (int j = 1;j <= 16;j++)
		{
			OLED_ShowChar(i,j,'.');
		}
	}
		Delay_ms(800);
		for (int i = 1;i <= 4; i++)
	{
		for (int j = 1;j <= 16;j++)
		{
			OLED_ShowChar(i,j,' ');
		}
	}
		Delay_ms(800);
		
		
	}


}
