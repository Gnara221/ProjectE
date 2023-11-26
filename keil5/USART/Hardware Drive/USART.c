#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#define USART_REC_LEN 200

u8 RX_Flag,RX_Data;

void MyUSART_Init(void){

	RCC->APB2ENR |= 1<<2;		//GPIOA使能
	RCC->APB2ENR |= 1<<14;		//USART1使能
	GPIOA->CRH &= 0xFFFFF00F;	//PA9,10状态清0
	GPIOA->CRH |= 0x000008B0;	//PA9复用推挽输出,50MHz;PA10浮空输入
	RCC->APB2RSTR |= 1<<14;		//USART1复位;
	RCC->APB2RSTR &= ~(1<<14);	//停止复位；
	USART1->CR1|=0X2000;		//USART使能；
//	USART1->CR2 |= 0X00;		//设置停止位数位1，默认为1，不设置也可以
//	USART1->BRR = 0X1D4C;		//设置波特率9600
	USART1->BRR = 0x1A0A;
	
//	NVIC->ISER[1] |= 1<<4;
	NVIC_EnableIRQ(USART1_IRQn);	
//	NVIC->IP[37] |= 1<<4;
	NVIC_SetPriority(USART1_IRQn,1);

}

void SendByte(char ch){
//	USART1->CR1 |= 0X88;		//TE位使能，开始发送数据
	USART1->CR1 |= ~(0x7<<4);
	USART1->CR1 |= ~(0x7);
	Delay_ms(105);
	
			USART1->DR = ch;
//			Delay_us(104);
			while((USART1->SR&0X40)==0);//等待发送结束
			USART1->DR = ' ';
//			Delay_us(104);
			while((USART1->SR&0X40)==0);
		
}

u8 GetReceiveFlag(void){
	USART1->CR1 |= 1<<2;
	if(USART1->SR&(1<<5)){
		RX_Flag = 1;
		USART1->CR1 |= 1<<5;				//接收缓冲器非空中断（CR1_TXEIE）使能
		NVIC_SetPendingIRQ(USART1_IRQn);
	}
	
	return RX_Flag;
}


void USART1_IRQHandler(void){
	u8 Byte = 0;
	if(USART1->SR&(1<<5)){					//接收到数据
		Byte = USART1->DR;					//从DR读取数据，SR_RXNE自动置0
		SendByte(Byte);
//		NVIC->ICPR[1] |= 1<<4;
		NVIC_ClearPendingIRQ(USART1_IRQn);
	}
		
}



void ReceiveChar(void){
	char ch;
	USART1->CR1 |= 1<<2;
	while(1){
		if(USART1->SR &(1<<5)){				//接收到数据
			ch = USART1->DR;				//从DR读取数据，SR_RXNE自动置0
			SendByte(ch);
//			USART1->CR1 &= ~(1<<5);			//清除缓冲器非空中断 （CR1_TXEIE）使能
		}
	
	}
}

