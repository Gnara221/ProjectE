#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"

#include "AD.h"

int main(void)
{
	AD_Init();
	OLED_Init();
	uint16_t i;
	OLED_ShowString(1,1,"ADNum");
	

	
	while(1)
	{

		i = AD_GetValue() ;
		float Voltage = (float)i / 4096 * 3.3;
		OLED_ShowNum(2,4,Voltage,1);
		OLED_ShowChar(2,5,'.');
		OLED_ShowNum(2,6,(uint16_t)(Voltage * 100) % 100,2);
		OLED_ShowChar(2,8,'V');
	}


}
