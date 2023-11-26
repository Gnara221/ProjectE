#include "stm32f10x.h"                  // Device header

uint16_t CountSensor_Count;
	
void CountSensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14); 		//配置AFIO数据选择器的函数   AFIO数据选择器被拨到GPIOB外设上，输出端固定连接EXTI的第14个中断线路
	
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line14;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStructure);										//配置EXTI   将EXTI第14线路配置为中断模式，开启中断，并选择为上升沿触发
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);						//对优先级进行分组，一个芯片分一次组
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);										//配置NVIC
		
}

uint16_t CountSensor_Get(void)
{
	return	CountSensor_Count;
}	

void EXTI15_10_IRQHandler(void)							///中断函数 从启动文件中找到函数名
{
	if(EXTI_GetITStatus(EXTI_Line14) == SET)			//判断中断标志位状态
	{
		CountSensor_Count++;
		EXTI_ClearITPendingBit(EXTI_Line14);			//运行完中断函数后需要清除中断标志位，否则不会退出中断函数
	}	
}
