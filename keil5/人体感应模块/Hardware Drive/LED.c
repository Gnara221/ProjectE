#include "stm32f10x.h" 
// Device header
void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);		//初始化GPIOA
	
	GPIO_SetBits(GPIOA,GPIO_Pin_All);
	
	GPIO_InitTypeDef  GPIO_InitStructureB;
	GPIO_InitStructureB.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructureB.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructureB.GPIO_Speed =  GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructureB);		//初始化GPIOB
	
	GPIO_SetBits(GPIOB,GPIO_Pin_All);
}

void LED_SET_ON(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	GPIO_ResetBits(GPIOx,GPIO_Pin);
}

void LED_SET_OFF(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
		GPIO_SetBits(GPIOx,GPIO_Pin);
}


