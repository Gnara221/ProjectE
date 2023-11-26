#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef  GPIO_KEY_InitStructure;
	GPIO_KEY_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_KEY_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_KEY_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_KEY_InitStructure);		//初始化GPIOA
	GPIO_Init(GPIOB,&GPIO_KEY_InitStructure);
	
	

}
uint8_t	Key_GetNum(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
	{
		uint8_t KeyNum = 0;
		if (GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == 1)
		{
			Delay_ms(20);
			KeyNum = 1;
			Delay_ms(20);
		}
		return KeyNum;
	}				//按下按键亮灯，松手即灭
	
void LED_Turn(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	if (GPIO_ReadOutputDataBit(GPIOx,GPIO_Pin) == 0)
		GPIO_SetBits(GPIOx,GPIO_Pin);
	else
		GPIO_ResetBits(GPIOx,GPIO_Pin);
}

	