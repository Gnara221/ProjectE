#include "stm32f10x.h"                  // Device header
#include "PWM.h"


void Servo_Init(void)
{
	PWM_Init();
	
}

void Temp_Servo_SetAngle(float Angle)
{
	uint16_t Compare = (Angle/180) * 2000 + 500;
	PWM_SetCompare2(Compare);
}

void Humi_Servo_SetAngle(float Angle)
{
	uint16_t Compare = (Angle/180) * 2000 + 500;
	PWM_SetCompare3(Compare);
}