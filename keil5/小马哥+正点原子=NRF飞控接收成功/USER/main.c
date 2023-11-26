#include "delay.h"
#include "usart.h"
#include "sys.h"
#include "led.h"
#include "motor.h"
#include "spi.h"
#include "si24r1.h"

//ALIENTEK miniSTM32开发板实验1
//跑马灯实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司
 int main(void)
 {	
	 	u8 tmp_buf[3]; 
	 
	delay_init();	    	 //延时函数初始化	 
	MOTOR_Init();
	LED_GPIO_Config();		  	//初始化与LED连接的硬件接口
	uart_init(115200);  
	SPI_GPIO_Init();
	SI24R1_Init();
	 
	SI24R1_Check();
	 
	NRF24L01_RX_Mode();	
	 
	while(1)
	{

		if(NRF24L01_RxPacket(tmp_buf)==0)//一旦接收到信息,则显示出来.
			{
					printf("NRF24L01_RxPacket is %d\r\n",tmp_buf[1]);		
			  
			}

		
		printf("串口运行正常\r\n");	
		Moto_Pwm(500,500,500,500);
		LED3( ON );			  // 亮
//		LED2( ON );
//		LED1( ON );
		delay_ms(1300);	 //延时300ms
		LED3( OFF );		  // 灭
//		LED2( OFF ); 
//		LED1( OFF );
		delay_ms(1300);	//延时300ms
	}
 }

