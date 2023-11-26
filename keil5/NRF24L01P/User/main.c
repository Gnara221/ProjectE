

#include	"stm32f10x.h"
#include	"system.h"
#include	"delay.h"
#include	"usart.h"
#include	"nrf24l01p.h"	
#include	"spi2.h"




int main(void)
{
	
	u8 key,mode;
	u16 t=0;			 
	u8 tmp_buf[33];		    
	delay_init();	    	 														//延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	USART1_Config();	 															//串口初始化为115200
 	NRF24L01_Init();    														//初始化NRF24L01 
	
	while(NRF24L01_Check())		//等待模块应答
	{
		printf("NRF24L01 Error\r\n");
		delay_ms(500);
	}
	printf("NRF24L01 OK\r\n");
	
	
	mode=0;//接收模式
//	mode=1;//发送模式
	
 	while(1)
	{
		

		if(mode==0)//RX模式
		{
			printf("NRF24L01 RX_Mode\r\n");
			printf("Received DATA:");
			NRF24L01_RX_Mode();
			while(1)
			{
				if(NRF24L01_RxPacket(tmp_buf)==0)//一旦接收到信息,则显示出来.
				{
					tmp_buf[32]=0;//加入字符串结束符
					printf("%s\r\n",tmp_buf);
				}
				else delay_us(100);			    
			};
		}
		else//TX模式
		{
			printf("NRF24L01 TX_Mode\r\n");
			NRF24L01_TX_Mode();
			mode=' ';//从空格键开始
		while(1)
		{
			if(NRF24L01_TxPacket(tmp_buf)==TX_OK)
			{
				printf("Sended DATA:");
				printf("%s\r\n",tmp_buf);
				
				//发送的内容(修改发送的内容)
				key=mode;
				for(t=0;t<32;t++)
				{
					key++;
					if(key>('~'))key=' ';
					tmp_buf[t]=key;
				}
				mode++; 
				if(mode>'~')mode=' ';
				tmp_buf[32]=0;//加入结束符
			}
			else
			{										   	
				printf("Send Failed \r\n");
			};
			delay_ms(1500);
		};
	} 
}
	
}

