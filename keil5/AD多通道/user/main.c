#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"

#include "AD.h"

int main(void)
{
	AD_Init();
	OLED_Init();
	uint16_t AD0,AD1,AD2,AD3;
	OLED_ShowString(1,1,"AD0:");
	OLED_ShowString(2,1,"AD1:");
	OLED_ShowString(3,1,"AD2:");
	OLED_ShowString(4,1,"AD3:");
	

	
	while(1)
	{

		AD0 = AD_GetValue(ADC_Channel_0);
		AD1 = AD_GetValue(ADC_Channel_1);
		AD2 = AD_GetValue(ADC_Channel_2);
		AD3 = AD_GetValue(ADC_Channel_3);
		OLED_ShowNum(1,5,AD0,4);
		OLED_ShowNum(2,5,AD1,4);
		OLED_ShowNum(3,5,AD2,4);
		OLED_ShowNum(4,5,AD3,4);

/*		i = AD_GetValue() ;
		float Voltage = (float)i / 4096 * 3.3;
		OLED_ShowNum(2,4,Voltage,1);
		OLED_ShowChar(2,5,'.');
		OLED_ShowNum(2,6,(uint16_t)(Voltage * 100) % 100,2);
		OLED_ShowChar(2,8,'V');*/
	}


}
