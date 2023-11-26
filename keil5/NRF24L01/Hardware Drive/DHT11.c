#include "stm32f10x.h"                  // Device header
#include "Delay.h"

#define OUT 1
#define IN  0
#define DHT_Low  GPIO_ResetBits(GPIOA,GPIO_Pin_11)
#define DHT_High GPIO_SetBits(GPIOA,GPIO_Pin_11)
u8 time = 0;

void DHT11_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
}

void DHT_Mode(u8 mode)
{
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	
	if(mode)
	{
		GPIO_Initstructure.GPIO_Mode = GPIO_Mode_Out_OD;
	}
	else
	{
		GPIO_Initstructure.GPIO_Mode = GPIO_Mode_IPU;
	}
	GPIO_Init(GPIOA,&GPIO_Initstructure);
	
}


void DHT_SendStaSign(void)
{
	DHT_Mode(OUT);
	
	DHT_Low;
	Delay_ms(18);									//低电平18ms
	DHT_High;
	Delay_us(40);									//40us高电平
	
}



void DHT_SendResponse(void)
{
	DHT_Mode(IN);
	
	while((GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11) == 0) && (time < 100))
	{
		time++;
		Delay_us(1);
	}
	time = 0;
	while((GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11) == 1) && (time < 100))
	{
		time++;
		Delay_us(1);
	}
	time = 0;
}


u8 DHT_Read_Byte(void)
{
	u8 data = 0;
	for(u8 i = 0; i < 8;i++)
	{
		DHT_Mode(IN);
		while((GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11) == 0) && (time < 100))
		{
			time++;
			Delay_us(1);
		}
		time = 0;
		data <<= 1;
		Delay_us(40);
		
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11) == 1)
		{
			data |= 0x01;
			
			while((GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11) == 1) && (time < 100))
			{
				time++;
				Delay_us(1);
			}
			time = 0;
		}
	}
	return data;
}

void DHT_ReadDATA(u8 *humi,u8* temp)
{
	u8 DATA[5] = {0,0,0,0,0};
	
	DHT_SendStaSign();
	DHT_SendResponse();
	
	for(u8 i = 0; i < 5; i++)
	{
		DATA[i] = DHT_Read_Byte();
	}
	if(DATA[0] +DATA[1] + DATA[2] + DATA[3] == DATA[4] )
	{
		*humi = DATA[0];
		*temp = DATA[2];
	}
	else 
		for(u8 i = 0; i < 5; i++)
		{
			DATA[i] = 0;
		}
}



