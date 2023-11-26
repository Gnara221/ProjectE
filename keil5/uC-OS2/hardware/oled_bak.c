#include "usart.h"
#include "stm32f4xx.h"
#include "OLED_Font.h"

#define GPIO_Pin_3 ((uint16_t)0x0008) 
#define GPIO_Pin_10 ((uint16_t)0x0400)

typedef enum
{ 
  Bit_RESET = 0,
  Bit_SET
}BitAction;

#define OLED_W_SCL(x)		GPIO_WriteBit(GPIOB,GPIO_Pin_10, x)
#define OLED_W_SDA(x)		GPIO_WriteBit(GPIOB,GPIO_Pin_3, x)
/*
#define OLED_W_SCL(x)		GPIO_WriteBit(GPIOB,GPIO_Pin_10, (BitAction)(x))
#define OLED_W_SDA(x)		GPIO_WriteBit(GPIOB,GPIO_Pin_3, (BitAction)(x))

void GPIO_WriteBit(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin, BitAction BitVal)
{

  if (BitVal != Bit_RESET)
  {
    GPIOB->BSRR = GPIO_Pin;
  }
  else
  {
    GPIOB->BSRR = (uint32_t)GPIO_Pin << 16;
  }
}
*/
void GPIO_WriteBit(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin, int BitVal)
{

  if (BitVal != 0)
  {
    GPIOB->BSRR = GPIO_Pin;
  }
  else
  {
    GPIOB->BSRR = (uint32_t)GPIO_Pin << 16;
  }
}

void OLED_I2C_Init(void)
{
 
	RCC->AHB1ENR |= 0x1 << 1; // 6.3.9
	
	GPIOB->MODER &= (unsigned int) ~(0x3 << 2*3); // 8.4.1
	GPIOB->MODER &= (unsigned int) ~(0x3 << 2*10);
	//GPIOB->MODER |= 0x2 << 2*3;
	//GPIOB->MODER |= 0x2 << 2*10;
	GPIOB->MODER |= 0x1 << 2*3;
	GPIOB->MODER |= 0x1 << 2*10;
	
	//GPIOB->AFR[0] &= (unsigned int) ~(0xF << 4*3); // AFRL PA9 Alternate 0000 8.4.9
	//GPIOB->AFR[1] &= (unsigned int) ~(0xF << 4*2); // AFRL PA10 Alternate 0000 8.4.9
	
	//GPIOB->AFR[0] |= 0x4 << 4*3; // PA9 Alternate AF7-USART1..2: 0111 8.4.9 / refer: p151
	//GPIOB->AFR[1] |= 0x4 << 4*2; // PA10 Alternate AF7-USART1..2: 0111 8.4.9 / refer: p151
	
	GPIOB->OTYPER &= (unsigned int) ~(0x1 << 3); // 8.4.2
	GPIOB->OTYPER &= (unsigned int) ~(0x1 << 10);
	GPIOB->OTYPER |= 0x1 << 3;
	GPIOB->OTYPER |= 0x1 << 10;
	
	GPIOB->OSPEEDR &= (unsigned int) ~(0x3 << 2*3); // 8.4.3
	GPIOB->OSPEEDR &= (unsigned int) ~(0x3 << 2*10);
	GPIOB->OSPEEDR |= 0x2 << 2*3; 
	GPIOB->OSPEEDR |= 0x2 << 2*10;
	
	GPIOB->PUPDR &= (unsigned int) ~(0x3 << 2*3); // 8.4.3
	GPIOB->PUPDR &= (unsigned int) ~(0x3 << 2*10);
	GPIOB->PUPDR |= 0x1 << 2*3; 
	GPIOB->PUPDR |= 0x1 << 2*10;


	//RCC->AHB1ENR = 3;
	//GPIOB->MODER =   1049152;
	//GPIOB->OSPEEDR = 2097280;
	//GPIOB->OTYPER =  1032;
	//GPIOB->PUPDR =   5243200;
	
	
	
	//OLED_W_SCL(0);
	// 8.4.7
	//GPIOB->BSRR = GPIO_Pin_10; // SCL
	//GPIOB->BSRR = GPIO_Pin_3; // SDA
	OLED_W_SCL(1);
	OLED_W_SDA(1);
	
}

