#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "SPI.h"
#include "NRF24L01.h"



#define NRF24L01_CSN_ON 	 GPIO_SetBits(GPIOA,GPIO_Pin_3);
#define NRF24L01_CSN_OFF	 GPIO_ResetBits(GPIOA,GPIO_Pin_3);
#define NRF24L01_CE_ON		 GPIO_SetBits(GPIOA,GPIO_Pin_4);
#define NRF24L01_CE_OFF  	 GPIO_ResetBits(GPIOA,GPIO_Pin_4);

u8 NRF24L01_Write_Buf(u8 reg, u8 *pBuf, u8 len);
u8 NRF24L01_Read_Buf(u8 reg,u8 *pBuf,u8 len);


const u8 TX_ADDRESS[5]={0x34,0x43,0x10,0x10,0x01}; //���͵�ַ
const u8 RX_ADDRESS[5]={0x34,0x43,0x10,0x10,0x01}; //���յ�ַ

void NRF24L01_Init(void){
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);		//��ʼ��GPIOA
	GPIO_SetBits(GPIOA,GPIO_Pin_3 | GPIO_Pin_4);
	
	MySPI1Init();
	
}

//���24L01�Ƿ����
//����ֵ:0���ɹ�;1��ʧ��
u8 NRF24L01_Check(void){
	u8 buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	u8 i; 	 
	NRF24L01_Write_Buf(SPI_WRITE_REG+TX_ADDR,buf,5);	//д��5���ֽڵĵ�ַ.	
	NRF24L01_Read_Buf(TX_ADDR,buf,5); 			//����д��ĵ�ַ  
	for(i=0;i<5;i++)
	if(buf[i]!=0XA5)
		break;	 							   
	if(i!=5)
		return 1;							//���24L01����	
	return 0;		 						//��⵽24L01
}


//��ȡSPI�Ĵ���ֵ
//reg:Ҫ���ļĴ���


//��ָ��λ�ö���ָ�����ȵ�����
//reg:�Ĵ���(λ��)
//*pBuf:����ָ��
//len:���ݳ���
//����ֵ,�˴ζ�����״̬�Ĵ���ֵ 
u8 NRF24L01_Read_Buf(u8 reg,u8 *pBuf,u8 len){
	u8 status;	       
  	NRF24L01_CSN_OFF;           	 //ʹ��SPI����
  	status = SPI_RW(reg);		 	 //���ͼĴ���ֵ(λ��),����ȡ״ֵ̬   	   
 	for(u8 i=0 ; i<len ; i++)
	pBuf[i]=SPI_RW(0XFF);			 //��������
  	NRF24L01_CSN_ON;      			 //�ر�SPI����
  	return status;       			 //���ض�����״ֵ̬
}

//��ָ��λ��дָ�����ȵ�����
//reg:�Ĵ���(λ��)
//*pBuf:����ָ��
//len:���ݳ���
//����ֵ,�˴ζ�����״̬�Ĵ���ֵ
u8 NRF24L01_Write_Buf(u8 reg, u8 *pBuf, u8 len){
	u8 status;	       
  	NRF24L01_CSN_OFF;           	//ʹ��SPI����
  	status = SPI_RW(reg);		 	//���ͼĴ���ֵ(λ��),����ȡ״ֵ̬   	   
 	for(u8 i=0 ; i<len ; i++)
	pBuf[i]=SPI_RW(*pBuf++);		//��������
  	NRF24L01_CSN_ON;       			//�ر�SPI����
  	return status;        			//���ض�����״ֵ̬
	
	
}



//д�Ĵ���
//reg:Ҫ���ļĴ���
u8 NRF24L01_Write_Reg(u8 reg,u8 value){
	u8 status;	
   	NRF24L01_CSN_OFF;                 //ʹ��SPI����
  	status =SPI_RW(reg);			  //���ͼĴ����� 
  	SPI_RW(value);      			  //д��Ĵ�����ֵ
  	NRF24L01_CSN_ON;                  //��ֹSPI����	   
  	return(status);       			  //����״ֵ̬
}

//��ȡ�Ĵ���
u8 NRF24L01_Read_Reg(u8 reg){
	u8 reg_val;	
   	NRF24L01_CSN_OFF;                 //ʹ��SPI����
  	SPI_RW(reg);			  		  //���ͼĴ����� 
	reg_val = SPI_RW(0XFF);			  //��ȡ�Ĵ�����ֵ
  	NRF24L01_CSN_ON;                  //��ֹSPI����	   
  	return(reg_val);       			  //����״ֵ̬
}




