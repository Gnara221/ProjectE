#include "stm32f10x.h"
#include "Delay.h"
#include "LED.h"
#include "Key.h"
uint8_t KeyNum1,KeyNum2;

int main(void)
{
	LED_Init();
	Key_Init();
	

	while(1)
	{
		KeyNum1 = Key_GetNum(GPIOB,GPIO_Pin_6);
		KeyNum2 = Key_GetNum(GPIOB,GPIO_Pin_0);
		if(KeyNum2 == 0)
			LED_SET_ON(GPIOA,GPIO_Pin_9);
		else
			LED_SET_OFF(GPIOA,GPIO_Pin_9);
		/*if(KeyNum1 == 0)
			LED_SET_ON(GPIOB,GPIO_Pin_0);
		else
			LED_SET_OFF(GPIOB,GPIO_Pin_0);*/
		
	}
}