void OLED_I2C_Start(void)
{
	//GPIOB->BSRR = GPIO_Pin_3; // SDA 1
	//GPIOB->BSRR = GPIO_Pin_10; // SCL 1
	//GPIOB->BSRR = (uint32_t)GPIO_Pin_3 << 16; // SDA 0
	//GPIOB->BSRR = (uint32_t)GPIO_Pin_10 << 16; // SCL 0
	OLED_W_SDA(1);
	OLED_W_SCL(1);
	OLED_W_SDA(0);
	OLED_W_SCL(0);
}

void OLED_I2C_Stop(void)
{
	//GPIOB->BSRR = (uint32_t)GPIO_Pin_3 << 16; // SDA 0
	//GPIOB->BSRR = GPIO_Pin_10; // SCL 1
	//GPIOB->BSRR = GPIO_Pin_3; // SDA 1
	OLED_W_SDA(0);
	OLED_W_SCL(1);
	OLED_W_SDA(1);
}


void OLED_I2C_SendByte(uint8_t Byte)
{
	uint8_t i;
	for (i = 0; i < 8; i++)
	{
		//GPIO_WriteBit((BitAction)(Byte & (0x80 >> i)));

		//GPIOB->BSRR = GPIO_Pin_10; // SCL 1
		//GPIOB->BSRR = (uint32_t)GPIO_Pin_10 << 16; // SCL 0
		OLED_W_SDA(Byte & (0x80 >> i));
		SendString(ToString(Byte & (0x80 >> i)));
		OLED_W_SCL(1);
		OLED_W_SCL(0);
	}
	//GPIOB->BSRR = GPIO_Pin_10; // SCL 1
	//GPIOB->BSRR = (uint32_t)GPIO_Pin_10 << 16; // SCL 0
	OLED_W_SCL(1);	//�����һ��ʱ�ӣ�������Ӧ���ź�
	OLED_W_SCL(0);
}

void OLED_WriteCommand(uint8_t Command)
{
	OLED_I2C_Start();
	OLED_I2C_SendByte(0x78);		//�ӻ���ַ
	OLED_I2C_SendByte(0x00);		//д����
	OLED_I2C_SendByte(Command); 
	OLED_I2C_Stop();
}

void OLED_WriteData(uint8_t Data)
{
	OLED_I2C_Start();
	OLED_I2C_SendByte(0x78);		//�ӻ���ַ
	OLED_I2C_SendByte(0x40);		//д����
	OLED_I2C_SendByte(Data);
	OLED_I2C_Stop();
}

void OLED_SetCursor(uint8_t Y, uint8_t X)
{
	OLED_WriteCommand(0xB0 | Y);					//����Yλ��
	OLED_WriteCommand(0x10 | ((X & 0xF0) >> 4));	//����Xλ�ø�4λ
	OLED_WriteCommand(0x00 | (X & 0x0F));			//����Xλ�õ�4λ
}

void OLED_Clear(void)
{  
	uint8_t i, j;
	for (j = 0; j < 8; j++)
	{
		OLED_SetCursor(j, 0);
		for(i = 0; i < 128; i++)
		{
			OLED_WriteData(0x00);
		}
	}
}

void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char)
{      	
	uint8_t i;
	OLED_SetCursor((Line - 1) * 2, (Column - 1) * 8);		//���ù��λ�����ϰ벿��
	for (i = 0; i < 8; i++)
	{
		OLED_WriteData(OLED_F8x16[Char - ' '][i]);			//��ʾ�ϰ벿������
	}
	OLED_SetCursor((Line - 1) * 2 + 1, (Column - 1) * 8);	//���ù��λ�����°벿��
	for (i = 0; i < 8; i++)
	{
		OLED_WriteData(OLED_F8x16[Char - ' '][i + 8]);		//��ʾ�°벿������
	}
}

