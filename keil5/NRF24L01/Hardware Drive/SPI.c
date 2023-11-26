#include "stm32f10x.h"                  // Device header

void MySPI1Init(void){
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1,ENABLE);
	
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 |GPIO_Pin_7 ;
	GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);		//³õÊ¼»¯GPIOA
	GPIO_SetBits(GPIOA, GPIO_Pin_5 | GPIO_Pin_6 |GPIO_Pin_7);
	
	//Master Mode
	//Software Manage Mode
	//8bit 
	SPI_InitTypeDef SPI_InitStructure;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;				
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;					
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;			
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	
	SPI_Init(SPI1,&SPI_InitStructure);
	SPI_Cmd(SPI1,ENABLE);

	
}


u8 SPI_RW(u8 TxDATA){
	u8 retry = 0;
	while((SPI1->SR&0x02) == 0){
		retry++;
		if(retry>=200)
			return 0;
	}
	SPI1->DR = TxDATA;
	while((SPI1->SR&0x01) == 0){
		retry++;
		if(retry>=200)
			return 0;
	}
	return TxDATA;
} 
	