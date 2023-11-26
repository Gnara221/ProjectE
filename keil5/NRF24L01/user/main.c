#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"


int main(void)
{

	OLED_Init();
	Delay_s(1);


/*	 											！！！		注意		！！！									*/
/*			此工程PWM.c中包含引脚重映射函数的使用，会将SWJ的复用调试功能关闭，谨慎使用！								*/
	
	
	while(1)
	{



	}


}
