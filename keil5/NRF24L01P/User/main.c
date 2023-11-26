

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
	delay_init();	    	 														//��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	USART1_Config();	 															//���ڳ�ʼ��Ϊ115200
 	NRF24L01_Init();    														//��ʼ��NRF24L01 
	
	while(NRF24L01_Check())		//�ȴ�ģ��Ӧ��
	{
		printf("NRF24L01 Error\r\n");
		delay_ms(500);
	}
	printf("NRF24L01 OK\r\n");
	
	
	mode=0;//����ģʽ
//	mode=1;//����ģʽ
	
 	while(1)
	{
		

		if(mode==0)//RXģʽ
		{
			printf("NRF24L01 RX_Mode\r\n");
			printf("Received DATA:");
			NRF24L01_RX_Mode();
			while(1)
			{
				if(NRF24L01_RxPacket(tmp_buf)==0)//һ�����յ���Ϣ,����ʾ����.
				{
					tmp_buf[32]=0;//�����ַ���������
					printf("%s\r\n",tmp_buf);
				}
				else delay_us(100);			    
			};
		}
		else//TXģʽ
		{
			printf("NRF24L01 TX_Mode\r\n");
			NRF24L01_TX_Mode();
			mode=' ';//�ӿո����ʼ
		while(1)
		{
			if(NRF24L01_TxPacket(tmp_buf)==TX_OK)
			{
				printf("Sended DATA:");
				printf("%s\r\n",tmp_buf);
				
				//���͵�����(�޸ķ��͵�����)
				key=mode;
				for(t=0;t<32;t++)
				{
					key++;
					if(key>('~'))key=' ';
					tmp_buf[t]=key;
				}
				mode++; 
				if(mode>'~')mode=' ';
				tmp_buf[32]=0;//���������
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

