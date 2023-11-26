#include "led.h"
#include "stm32f4xx.h"
int main(void)
{
	InitLED();
	FlashLED();
	return 0;
}