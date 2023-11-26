#include "stm32f10x.h"
#include "Delay.h"
#include "Buzzer.h"
#include "LightSensor.h"
uint8_t KeyNum1,KeyNum2;

int main(void)
{
	BUZZER_Init();
	LightSensor_Init();

	while(1)
	{

//		if(LightSensor_Get() == 1)
			Buzzer_ON(GPIOA,GPIO_Pin_4);
//		else
//			Buzzer_OFF(GPIOB,GPIO_Pin_1);
		
		
	}
}
