#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "NRF24L01.h"
u8 buf[33] = {'H','E','L','L','O'};

int main(void)
{

	buf[32] = '\0';
	OLED_Init();
	Delay_s(1);
	NRF24L01_Init();
	while(NRF24L01_Check()){
		OLED_ShowString(1,1,"NRF error!");
	}
	SPI_TX_Mode();
	if(NRF24L01_TxPacket(buf) == TX_OK){
		OLED_ShowString(1,1,"Sended Data:");
		OLED_ShowString(2,1,(char*)buf);
		
	}
	


/*	 											！！！		注意		！！！									*/
/*			此工程PWM.c中包含引脚重映射函数的使用，会将SWJ的复用调试功能关闭，谨慎使用！								*/
	
	
	while(1)
	{



	}


}
