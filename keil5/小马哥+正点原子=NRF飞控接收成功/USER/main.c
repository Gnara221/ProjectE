#include "delay.h"
#include "usart.h"
#include "sys.h"
#include "led.h"
#include "motor.h"
#include "spi.h"
#include "si24r1.h"

//ALIENTEK miniSTM32������ʵ��1
//�����ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾
 int main(void)
 {	
	 	u8 tmp_buf[3]; 
	 
	delay_init();	    	 //��ʱ������ʼ��	 
	MOTOR_Init();
	LED_GPIO_Config();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	uart_init(115200);  
	SPI_GPIO_Init();
	SI24R1_Init();
	 
	SI24R1_Check();
	 
	NRF24L01_RX_Mode();	
	 
	while(1)
	{

		if(NRF24L01_RxPacket(tmp_buf)==0)//һ�����յ���Ϣ,����ʾ����.
			{
					printf("NRF24L01_RxPacket is %d\r\n",tmp_buf[1]);		
			  
			}

		
		printf("������������\r\n");	
		Moto_Pwm(500,500,500,500);
		LED3( ON );			  // ��
//		LED2( ON );
//		LED1( ON );
		delay_ms(1300);	 //��ʱ300ms
		LED3( OFF );		  // ��
//		LED2( OFF ); 
//		LED1( OFF );
		delay_ms(1300);	//��ʱ300ms
	}
 }

