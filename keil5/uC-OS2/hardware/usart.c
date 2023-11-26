#include "usart.h"

void SendByte(char ch){
	USART1->DR = ch;
	while((USART1->SR&(1<<7))==0);//�ȴ����ͽ���
}

void SendString(char *ch){
	for(int i=0;ch[i]!='\0';i++)SendByte(ch[i]);
}

char ReadByte(void){
	while((USART1->SR&(1<<5))==0);//��ѯ�Ƿ��ܵ�����
	char tmp = USART1->DR & (uint16_t)0x01FF;
	if(tmp!=0)return tmp;
	else return '*';
}

void USARTInit(void)
{
	/*** RCC ***/
	RCC->AHB1ENR |= 0x1 << 0; // Enable GPIOA 6.3.9
	RCC->APB2ENR |= 0x1 << 4; // Enable USART1 6.3.12

	/*** GPIO ***/
	GPIOA->AFR[1] &= (unsigned int) ~(0xF << 4*1); // AFRL PA9 Alternate 0000 8.4.9
	GPIOA->AFR[1] &= (unsigned int) ~(0xF << 4*2); // AFRL PA10 Alternate 0000 8.4.9
	
	GPIOA->AFR[1] |= 0x7 << 4*1; // PA9 Alternate AF7-USART1..2: 0111 8.4.9 / refer: p151
	GPIOA->AFR[1] |= 0x7 << 4*2; // PA10 Alternate AF7-USART1..2: 0111 8.4.9 / refer: p151
	
	GPIOA->MODER &= (unsigned int) ~(0x3 << 2*9); // GPIOA9 reset 00 8.4.1
	GPIOA->MODER &= (unsigned int) ~(0x3 << 2*10);
	
	GPIOA->MODER |= 0x2 << 2*9; // GPIOA9 Altermate function mode 8.4.1
	GPIOA->MODER |= 0x2 << 2*10; // GPIOA10 Altermate function mode 8.4.1
	
	GPIOA->OSPEEDR &= (unsigned int) ~(0x3 << 2*9);
	GPIOA->OSPEEDR &= (unsigned int) ~(0x3 << 2*10);
	
	
	GPIOA->OSPEEDR |= 0x2 << 2*9; // GPIOA9 High speed 10 8.4.3
	GPIOA->OSPEEDR |= 0x2 << 2*10; // GPIOA10 High speed 10
	
	GPIOA->OTYPER &= (unsigned int) ~(0x1 << 9); // GPIOA9 push-pull 00 8.4.2
	GPIOA->OTYPER &= (unsigned int) ~(0x1 << 10);
	
	GPIOA->PUPDR &= (unsigned int) ~(0x3 << 2*9);
	GPIOA->PUPDR &= (unsigned int) ~(0x3 << 2*10);

	GPIOA->PUPDR |= 0x0 << 2*9; // GPIOA 2 No pull-up, pull-down 00 8.4.4
	GPIOA->PUPDR |= 0x0 << 2*10; 

	/*** USART ***/
	// USART1->BRR = 0x369d; // USARTDIV (Tx/Rx=fCK/16*USARTDIV) 19.6.3 / refer: p519
	// USART1->BRR = 0x682; // USARTDIV (Tx/Rx=fCK/16*USARTDIV) 19.6.3 / refer: p519
	USART1->BRR = 0x222E;
	
	USART1->CR3 &=(unsigned int) ~(0x1 << 9); // disable CTS hardware flow 0 19.6.6
	USART1->CR3 &=(unsigned int) ~(0x1 << 8); // disable RTS hardware flow 0 19.6.6
	
	USART1->CR1 |= 0x1 << 3; // transmitter enable 1 19.6.4
	USART1->CR1 |= 0x1 << 2; // receiver enable 1 19.6.4
	
	USART1->CR1 &= (unsigned int) ~(0x1 << 10); // parity control disable 0 19.6.4
		
	USART1->CR2 &= (unsigned int) ~(0x3 << 2*6); // 1 stop bit 0 19.6.5
	
	USART1->CR1 &= (unsigned int) ~(0x1 << 12); // 1-8-n word length 19.6.4
	
	USART1->CR1 |= 1 << 13; // USART enable 19.6.4
}





char* ToString(int iVal){
	char* ReadClock(void);
	char str[1024] = {'\0',};
	char *pos = 0;
	int sign = 0;   //���� ������ 0
	int abs = iVal;

	pos = str + 1023; //�ƶ�ָ��,ָ���ջ�ײ�
	*pos-- = '\0';  //end

	if(iVal < 0)
	{
	  sign = 1;
	  abs = -abs;
	}		 
	int dit = 0;
	while(abs > 0)
	{
	  dit = abs % 10;
	  abs = abs / 10;	 
	  *pos-- = (char)('0' + dit); 
	}
	if(sign) *pos-- = '-';
	char *ret = (char*)malloc(1024 - (pos - str));
	if(iVal == 0)               //0��һ������
		strcpy(ret, "0");
	else                        //iVal��0�Ŀ���
		strcpy(ret, pos+1);
	 
	return(ret);    
 }