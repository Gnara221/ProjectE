#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "MyDMA.h"

uint8_t ArrayA[5] = {0x01,0x02,0x03,0x04,0x05};
uint8_t ArrayB[5] = {0,0,0,0,0};
	
int main(void)
{
	
	OLED_Init();
	OLED_ShowHexNum(1,1,ArrayA[0],2);
	OLED_ShowHexNum(1,4,ArrayA[1],2);
	OLED_ShowHexNum(1,7,ArrayA[2],2);
	OLED_ShowHexNum(1,10,ArrayA[3],2);
	OLED_ShowHexNum(1,13,ArrayA[4],2);
	OLED_ShowHexNum(2,1,ArrayB[0],2);
	OLED_ShowHexNum(2,4,ArrayB[1],2);
	OLED_ShowHexNum(2,7,ArrayB[2],2);
	OLED_ShowHexNum(2,10,ArrayB[3],2);
	OLED_ShowHexNum(2,13,ArrayB[4],2);
	
	MDMA_Init((uint32_t)ArrayA,(uint32_t)ArrayB,5);
	
	OLED_ShowHexNum(3,1,ArrayA[0],2);
	OLED_ShowHexNum(3,4,ArrayA[1],2);
	OLED_ShowHexNum(3,7,ArrayA[2],2);
	OLED_ShowHexNum(3,10,ArrayA[3],2);
	OLED_ShowHexNum(3,13,ArrayA[4],2);
	OLED_ShowHexNum(4,1,ArrayB[0],2);
	OLED_ShowHexNum(4,4,ArrayB[1],2);
	OLED_ShowHexNum(4,7,ArrayB[2],2);
	OLED_ShowHexNum(4,10,ArrayB[3],2);
	OLED_ShowHexNum(4,13,ArrayB[4],2);
	
	
	while(1)
	{

	}


}
