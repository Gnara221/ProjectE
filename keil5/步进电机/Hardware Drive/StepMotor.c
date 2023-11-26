#include "stm32f10x.h"                  // Device header
#include "Delay.h"

#define LA_ON 	GPIO_SetBits(GPIOA,GPIO_Pin_1)
#define LB_ON 	GPIO_SetBits(GPIOA,GPIO_Pin_2)
#define LC_ON 	GPIO_SetBits(GPIOA,GPIO_Pin_3)
#define LD_ON 	GPIO_SetBits(GPIOA,GPIO_Pin_4)
#define LA_OFF 	GPIO_ResetBits(GPIOA,GPIO_Pin_1)
#define LB_OFF 	GPIO_ResetBits(GPIOA,GPIO_Pin_2)
#define LC_OFF 	GPIO_ResetBits(GPIOA,GPIO_Pin_3)
#define LD_OFF 	GPIO_ResetBits(GPIOA,GPIO_Pin_4)
#define LA 0x01
#define LB 0x02
#define LC 0x04
#define LD 0x08
static uint8_t Steps[8] = {0x01, 0x03, 0x02, 0x6, 0x04, 0x0c, 0x08, 0x09};



void StepMotorInit(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIOA_Initstructure;
	GPIOA_Initstructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIOA_Initstructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIOA_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIOA_Initstructure);
	
	LA_OFF;
    LB_OFF;
    LC_OFF;
    LD_OFF;
	
}

void Forward_Rotating(void){
	for(int i = 0; i < 8; i++){
		if(LA & Steps[i] ){
			LA_ON;
		}else
			LA_OFF;
		
		if(LB & Steps[i] ){
			LB_ON;
		}else
			LB_OFF;
		
		if(LC & Steps[i] ){
			LC_ON;
		}else
			LC_OFF;
		
		if(LD & Steps[i] ){
			LD_ON;
		}else
			LD_OFF;
		Delay_ms(2);
	}
	LA_OFF;
    LB_OFF;
    LC_OFF;
    LD_OFF;

}