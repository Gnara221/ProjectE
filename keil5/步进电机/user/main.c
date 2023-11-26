#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "StepMotor.h"

int main(void)
{

	OLED_Init();
	Delay_s(1);
	StepMotorInit();
	for(int i = 0; i < 10000; i++){
		Forward_Rotating();
	}
	OLED_ShowString(1,1,"Finished!");

/*	 											！！！		注意		！！！									*/
/*			此工程PWM.c中包含引脚重映射函数的使用，会将SWJ的复用调试功能关闭，谨慎使用！								*/
	
	
	while(1)
	{



	}


}
