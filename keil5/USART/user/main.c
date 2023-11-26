#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "USART.h"


int main(void)
{

	OLED_Init();
	SysteminitClock();
	SystemCoreClockUpdate();
	uint32_t a = SystemCoreClock;
	OLED_ShowHexNum(4,1,a,16);
	MyUSART_Init();
	OLED_ShowString(1,2,"Preparing...");
	Delay_s(1);
	OLED_ShowString(2,2,"Sending...");
	Delay_s(1);
//	SendBit('A');
	OLED_ShowString(2,2,"Receiving...");
//	ReceiveChar();
//	OLED_ShowString(3,2,"Over!");
	u8 data;

	
	while(1)
	{
		while(GetReceiveFlag() == 1){
			OLED_ShowString(3,2,"Receive!");
		}


	}
		
		
/*		for (int i = 1;i <= 4; i++)
	{
		for (int j = 1;j <= 16;j++)
		{
			OLED_ShowChar(i,j,'.');
		}
	}
		Delay_ms(800);
		for (int i = 1;i <= 4; i++)
	{
		for (int j = 1;j <= 16;j++)
		{
			OLED_ShowChar(i,j,' ');
		}
	}
		Delay_ms(800);
*/		
		




}
