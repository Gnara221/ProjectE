#include "stm32f10x.h"                  // Device header

void LightSensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef  GPIO_KEY_InitStructure;
	GPIO_KEY_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_KEY_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_KEY_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_KEY_InitStructure);		//初始化GPIOA
	
	
	GPIO_InitTypeDef  GPIO_KEY_InitStructureB;
	GPIO_KEY_InitStructureB.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_KEY_InitStructureB.GPIO_Pin = GPIO_Pin_All;
	GPIO_KEY_InitStructureB.GPIO_Speed =  GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_KEY_InitStructureB);		//初始化GPIOB
	
}

uint8_t LightSensor_Get(void)
{
	return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13);
	
}



