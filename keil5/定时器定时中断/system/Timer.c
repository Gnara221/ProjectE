#include "stm32f10x.h"                  										// Device header

void Timer_Init(void)
{
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);							//开启时钟，打开定时器的基准时钟和整个外设的工作时钟

	
	TIM_InternalClockConfig(TIM2);												//选择时基单元时钟源，这里选择内部时钟源


	TIM_TimeBaseInitTypeDef TimeBaseInitStructure;
	TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TimeBaseInitStructure.TIM_Period = 10000 - 1;								//对ARR在10K频率下计10K个数，即为1s   范围0~65535
	TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;								//对PSC7200分频，得到10K计数频率 	范围0~65535
	TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TimeBaseInitStructure);								//配置时基单元，包括预分频器、自动重装器、计数器等

	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);								//配置输出中断控制，允许更新中断输出到NVIC,优先级为组二

	NVIC_InitTypeDef NVIC_InitStructure;											
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;							//配置NVIC,在NVIC中打开定时器2中断的通道，并分配优先级
	NVIC_Init(&NVIC_InitStructure);
	
	
	TIM_Cmd(TIM2,ENABLE);														//启动定时器
}

/*void TIM2_IRQHanler(void)
{
	
	
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
	{
		num++;
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
	
	
}
*/

	
	