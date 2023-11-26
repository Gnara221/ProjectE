#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "LED.h"
#include "PWM.h"
#include "Motor.h"
#include "Encoder.h"


int main(void)
{
//	LED_Init();
//	Key_Init();
	OLED_Init();
//	PWM_Init();
	Motor_Init();
	Encoder_Init();
	int16_t i = 0;
	Motor_SetSpeed(0);
	OLED_ShowSignedNum(2,5,i,4);
	


	
	while(1)
	{
/*		if(Key_GetNum(GPIOB,GPIO_Pin_1) == 1 && i < 100)
		{
			i += 1;
		
			Motor_SetSpeed(i);
		}	
		

*/		
		i += Encoder_Get();

		Motor_SetSpeed(i);
		
		OLED_ShowSignedNum(2,5,i,4);
		


	}
		
		


}
