#include "stm32f10x.h"                  // Device header



void Serial_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);									//开启时钟，打开USART和GPIO的时钟打开
	
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);		
	GPIO_Init(GPIOB,&GPIO_InitStructure);													//GPIO初始化，把TX配置为复用输出
		
	
	USART_InitTypeDef USART_InitSrtruct;
	USART_InitSrtruct.USART_BaudRate = 9600;												//波特率为9600，函数会自动计算对应的分频系数，写到BRR寄存器
	USART_InitSrtruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;			//硬件流控制配置为none
	USART_InitSrtruct.USART_Mode = USART_Mode_Tx;											//接收模式
	USART_InitSrtruct.USART_Parity = USART_Parity_No;										//校验位配置为no
	USART_InitSrtruct.USART_StopBits = USART_StopBits_1;									//一位停止位
	USART_InitSrtruct.USART_WordLength = USART_WordLength_8b;								//8位字长
	USART_Init(USART1,&USART_InitSrtruct);//配置USART

	USART_Cmd(USART1,ENABLE);
}


void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(USART1,Byte);
	while (USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
}


void Serial_SendArray(uint8_t *Array,uint16_t Length)
{
	uint16_t i;
	for(i = 0 ; i < Length ; i++)
	{
		Serial_SendByte(Array[i]);
	}
}


void Serial_SendString(char *String)
{
	uint16_t i;
	for(i = 0 ; String[i] != '\0' ; i++)
	{
		Serial_SendByte(String[i]);
	}
}

uint32_t Serial_Pow(uint32_t x,uint32_t y)
{
	uint32_t result = 1;
	while(y--)
	{
		result *=  x;
	}
	return result;
}

void Serial_SendNumber(uint32_t Number,uint8_t Length)
{
	uint8_t i;
	uint8_t l = Length - 1;
	for(i = 0 ; i < Length ; i++)
	{
		Serial_SendByte(Number / l);
		l--;
	}
}

