#include "stm32f10x.h"                  // Device header

int main(void){

	NVIC_EnableIRQ(USART1_IRQn);
	NVIC_SetPendingIRQ(USART1_IRQn);
	NVIC_SetPriority(USART1_IRQn,1);
	NVIC_GetPendingIRQ(USART1_IRQn);
	NVIC_SetPendingIRQ(USART1_IRQn);
	NVIC_ClearPendingIRQ(USART1_IRQn);
	
}

