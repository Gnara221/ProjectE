#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"
#include "LED.h"

uint16_t Num;

int main(void)
{	
	LED_Init();
	OLED_Init();
	Timer_Init();
	
	
	
	
	while(1)
	{
		OLED_ShowString(1,5,"Time is");
		OLED_ShowString(3,7,"NOW");
	}

}

void TIM2_IRQHandler(void)
{	
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
	{
		Num ++;
		LED_SET_ON(GPIOA,GPIO_Pin_3);
		Delay_ms(100);
		LED_SET_OFF(GPIOA,GPIO_Pin_3);
		OLED_ShowNum(2,4,Num,5);
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}


