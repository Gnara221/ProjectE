#include "stm32f4xx.h"                  // Device header


#define MPU6050_IIC_SCL_1()  	GPIOB->PUPDR |= 0x0003<<16; /* SCL = 1 */
#define MPU6050_IIC_SCL_0()  	GPIOB->PUPDR &=~(0x0003<<16);/* SCL = 0 */

#define MPU6050_IIC_SDA_1()  	GPIOB->PUPDR |= 0x0003<<18;	/* SDA = 1 */
#define MPU6050_IIC_SDA_0()  	GPIOB->PUPDR &=~(0x0003<<18);/* SDA = 0 */


void IIC_GPIOInit(void);
/*
*********************************************************************************************************
*	�� �� ��: IIC_Init
*	����˵��: IIC��ʼ��
*	��    �Σ� reg:�Ĵ�����ַ 
*	�� �� ֵ: ����������
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
*	�� �� ��: IIC_GPIOInit
*	����˵��: GPIO�ڳ�ʼ��������PB8��PB9
*	��    �Σ� NONE
*	�� �� ֵ: void
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