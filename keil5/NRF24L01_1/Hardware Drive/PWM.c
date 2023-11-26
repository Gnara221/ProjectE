#include "stm32f10x.h"                  // Device header


void PWM_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);							//开启时钟，打开定时器的基准时钟和整个外设的工作时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
/*	引脚重映射
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);							//开启AFIO时钟
	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);						//启用引脚重映射
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);							//使PB3,PB4,PA15默认的复用功能SWJ调试功能失效，转换为普通的GPIO口
*/
	
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;								//复用开漏输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;						
	GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);		//初始化GPIOA
	
	TIM_InternalClockConfig(TIM2);												//选择时基单元时钟源为TIM2内部时钟源


	TIM_TimeBaseInitTypeDef TimeBaseInitStructure;
	TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TimeBaseInitStructure.TIM_Period = 20000 - 1;								//对ARR在频率下计20K个数，即为20ms   范围0~65535
	TimeBaseInitStructure.TIM_Prescaler = 72 - 1;								//对PSC72分频，得到20K计数频率 	范围0~65535
	TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TimeBaseInitStructure);								//配置时基单元，包括预分频器、自动重装器、计数器等

	
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);										//给所有成员赋一个初始值
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC2Init(TIM2,&TIM_OCInitStructure);
	TIM_OC3Init(TIM2,&TIM_OCInitStructure);
	
	TIM_Cmd(TIM2,ENABLE);

}

void PWM_SetCompare2(uint16_t Compare)
{
	TIM_SetCompare2(TIM2,Compare);
}

void PWM_SetCompare3(uint16_t Compare)
{
	TIM_SetCompare3(TIM2,Compare);
}
