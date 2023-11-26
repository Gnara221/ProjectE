#include "stm32f4xx.h"                  // Device header


#define MPU6050_IIC_SCL_1()  	GPIOB->PUPDR |= 0x0003<<16; /* SCL = 1 */
#define MPU6050_IIC_SCL_0()  	GPIOB->PUPDR &=~(0x0003<<16);/* SCL = 0 */

#define MPU6050_IIC_SDA_1()  	GPIOB->PUPDR |= 0x0003<<18;	/* SDA = 1 */
#define MPU6050_IIC_SDA_0()  	GPIOB->PUPDR &=~(0x0003<<18);/* SDA = 0 */


void IIC_GPIOInit(void);
/*
*********************************************************************************************************
*	函 数 名: IIC_Init
*	功能说明: IIC初始化
*	形    参： reg:寄存器地址 
*	返 回 值: 读到的数据
*********************************************************************************************************
*/

void IIC_Init(void){
	//PB8 PB9 I2C1 ENR
	RCC->AHB1ENR |= (uint16_t)0x0001<<1; 
	RCC->APB1ENR |= (uint16_t)0x0001<<21;
	IIC_GPIOInit();
}

/*
*********************************************************************************************************
*	函 数 名: IIC_GPIOInit
*	功能说明: GPIO口初始化，包含PB8和PB9
*	形    参： NONE
*	返 回 值: void
*********************************************************************************************************
*/
void IIC_GPIOInit(void){
	//Set PB8,PB9 to alternate mode
	GPIOB->MODER &= ~(0x0003<<16);
	GPIOB->MODER &= ~(0x0003<<18);
	GPIOB->MODER |= 0x0002<<16;
	GPIOB->MODER |= 0x0002<<18;
	
	//OUT_OD
	GPIOB->OTYPER &= 0x0001<<8;
	GPIOB->OTYPER &= 0x0001<<9;
	
	//SPEED 100MHz
	GPIOB->OSPEEDR |= 0x0003<<16;
	GPIOB->OSPEEDR |= 0x0003<<18;
	
	//PULL UP
	GPIOB->PUPDR &=~(0x0003<<16);
	GPIOB->PUPDR &=~(0x0003<<18);
	GPIOB->PUPDR |= 0x0003<<16;
	GPIOB->PUPDR |= 0x0003<<18;	
	
	//AF choose IIC
	GPIOB->AFR[1] |= 0x0004<<0;
	GPIOB->AFR[1] |= 0x0004<<4;
	
}

void IIC_MasterMode(void){

}

void IIC_Start(void){
	
}