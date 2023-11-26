#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "LED.h"
#include "Serial.h"
int main(void)
{
	Key_Init();
	OLED_Init();
	Serial_Init();

	//Serial_SendByte(0x41);
	
	/*uint8_t Array[6] = {'G','N','A','R','A',' '};
	char String[5] = "\rDji\r";*/
	
	uint32_t Number = 133456;
	
	/*Serial_SendArray(Array,5);
	Serial_SendString(String);*/
	Serial_SendNumber(Number,6);
	
	while(1)
	{

	}


}