//����NRF24L01����һ������
//txbuf:�����������׵�ַ
//����ֵ:�������״��
u8 NRF24L01_TxPacket(u8 *txbuf)
{
	u8 sta;
	NRF24L01_CE_OFF;
  	NRF24L01_Write_Buf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);//д���ݵ�TX BUF  32���ֽ�
 	NRF24L01_CE_ON;//��������	   
	while(NRF24L01_Read_Reg(STATUS)!=0);//�ȴ��������
	sta=NRF24L01_Read_Reg(STATUS);  //��ȡ״̬�Ĵ�����ֵ	   
	if(sta&MAX_TX)//�ﵽ����ط�����
	{
		NRF24L01_Write_Reg(FLUSH_TX,0xff);//���TX FIFO�Ĵ��� 
		return MAX_TX; 
	}
	if(sta&TX_OK)//�������
	{
		return TX_OK;
	}
	return 0xff;//����ԭ����ʧ��
}


//�ú�����ʼ��NRF24L01��RXģʽ
//����RX��ַ,дRX���ݿ��,ѡ��RFƵ��,�����ʺ�LNA HCURR
//��CE��ߺ�,������RXģʽ,�����Խ���������
u8 NRF24L01_RxPacket(u8 *rxbuf)
{
	u8 status;		    							     
	status = NRF24L01_Read_Reg(STATUS);  //��ȡ״̬�Ĵ�����ֵ    	 
	NRF24L01_Write_Reg(SPI_WRITE_REG+STATUS,status); //���TX_DS��MAX_RT�жϱ�־
	if(status&RX_OK)//���յ�����
	{
		NRF24L01_Read_Buf(RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);//��ȡ����
		NRF24L01_Write_Reg(FLUSH_RX,0xff);//���RX FIFO�Ĵ��� 
		return 0; 
	}	   
	return 1;//û�յ��κ�����
}


//����NRF24L01����һ������
//txbuf:�����������׵�ַ
//����ֵ:0��������ɣ��������������
void SPI_RX_Mode(void)
{
	NRF24L01_CE_OFF;	  
  	NRF24L01_Write_Buf(SPI_WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH);//дRX�ڵ��ַ
	  
  	NRF24L01_Write_Reg(SPI_WRITE_REG+EN_AA,0x01);    //ʹ��ͨ��0���Զ�Ӧ��    
  	NRF24L01_Write_Reg(SPI_WRITE_REG+EN_RXADDR,0x01);//ʹ��ͨ��0�Ľ��յ�ַ  	 
  	NRF24L01_Write_Reg(SPI_WRITE_REG+RF_CH,40);	     //����RFͨ��Ƶ��		  
  	NRF24L01_Write_Reg(SPI_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);//ѡ��ͨ��0����Ч���ݿ�� 	    
  	NRF24L01_Write_Reg(SPI_WRITE_REG+RF_SETUP,0x0f);//����TX�������,0db����,2Mbps,���������濪��   
  	NRF24L01_Write_Reg(SPI_WRITE_REG+CONFIG, 0x0f);//���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ 
  	NRF24L01_CE_ON; //CEΪ��,�������ģʽ 
}						 
//�ú�����ʼ��NRF24L01��TXģʽ
//����TX��ַ,дTX���ݿ��,����RX�Զ�Ӧ��ĵ�ַ,���TX��������,ѡ��RFƵ��,�����ʺ�LNA HCURR
//PWR_UP,CRCʹ��
//��CE��ߺ�,������RXģʽ,�����Խ���������		   
//CEΪ�ߴ���10us,����������.	 

void SPI_TX_Mode(void)
{														 
	NRF24L01_CE_OFF;	    
  	NRF24L01_Write_Buf(SPI_WRITE_REG+TX_ADDR,(u8*)TX_ADDRESS,TX_ADR_WIDTH);//дTX�ڵ��ַ 
  	NRF24L01_Write_Buf(SPI_WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH); //����TX�ڵ��ַ,��ҪΪ��ʹ��ACK	  

  	NRF24L01_Write_Reg(SPI_WRITE_REG+EN_AA,0x01);     //ʹ��ͨ��0���Զ�Ӧ��    
  	NRF24L01_Write_Reg(SPI_WRITE_REG+EN_RXADDR,0x01); //ʹ��ͨ��0�Ľ��յ�ַ  
  	NRF24L01_Write_Reg(SPI_WRITE_REG+SETUP_RETR,0x1a);//�����Զ��ط����ʱ��:500us + 86us;����Զ��ط�����:10��
  	NRF24L01_Write_Reg(SPI_WRITE_REG+RF_CH,40);       //����RFͨ��Ϊ40
  	NRF24L01_Write_Reg(SPI_WRITE_REG+RF_SETUP,0x0f);  //����TX�������,0db����,2Mbps,���������濪��   
  	NRF24L01_Write_Reg(SPI_WRITE_REG+CONFIG,0x0e);    //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ,���������ж�
	NRF24L01_CE_ON;//CEΪ��,10us����������
}		  