void OLED_ShowString(uint8_t Line, uint8_t Column, char *String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i++)
	{
		OLED_ShowChar(Line, Column + i, String[i]);
	}
}

uint32_t OLED_Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;
	while (Y--)
	{
		Result *= X;
	}
	return Result;
}

void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
	uint8_t i;
	for (i = 0; i < Length; i++)							
	{
		OLED_ShowChar(Line, Column + i, Number / OLED_Pow(10, Length - i - 1) % 10 + '0');
	}
}

void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length)
{
	uint8_t i;
	uint32_t Number1;
	if (Number >= 0)
	{
		OLED_ShowChar(Line, Column, '+');
		Number1 = Number;
	}
	else
	{
		OLED_ShowChar(Line, Column, '-');
		Number1 = -Number;
	}
	for (i = 0; i < Length; i++)							
	{
		OLED_ShowChar(Line, Column + i + 1, Number1 / OLED_Pow(10, Length - i - 1) % 10 + '0');
	}
}

void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
	uint8_t i, SingleNumber;
	for (i = 0; i < Length; i++)							
	{
		SingleNumber = Number / OLED_Pow(16, Length - i - 1) % 16;
		if (SingleNumber < 10)
		{
			OLED_ShowChar(Line, Column + i, SingleNumber + '0');
		}
		else
		{
			OLED_ShowChar(Line, Column + i, SingleNumber - 10 + 'A');
		}
	}
}

void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
	uint8_t i;
	for (i = 0; i < Length; i++)							
	{
		OLED_ShowChar(Line, Column + i, Number / OLED_Pow(2, Length - i - 1) % 2 + '0');
	}
}

void OLED_Init(void)
{
	uint32_t i, j;
	
	for (i = 0; i < 1000; i++)			//�ϵ���ʱ
	{
		for (j = 0; j < 1000; j++);
	}
	
	OLED_I2C_Init();			//�˿ڳ�ʼ��
	
	OLED_WriteCommand(0xAE);	//�ر���ʾ
	
	OLED_WriteCommand(0xD5);	//������ʾʱ�ӷ�Ƶ��/����Ƶ��
	OLED_WriteCommand(0x80);
	
	OLED_WriteCommand(0xA8);	//���ö�·������
	OLED_WriteCommand(0x3F);
	
	OLED_WriteCommand(0xD3);	//������ʾƫ��
	OLED_WriteCommand(0x00);
	
	OLED_WriteCommand(0x40);	//������ʾ��ʼ��
	
	OLED_WriteCommand(0xA1);	//�������ҷ���0xA1���� 0xA0���ҷ���
	
	OLED_WriteCommand(0xC8);	//�������·���0xC8���� 0xC0���·���

	OLED_WriteCommand(0xDA);	//����COM����Ӳ������
	OLED_WriteCommand(0x12);
	
	OLED_WriteCommand(0x81);	//���öԱȶȿ���
	OLED_WriteCommand(0xCF);

	OLED_WriteCommand(0xD9);	//����Ԥ�������
	OLED_WriteCommand(0xF1);

	OLED_WriteCommand(0xDB);	//����VCOMHȡ��ѡ�񼶱�
	OLED_WriteCommand(0x30);

	OLED_WriteCommand(0xA4);	//����������ʾ��/�ر�

	OLED_WriteCommand(0xA6);	//��������/��ת��ʾ

	OLED_WriteCommand(0x8D);	//���ó���
	OLED_WriteCommand(0x14);

	OLED_WriteCommand(0xAF);	//������ʾ
		
	OLED_Clear();				//OLED����

}