#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "LED.h"
#include "PWM.h"

int main(void)
{
//	LED_Init();
//	Key_Init();
	OLED_Init();
	PWM_Init();
	int i = 0;
	


	
	while(1)
	{
		PWM_SetCompare1(100);
/*		for(i = 0;i < 100;i++)
		{
			PWM_SetCompare1(i);
			Delay_ms(10);
		}
		for(i = 100;i > 0;i--)
		{
			PWM_SetCompare1(i);
			Delay_ms(10);
		}*/

	}


}
