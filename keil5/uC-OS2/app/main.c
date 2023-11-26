#include "led.h"
#include "stm32f4xx.h"
#include "MyDelay.h"
#include "oled.h"
#include "MyI2C.h"
#include "usart.h"
#include "GY86.h"

int main(void)
{
	InitLED();
	OLED_Init();
	
	uint32_t timefre = 0;
	char time;
	
	My_SystemClockUpdate();
	Delay_ms(100);
	timefre = SystemCoreClock;
	time = (char)timefre;
	while(1)
	{
		OLED_ShowString(1,2,"SystemClock:");
		OLED_ShowNum(2,2,timefre,8);
//		OLED_ShowString(2,2,sprintf(&time));
		FlashLED();
		return 0;	
	
	}
	
}
