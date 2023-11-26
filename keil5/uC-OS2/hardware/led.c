#include "led.h"
void InitLED(void){
	RCC->AHB1ENR |= 0x1 << 0; /* GPIOA 时钟外设使能 6.3.12 */
	RCC->AHB1ENR |= 0x1 << 1; /* GPIOB 时钟外设使能 6.3.12 */
	
	GPIOA->MODER   &= ~(0x3 << 2*5);  /* GPIO 端口模式寄存器 7.4.1 */
	GPIOA->MODER   |=   0x1 << 2*5;
	
	GPIOA->OTYPER  &=   0x0 << 5;  /* GPIO 端口输出类型寄存器 7.4.2 */
	
	GPIOA->OSPEEDR &= ~(0x3 << 2*5); /* GPIO 端口输出速度寄存器 7.4.3 */
	GPIOA->OSPEEDR |=   0x2 << 2*5;
	
	GPIOA->PUPDR   &= ~(0x3 << 2*5); /* GPIO 端口上拉/下拉寄存器 7.4.4 */
	
	
#ifdef TEST
	GPIOA->MODER   &= ~(0x3 << 2*0);  /* GPIO 端口模式寄存器 7.4.1 */
	GPIOA->MODER   |=   0x1 << 2*0;
	GPIOA->OTYPER  &=   0x0 << 	 0;  /* GPIO 端口输出类型寄存器 7.4.2 */
	GPIOA->OSPEEDR &= ~(0x3 << 2*0); /* GPIO 端口输出速度寄存器 7.4.3 */
	GPIOA->OSPEEDR |=   0x2 << 2*0;
	GPIOA->PUPDR   &= ~(0x3 << 2*0); /* GPIO 端口上拉/下拉寄存器 7.4.4 */
	
	GPIOA->MODER   &= ~(0x3 << 2*6);  /* GPIO 端口模式寄存器 7.4.1 */
	GPIOA->MODER   |=   0x1 << 2*6;
	GPIOA->OTYPER  &=   0x0 << 	 6;  /* GPIO 端口输出类型寄存器 7.4.2 */
	GPIOA->OSPEEDR &= ~(0x3 << 2*6); /* GPIO 端口输出速度寄存器 7.4.3 */
	GPIOA->OSPEEDR |=   0x2 << 2*6;
	GPIOA->PUPDR   &= ~(0x3 << 2*6); /* GPIO 端口上拉/下拉寄存器 7.4.4 */
	
	GPIOA->MODER   &= ~(0x3 << 2*7);  /* GPIO 端口模式寄存器 7.4.1 */
	GPIOA->MODER   |=   0x1 << 2*7;
	GPIOA->OTYPER  &=   0x0 << 	 7;  /* GPIO 端口输出类型寄存器 7.4.2 */
	GPIOA->OSPEEDR &= ~(0x3 << 2*7); /* GPIO 端口输出速度寄存器 7.4.3 */
	GPIOA->OSPEEDR |=   0x2 << 2*7;
	GPIOA->PUPDR   &= ~(0x3 << 2*7); /* GPIO 端口上拉/下拉寄存器 7.4.4 */
	
	GPIOA->MODER   &= ~(0x3 << 2*8);  /* GPIO 端口模式寄存器 7.4.1 */
	GPIOA->MODER   |=   0x1 << 2*8;
	GPIOA->OTYPER  &=   0x0 << 	 8;  /* GPIO 端口输出类型寄存器 7.4.2 */
	GPIOA->OSPEEDR &= ~(0x3 << 2*8); /* GPIO 端口输出速度寄存器 7.4.3 */
	GPIOA->OSPEEDR |=   0x2 << 2*8;
	GPIOA->PUPDR   &= ~(0x3 << 2*8); /* GPIO 端口上拉/下拉寄存器 7.4.4 */
	
	GPIOA->MODER   &= ~(0x3 << 2*9);  /* GPIO 端口模式寄存器 7.4.1 */
	GPIOA->MODER   |=   0x1 << 2*9;
	GPIOA->OTYPER  &=   0x0 << 	 9;  /* GPIO 端口输出类型寄存器 7.4.2 */
	GPIOA->OSPEEDR &= ~(0x3 << 2*9); /* GPIO 端口输出速度寄存器 7.4.3 */
	GPIOA->OSPEEDR |=   0x2 << 2*9;
	GPIOA->PUPDR   &= ~(0x3 << 2*9); /* GPIO 端口上拉/下拉寄存器 7.4.4 */
	
	GPIOA->MODER   &= ~(0x3 << 2*10);  /* GPIO 端口模式寄存器 7.4.1 */
	GPIOA->MODER   |=   0x1 << 2*10;
	GPIOA->OTYPER  &=   0x0 << 	 10;  /* GPIO 端口输出类型寄存器 7.4.2 */
	GPIOA->OSPEEDR &= ~(0x3 << 2*10); /* GPIO 端口输出速度寄存器 7.4.3 */
	GPIOA->OSPEEDR |=   0x2 << 2*10;
	GPIOA->PUPDR   &= ~(0x3 << 2*10); /* GPIO 端口上拉/下拉寄存器 7.4.4 */
	
	GPIOA->MODER   &= ~(0x3 << 2*11);  /* GPIO 端口模式寄存器 7.4.1 */
	GPIOA->MODER   |=   0x1 << 2*11;
	GPIOA->OTYPER  &=   0x0 << 	 11;  /* GPIO 端口输出类型寄存器 7.4.2 */
	GPIOA->OSPEEDR &= ~(0x3 << 2*11); /* GPIO 端口输出速度寄存器 7.4.3 */
	GPIOA->OSPEEDR |=   0x2 << 2*11;
	GPIOA->PUPDR   &= ~(0x3 << 2*11); /* GPIO 端口上拉/下拉寄存器 7.4.4 */
	
	
	GPIOB->MODER   &= ~(0x3 << 2*6);  /* GPIO 端口模式寄存器 7.4.1 */
	GPIOB->MODER   |=   0x1 << 2*6;
	GPIOB->OTYPER  &=   0x0 << 	 6;  /* GPIO 端口输出类型寄存器 7.4.2 */
	GPIOB->OSPEEDR &= ~(0x3 << 2*6); /* GPIO 端口输出速度寄存器 7.4.3 */
	GPIOB->OSPEEDR |=   0x2 << 2*6;
	GPIOB->PUPDR   &= ~(0x3 << 2*6); /* GPIO 端口上拉/下拉寄存器 7.4.4 */
	
	GPIOB->MODER   &= ~(0x3 << 2*7);  /* GPIO 端口模式寄存器 7.4.1 */
	GPIOB->MODER   |=   0x1 << 2*7;
	GPIOB->OTYPER  &=   0x0 << 	 7;  /* GPIO 端口输出类型寄存器 7.4.2 */
	GPIOB->OSPEEDR &= ~(0x3 << 2*7); /* GPIO 端口输出速度寄存器 7.4.3 */
	GPIOB->OSPEEDR |=   0x2 << 2*7;
	GPIOB->PUPDR   &= ~(0x3 << 2*7); /* GPIO 端口上拉/下拉寄存器 7.4.4 */
	
	GPIOB->MODER   &= ~(0x3 << 2*8);  /* GPIO 端口模式寄存器 7.4.1 */
	GPIOB->MODER   |=   0x1 << 2*8;
	GPIOB->OTYPER  &=   0x0 << 	 8;  /* GPIO 端口输出类型寄存器 7.4.2 */
	GPIOB->OSPEEDR &= ~(0x3 << 2*8); /* GPIO 端口输出速度寄存器 7.4.3 */
	GPIOB->OSPEEDR |=   0x2 << 2*8;
	GPIOB->PUPDR   &= ~(0x3 << 2*8); /* GPIO 端口上拉/下拉寄存器 7.4.4 */
	
	GPIOB->MODER   &= ~(0x3 << 2*9);  /* GPIO 端口模式寄存器 7.4.1 */
	GPIOB->MODER   |=   0x1 << 2*9;
	GPIOB->OTYPER  &=   0x0 << 	 9;  /* GPIO 端口输出类型寄存器 7.4.2 */
	GPIOB->OSPEEDR &= ~(0x3 << 2*9); /* GPIO 端口输出速度寄存器 7.4.3 */
	GPIOB->OSPEEDR |=   0x2 << 2*9;
	GPIOB->PUPDR   &= ~(0x3 << 2*9); /* GPIO 端口上拉/下拉寄存器 7.4.4 */
#endif
}
void LED_On(void){

	GPIOA->ODR |= 0x1 << 5 ;
#ifdef TEST
	GPIOA->ODR |= 0x1 << 0 ;
	GPIOA->ODR |= 0x1 << 6 ;
	GPIOA->ODR |= 0x1 << 7 ;
	GPIOA->ODR |= 0x1 << 8 ;
	GPIOA->ODR |= 0x1 << 9 ;
	GPIOA->ODR |= 0x1 << 10;
	GPIOA->ODR |= 0x1 << 11;
	
	GPIOB->ODR |= 0x1 << 6;
	GPIOB->ODR |= 0x1 << 7;
	GPIOB->ODR |= 0x1 << 8;
	GPIOB->ODR |= 0x1 << 9;
#endif
}
void LED_Off(void){
	
	GPIOA->ODR &= ~(0x1 << 5 );
#ifdef TEST
	GPIOA->ODR &= ~(0x1 << 0 );
	GPIOA->ODR &= ~(0x1 << 6 );
	GPIOA->ODR &= ~(0x1 << 7 );
	GPIOA->ODR &= ~(0x1 << 8 );
	GPIOA->ODR &= ~(0x1 << 9 );
	GPIOA->ODR &= ~(0x1 << 10);
	GPIOA->ODR &= ~(0x1 << 11);
	
	GPIOB->ODR &= ~(0x1 << 6 );
	GPIOB->ODR &= ~(0x1 << 7 );
	GPIOB->ODR &= ~(0x1 << 8 );
	GPIOB->ODR &= ~(0x1 << 9 );
	
#endif
}
void FlashLED(void)
{

		LED_On();
        int temp_cnt=1000000;
        while(temp_cnt--);
        LED_Off();
        temp_cnt=1000000;
        while(temp_cnt--);
}
