#include "stm32f10x.h"
#include "Delay.h"
int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOA,ENABLE);//打开时钟函数
	GPIO_InitTypeDef GPIO_InitStructure;									  //定义结构体
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;						  //设置对应端口
	
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_Init(GPIOA,&GPIO_InitStructure);									  //初始化GPIOA&GPIOB
	while(1)
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_6);
		GPIO_ResetBits(GPIOA,GPIO_Pin_7);
		GPIO_ResetBits(GPIOA,GPIO_Pin_8);
		GPIO_ResetBits(GPIOA,GPIO_Pin_9);		
		Delay_ms(1000);
		GPIO_SetBits(GPIOA,GPIO_Pin_6);
		GPIO_SetBits(GPIOA,GPIO_Pin_7);
		GPIO_SetBits(GPIOA,GPIO_Pin_8);
		GPIO_SetBits(GPIOA,GPIO_Pin_9);
		Delay_ms(1000);

	/*	GPIO_ResetBits(GPIOB,GPIO_Pin_1);
		GPIO_SetBits(GPIOA,GPIO_Pin_4);
		GPIO_SetBits(GPIOB,GPIO_Pin_0);
		GPIO_ResetBits(GPIOA,GPIO_Pin_8);
		GPIO_SetBits(GPIOA,GPIO_Pin_8);
		Delay_ms(500);

	
		GPIO_SetBits(GPIOA,GPIO_Pin_5);
		GPIO_SetBits(GPIOB,GPIO_Pin_1);
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
		GPIO_ResetBits(GPIOB,GPIO_Pin_0);
		GPIO_ResetBits(GPIOA,GPIO_Pin_9);
		Delay_ms(100);
		GPIO_SetBits(GPIOA,GPIO_Pin_9);
		Delay_ms(500);*/

	}
}
