#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "LED.h"
#include "PWM.h"
#include "Servo.h"
#include "DHT11.h"


int main(void)
{

	OLED_Init();
	Servo_Init();									//包含PWM_Init()
	DHT11_Init();
	uint8_t HUMI,TEMP,Ang1,Ang2 = 0;
	Temp_Servo_SetAngle(Ang1);
	Humi_Servo_SetAngle(Ang2);
	OLED_ShowString(1,1,"Ang1:");
	OLED_ShowString(2,1,"Ang2:");
	OLED_ShowString(3,1,"humi:");
	OLED_ShowString(4,1,"temp:");
	Delay_s(1);


/*	 											！！！		注意		！！！									*/
/*			此工程PWM.c中包含引脚重映射函数的使用，会将SWJ的复用调试功能关闭，谨慎使用！								*/
	
	
	while(1)
	{
		DHT_ReadDATA(&HUMI,&TEMP);
		
		if( Ang1 < 180)
		{
			Ang1  = -((HUMI-100) * 180 / 100);
		
			Humi_Servo_SetAngle(Ang1);
		
		}	
		
		if( Ang2 < 180)
		{

			
			Ang2  = -((TEMP-50) * 180 / 50);
		
			Temp_Servo_SetAngle(Ang2);
		}

		
		OLED_ShowNum(3,7,HUMI,3);
		OLED_ShowNum(4,7,TEMP,3);
		OLED_ShowNum(1,7,Ang1,3);
		OLED_ShowNum(2,7,Ang2,3);
		


	}


}