void SysteminitClock(void)
{
#define abcde
#ifdef abcde
	RCC->CR |= (uint32_t)0x00000001;
	RCC->CFGR &= (uint32_t)0xF8FF0000;
	RCC->CR &= (uint32_t)0xFEF6FFFF;
	RCC->CR &= (uint32_t)0xFFFBFFFF;
	RCC->CFGR &= (uint32_t)0xFF80FFFF;
	RCC->CIR = 0x009F0000;
	
	RCC->CR |= (uint32_t)0x00000001;
	RCC->CFGR = 0X0000;
	
	RCC->CR |= 1<<16;


	while((RCC->CR & 0x00020000) == 0);
	RCC->APB1ENR |= 1<<28;
	
	FLASH->ACR |= 1<<4;
	FLASH->ACR &= ~(0x03);
	FLASH->ACR |= 0X02;					//	预取缓冲器2个周期
	
	
	RCC->CFGR &= 0<<13;
	RCC->CFGR |= 1U<<10;					//APB1 不分频,APB2 
	RCC->CFGR &= 0<<7;					//AHB不分频
	

	
	RCC->CFGR &= ~(RCC_CFGR_PLLSRC|RCC_CFGR_PLLXTPRE|RCC_CFGR_PLLMULL);
	RCC->CFGR |=1<<16;					//HSE CHOOSE PLL
	RCC->CFGR |= 6U<<18;				//PLLN 8
	RCC->CR |= 1<<24;					//PLL ON
	
	while((RCC->CR & 0x03000000) == 0);
	RCC->CFGR &= ~(0x03);
	RCC->CFGR |= 1<<1;			//SW PLL
	while((RCC->CFGR & 0x0000000C) != (uint32_t)0x08);
#endif

#ifdef asd1
  RCC->CR |= (uint32_t)0x00000001;

  /* Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits */
#ifndef STM32F10X_CL
  RCC->CFGR &= (uint32_t)0xF8FF0000;
#else
  RCC->CFGR &= (uint32_t)0xF0FF0000;
#endif /* STM32F10X_CL */   
  
  /* Reset HSEON, CSSON and PLLON bits */
  RCC->CR &= (uint32_t)0xFEF6FFFF;

  /* Reset HSEBYP bit */
  RCC->CR &= (uint32_t)0xFFFBFFFF;

  /* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits */
  RCC->CFGR &= (uint32_t)0xFF80FFFF;

#ifdef STM32F10X_CL
  /* Reset PLL2ON and PLL3ON bits */
  RCC->CR &= (uint32_t)0xEBFFFFFF;

  /* Disable all interrupts and clear pending bits  */
  RCC->CIR = 0x00FF0000;

  /* Reset CFGR2 register */
  RCC->CFGR2 = 0x00000000;
#elif defined (STM32F10X_LD_VL) || defined (STM32F10X_MD_VL) || (defined STM32F10X_HD_VL)
  /* Disable all interrupts and clear pending bits  */
  RCC->CIR = 0x009F0000;

  /* Reset CFGR2 register */
  RCC->CFGR2 = 0x00000000;      
#else
  /* Disable all interrupts and clear pending bits  */
  RCC->CIR = 0x009F0000;
#endif /* STM32F10X_CL */

	RCC->CR |= (uint32_t)0x00000001;
	RCC->CFGR = 0X0000;
  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
  
  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/    
  /* Enable HSE */    
  RCC->CR |= ((uint32_t)RCC_CR_HSEON);
 
  /* Wait till HSE is ready and if Time out is reached exit */
  do
  {
    HSEStatus = RCC->CR & RCC_CR_HSERDY;
    StartUpCounter++;  
  } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

  if ((RCC->CR & RCC_CR_HSERDY) != RESET)
  {
    HSEStatus = (uint32_t)0x01;
  }
  else
  {
    HSEStatus = (uint32_t)0x00;
  }  

  if (HSEStatus == (uint32_t)0x01)
  {
    /* Enable Prefetch Buffer */
    FLASH->ACR |= FLASH_ACR_PRFTBE;

    /* Flash 2 wait state */
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;    
	
	  
    /* HCLK = SYSCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
      
    /* PCLK2 = HCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
    
    /* PCLK1 = HCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;

   
    /*  PLL configuration: PLLCLK = HSE * 9 = 72 MHz */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE |
                                        RCC_CFGR_PLLMULL));
	RCC->CFGR &= ~(RCC_CFGR_PLLSRC|RCC_CFGR_PLLXTPRE|RCC_CFGR_PLLMULL);
	RCC->CFGR |=1<<16;					//HSE CHOOSE PLL
	RCC->CFGR |= 6U<<18;				//PLLN 8
	RCC->CR |= 1<<24;					//PLL ON
//    RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL9);


    /* Enable PLL */
	
    RCC->CR |= RCC_CR_PLLON;

    /* Wait till PLL is ready */
    while((RCC->CR & RCC_CR_PLLRDY) == 0)
    {
    }
    
    /* Select PLL as system clock source */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
    RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;    

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08)
    {
    }
  }
  else
  { /* If HSE fails to start-up, the application will have wrong clock 
         configuration. User can add here some code to deal with this error */
  }
#endif

}



