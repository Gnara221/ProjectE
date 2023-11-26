#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "Encoder.h"

int16_t num = 0;

int main(void)
{
	OLED_Init();
	Encoder_Init();
	OLED_ShowString(2,3,"Count:");	
	
	while(1)
	{
		num += Encoder_Get();
		OLED_ShowSignedNum(2,9,num,5);	




	
	}

}
