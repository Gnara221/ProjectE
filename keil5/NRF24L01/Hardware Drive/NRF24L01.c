#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "SPI.h"


#define NRF24L01_CSN_ON 	 GPIO_SetBits(GPIO_Pin_3);
#define NRF24L01_CSN_OFF	 GPIO_ResetBits(GPIO_Pin_3);
#define NRF24L01_CE_ON		 GPIO_SetBits(GPIO_Pin_4);
#define NRF24L01_CE_OFF  	 GPIO_ResetBits(GPIO_Pin_4);
u8 NRF24L01_Write_Buf(u8 reg, u8 *pBuf, u8 len);



const u8 TX_ADDRESS[5]={0x34,0x43,0x10,0x10,0x01}; //发送地址
const u8 RX_ADDRESS[5]={0x34,0x43,0x10,0x10,0x01}; //接收地址

void NRF24L01_Init(void){
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);		//初始化GPIOA
	GPIO_SetBits(GPIOA,GPIO_Pin_3 | GPIO_Pin_4);
	
	MySPI1Init();
	
}


void NRF24L01_Check(void){
	u8 buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	u8 i; 	 
	NRF24L01_Write_Buf(WRITE_REG+TX_ADDR,buf,5);//写入5个字节的地址.	
	NRF24L01_Read_Buf(TX_ADDR,buf,5); //读出写入的地址  
	for(i=0;i<5;i++)if(buf[i]!=0XA5)break;	 							   
	if(i!=5)return 1;//检测24L01错误	
	return 0;		 //检测到24L01
}


u8 NRF24L01_Write_Buf(u8 reg, u8 *pBuf, u8 len){
	u8 status;
	NRF24L01_CSN_OFF;
	
	
}



void NRF24L01_TX_Mode(){
	NRF24L01_CE_OFF;
	
}