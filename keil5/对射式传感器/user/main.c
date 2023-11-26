#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "CountSensor.h"


int main(void)
{

	OLED_Init();
	CountSensor_Init();


	
	while(1)
{

	OLED_ShowString(2,3,"Count:");
	OLED_ShowNum(2,9,CountSensor_Get(),5);	




	
}

}
