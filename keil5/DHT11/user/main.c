#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "LED.h"
#include "DHT11.h"

int main(void)
{
	
	DHT11_Init();
	OLED_Init();
	u8 temp,humi = 0;


	
	while(1)
	{
		DHT_ReadDATA(&humi,&temp);
		
		OLED_ShowNum(2,3,humi,4);
		OLED_ShowNum(3,3,temp,4);
		
		
	}


}
