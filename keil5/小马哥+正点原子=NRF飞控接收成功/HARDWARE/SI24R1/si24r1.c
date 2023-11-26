//#include "stm32f10x.h"
#include "si24r1.h"
#include "spi.h"
#include "delay.h"
#include "led.h"
#include "stdio.h"
#include "stdlib.h"
//#include "paramsave.h"
//#include "remotedata.h"



#define SI24R1AddrMax 50 //NRF最后一个字节地址最大为50

uint8_t SI24R1addr = 0xFF; //初始化NRF最后一字节地址

uint8_t SI24R1_TX_DATA[TX_PAYLO_WIDTH];//NRF发送缓冲区
uint8_t SI24R1_RX_DATA[RX_PAYLO_WIDTH];//NRF接收缓冲区

uint8_t TX_ADDRESS[TX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //发送地址
uint8_t RX_ADDRESS[RX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //接收地址


/*****************************************************************************
* 函  数：void SI24R1_Init(void)
* 功  能：NRF引脚GPIO初始化
* 参  数：无
* 返回值：无
* 备  注：无
*****************************************************************************/
void SI24R1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct; 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA,ENABLE);
	
	/*   配置CSN引脚   */
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	
	/*  配置CE引脚  */
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	GPIO_ResetBits(GPIOA,GPIO_Pin_8);
		
	SPI_GPIO_Init(); //SPI2初始化

	SI24R1_Check(); //检查SI24R1是否与MCU通信                                    

	SI24R1_CSN_HIGH; //失能NRF
	SI24R1_CE_LOW; 	 //待机模式
}

/*****************************************************************************
* 函  数：uint8_t SI24R1_write_reg(uint8_t reg,uint8_t value)
* 功  能：写一字节数据到寄存器
* 参  数：reg： 寄存器地址
*         val:  要写入的数据
* 返回值：status
* 备  注：SI24R1代码移植只需把SPI驱动修改成自己的即可
*****************************************************************************/
uint8_t SI24R1_write_reg(uint8_t reg,uint8_t value)
{
	uint8_t status;
	
	SI24R1_CSN_LOW;
	status=SPI2_WriteReadByte(reg);
	SPI2_WriteReadByte(value);
	SI24R1_CSN_HIGH;
	
	return status;
}

/*****************************************************************************
* 函  数：uint8_t SI24R1_read_reg(uint8_t reg)
* 功  能：读一字节数据到寄存器
* 参  数：reg： 寄存器地址
* 返回值：reg_val
* 备  注：SI24R1代码移植只需把SPI驱动修改成自己的即可
*****************************************************************************/
uint8_t SI24R1_read_reg(uint8_t reg)
{
	uint8_t reg_val;
	
	SI24R1_CSN_LOW;
	SPI2_WriteReadByte(reg);
	reg_val = SPI2_WriteReadByte(0xff);
	SI24R1_CSN_HIGH;
	
	return reg_val;
}

/*****************************************************************************
* 函  数：uint8_t SI24R1_Write_Buf(uint8_t reg, uint8_t *pBuf, uint8_t len)
* 功  能：写一组数据到寄存器
* 参  数：reg： 寄存器地址
*         pBuf： 要写入数据的地址
*         len:  要写入的数据长度
* 返回值：status
* 备  注：SI24R1代码移植只需把SPI驱动修改成自己的即可
*****************************************************************************/
uint8_t SI24R1_Write_Buf(uint8_t reg, uint8_t *pBuf, uint8_t len)
{
	uint8_t status;
	int i;
	
	SI24R1_CSN_LOW;
	status = SPI2_WriteReadByte(reg);
	for( i=0;i<len;i++)
	{
		SPI2_WriteReadByte(*pBuf);
		pBuf++;
	}
	SI24R1_CSN_HIGH;
	
	return status;
}

/*****************************************************************************
* 函  数：uint8_t SI24R1_Read_Buf(uint8_t reg, uint8_t *pBuf, uint8_t len)
* 功  能：读一组数据到寄存器
* 参  数：reg： 	寄存器地址
*         pBuf： 要读取数据的地址
*         len:  	要读取的数据长度
* 返回值：status
* 备  注：SI24R1代码移植只需把SPI驱动修改成自己的即可
*****************************************************************************/
uint8_t SI24R1_Read_Buf(uint8_t reg, uint8_t *pBuf, uint8_t len)
{
	uint8_t status;
	int i;
	
	SI24R1_CSN_LOW;
	status = SPI2_WriteReadByte(reg);
	for(i = 0;i < len ;i++)
	{
		*pBuf = SPI2_WriteReadByte(0xff);
		pBuf++;
	}
	SI24R1_CSN_HIGH;
	
	return status;
}

/*****************************************************************************
* 函  数：void SI24R1set_Mode(uint8_t mode)
* 功  能：切换SI24R1的工作模式模式
* 参  数：无
* 返回值：无
* 备  注：无
*****************************************************************************/
void SI24R1set_Mode(uint8_t mode)
{
	if(mode == IT_TX)
	{
		SI24R1_CE_LOW;
		SI24R1_write_reg(W_REGISTER+CONFIG,IT_TX);
		SI24R1_write_reg(W_REGISTER+STATUS,0X7E); //清除所有中断,防止一进去发送模式就触发中断	
		SI24R1_CE_HIGH;
//		Delay_us(15);
	}
	else
	{
		SI24R1_CE_LOW;
		SI24R1_write_reg(W_REGISTER+CONFIG,IT_RX);//配置为接收模式
		SI24R1_write_reg(W_REGISTER+STATUS,0X7E); //清除所有中断,防止一进去接收模式就触发中断
		SI24R1_CE_HIGH;
		Delay_us(200);
	}		
}

/*****************************************************************************
* 函  数：void SI24R1_Config(void)
* 功  能：SI24R1基本参数配置，并初始化为接收模式
* 参  数：无
* 返回值：无
* 备  注：无
*****************************************************************************/
void SI24R1_Config(void)
{
	SI24R1_CE_LOW;
	SI24R1_write_reg(W_REGISTER+SETUP_AW, 0x03); //配置通信地址的长度，默认值时0x03,即地址长度为5字节
	SI24R1_Write_Buf(W_REGISTER+TX_ADDR,(uint8_t*)TX_ADDRESS,TX_ADR_WIDTH); //写TX节点地址 
	SI24R1_Write_Buf(W_REGISTER+RX_ADDR_P0,(uint8_t*)TX_ADDRESS,RX_ADR_WIDTH); //设置TX节点地址,主要为了使能ACK
	SI24R1_write_reg(W_REGISTER+SETUP_RETR,0x1A); //设置自动重发间隔时间:500us + 86us;最大自动重发次数:10次 0x1A
	
	SI24R1_write_reg(W_REGISTER+EN_RXADDR,0x01);//使能通道0的接收地址  
	SI24R1_write_reg(W_REGISTER+EN_AA,0x01); //使能通道0自动应答
	SI24R1_write_reg(W_REGISTER+RX_PW_P0,RX_PAYLO_WIDTH);//选择通道0的有效数据宽度  
	SI24R1_Write_Buf(W_REGISTER+RX_ADDR_P0,(uint8_t*)RX_ADDRESS,RX_ADR_WIDTH); //写RX节点地址
	SI24R1_write_reg(W_REGISTER+RF_CH,30); //设置RF通道为40hz(1-64Hz都可以)
	SI24R1_write_reg(W_REGISTER+RF_SETUP,0x27); //设置TX发射参数,0db增益,2Mbps,低噪声增益关闭 （注意：低噪声增益关闭/开启直接影响通信,要开启都开启，要关闭都关闭0x0f）
	
	SI24R1set_Mode(IT_RX); //默认为接收模式
	
	SI24R1_CE_HIGH;
}	

/*****************************************************************************
* 函  数：uint8_t SI24R1_TxPacket(uint8_t *txbuf)
* 功  能：SI24R1发送一包数据
* 参  数：txbuf：要发送数据地址
* 返回值：无 
* 备  注：无
*****************************************************************************/
void SI24R1_TxPacket(uint8_t *txbuf)
{
	SI24R1_CE_LOW;	
	SI24R1_Write_Buf(W_REGISTER+TX_ADDR,(uint8_t*)TX_ADDRESS,TX_ADR_WIDTH);  //写TX节点地址 
	SI24R1_Write_Buf(W_REGISTER+RX_ADDR_P0,(uint8_t*)TX_ADDRESS,RX_ADR_WIDTH); //设置TX节点地址,主要为了使能ACK
	SI24R1_Write_Buf(W_RX_PAYLOAD,txbuf,TX_PAYLO_WIDTH); //写数据到TX_BUFF
	SI24R1_write_reg(W_REGISTER+CONFIG,0x0e);	//设置为发送模式,开启所有中断
	SI24R1_write_reg(W_REGISTER+STATUS,0X7E); //清除所有中断,防止一进去发送模式就触发中断
	SI24R1_CE_HIGH;
	Delay_us(10);  //CE持续高电平10us
}

/*****************************************************************************
* 函  数：uint8_t SI24R1_RxPacket(uint8_t *rxbuf)
* 功  能：SI24R1接收一包数据
* 参  数：rxbuf：接收数据存储地址
* 返回值：无
* 备  注：无
*****************************************************************************/
void SI24R1_RxPacket(uint8_t *rxbuf)
{
	SI24R1_CE_LOW;
	SI24R1_Read_Buf(R_RX_PAYLOAD,rxbuf,TX_PAYLO_WIDTH);//读取RX的有效数据
	SI24R1_write_reg(FLUSH_RX,0xff); //清除RX FIFO(注意：这句话很必要)
	SI24R1_CE_HIGH;
}

/*****************************************************************************
* 函  数：uint8_t SI24R1_testConnection(void)
* 功  能：检查SI24R1与MCU的SPI总线是否通信正常
* 参  数：无
* 返回值：1已连接 0未连接
* 备  注：无
*****************************************************************************/
uint8_t SI24R1_testConnection(void)
{
	uint8_t buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	uint8_t i; 	 
	SI24R1_Write_Buf(W_REGISTER+TX_ADDR,buf,5); //写入5个字节的地址.	
	SI24R1_Read_Buf(TX_ADDR,buf,5); //读出写入的地址  
	for(i=0;i<5;i++)
	if(buf[i]!=0XA5)break;	 							   
	if(i!=5)return 0; //检测24L01错误	
	return 1;	//检测到24L01
}

/*****************************************************************************
* 函  数：void SI24R1_Check(void)
* 功  能：检测SI24R1是否连接
* 参  数：无
* 返回值：无
* 备  注：无
*****************************************************************************/
void SI24R1_Check(void)
{
	while(SI24R1_testConnection()==1)
	{
		printf("\r SI24R1 is connect...\r\n");
		Delay_ms(1000);
		break;
	}
}

/*****************************************************************************
* 函  数：void SI24R1_GetAddr(void)
* 功  能：给飞机获取上的SI24R1获取一个地址
* 参  数：无
* 返回值：无 
* 备  注：此函数需要与遥控器的对频函数联合使用否者SI24R1通信不成功，
          如果自己做的的遥控器可直接用固定地址
*****************************************************************************/
void SI24R1_GetAddr(void)
{
	if(SI24R1addr > SI24R1AddrMax)//当 SI24R1addr大于10，就说明次时SI24R1还未初始化完成
	{
		srand(SysTick->VAL);//给随机数种子
//		printf("SysTick->VAL:%d\r\n",SysTick->VAL);
		SI24R1addr = rand()%SI24R1AddrMax;//随机获取SI24R1最后一位地址（地址:0~50）
//		PID_WriteFlash();//保存此地址Flash
	}else if(SI24R1addr != TX_ADDRESS[TX_ADR_WIDTH-1])
	{
		TX_ADDRESS[TX_ADR_WIDTH-1] = SI24R1addr;
		RX_ADDRESS[TX_ADR_WIDTH-1] = SI24R1addr;
		SI24R1_Config();
//		printf("SI24R1Addr:%d\r\n",SI24R1addr);
	}
}

/*****************************************************************************
* 函  数：void SI24R1_Test(void)
* 功  能：SI24R1通信测试函数
* 参  数：无
* 返回值：无 
* 备  注：测试时用
*****************************************************************************/
void SI24R1_Test(void)
{
	uint8_t t=0;
	static uint8_t mode,key;
	mode = ' ';
	key=mode;
	for(t=0;t<32;t++)
	{
		key++;
		if(key>('~'))key=' ';
		SI24R1_TX_DATA[t]=key;	
	}
	mode++; 
	if(mode>'~')mode=' ';  	  		
	SI24R1_TxPacket(SI24R1_TX_DATA);
}






//原子哥程序修改

//SPI写寄存器
//reg:指定寄存器地址
//value:写入的值


uint8_t NRF24L01_Write_Reg(uint8_t reg,uint8_t value)
{
		uint8_t status;	
   	SI24R1_CSN_LOW;                 //使能SPI传输
	
  	status =SPI2_ReadWriteByte(reg);//发送寄存器号 
  	SPI2_ReadWriteByte(value);      //写入寄存器的值
  	SI24R1_CSN_HIGH;               //禁止SPI传输	   
  	return(status);       			//返回状态值
}

//读取SPI寄存器值
//reg:要读的寄存器
uint8_t NRF24L01_Read_Reg(uint8_t reg)
{
		uint8_t reg_val;	    
		SI24R1_CSN_LOW;          //使能SPI传输		
  	SPI2_ReadWriteByte(reg);   //发送寄存器号
  	reg_val=SPI2_ReadWriteByte(0XFF);//读取寄存器内容
  	SI24R1_CSN_HIGH;          //禁止SPI传输		    
  	return(reg_val);           //返回状态值
}	



//在指定位置读出指定长度的数据
//reg:寄存器(位置)
//*pBuf:数据指针
//len:数据长度
//返回值,此次读到的状态寄存器值 
uint8_t NRF24L01_Read_Buf(uint8_t reg,uint8_t *pBuf,uint8_t len)
{
	uint8_t status,u8_ctr;	       
  	SI24R1_CSN_LOW;           //使能SPI传输
  	status=SPI2_ReadWriteByte(reg);//发送寄存器值(位置),并读取状态值   	   
 	for(u8_ctr=0;u8_ctr<len;u8_ctr++)pBuf[u8_ctr]=SPI2_ReadWriteByte(0XFF);//读出数据
  	SI24R1_CSN_HIGH;       //关闭SPI传输
  	return status;        //返回读到的状态值
}

//在指定位置写指定长度的数据
//reg:寄存器(位置)
//*pBuf:数据指针
//len:数据长度
//返回值,此次读到的状态寄存器值
uint8_t NRF24L01_Write_Buf(uint8_t reg, uint8_t *pBuf, uint8_t len)
{
		uint8_t status,u8_ctr;	    
		SI24R1_CSN_LOW;          //使能SPI传输
  	status = SPI2_ReadWriteByte(reg);//发送寄存器值(位置),并读取状态值
  	for(u8_ctr=0; u8_ctr<len; u8_ctr++)SPI2_ReadWriteByte(*pBuf++); //写入数据	 
  	SI24R1_CSN_HIGH;       //关闭SPI传输
  	return status;          //返回读到的状态值
}		


				   
//启动NRF24L01发送一次数据
//txbuf:待发送数据首地址
//返回值:发送完成状况
uint8_t NRF24L01_TxPacket(uint8_t *txbuf)
{
	uint8_t sta;
// 	SPI2_SetSpeed(SPI_BaudRatePrescaler_8);//spi速度为9Mhz（24L01的最大SPI时钟为10Mhz）   
	SI24R1_CE_LOW;
  NRF24L01_Write_Buf(W_RX_PAYLOAD,txbuf,TX_PAYLO_WIDTH);//写数据到TX BUF  32个字节
 	SI24R1_CE_HIGH;//启动发送	   
	while(NRF24L01_IRQ!=0);//等待发送完成
	sta=NRF24L01_Read_Reg(STATUS);  //读取状态寄存器的值	   
	NRF24L01_Write_Reg(W_REGISTER+STATUS,sta); //清除TX_DS或MAX_RT中断标志
	if(sta&MAX_TX)//达到最大重发次数
	{
		NRF24L01_Write_Reg(FLUSH_TX,0xff);//清除TX FIFO寄存器 
		return MAX_TX; 
	}
	if(sta&TX_OK)//发送完成
	{
		return TX_OK;
	}
	return 0xff;//其他原因发送失败
}


//启动NRF24L01发送一次数据
//txbuf:待发送数据首地址
//返回值:0，接收完成；其他，错误代码
uint8_t NRF24L01_RxPacket(uint8_t *rxbuf)
{
	uint8_t sta;		    							   
//	SPI2_SetSpeed(SPI_BaudRatePrescaler_8); //spi速度为9Mhz（24L01的最大SPI时钟为10Mhz）   
	sta=NRF24L01_Read_Reg(STATUS);  //读取状态寄存器的值    	 
	NRF24L01_Write_Reg(W_REGISTER+STATUS,sta); //清除TX_DS或MAX_RT中断标志
	if(sta&RX_OK)//接收到数据
	{
		NRF24L01_Read_Buf(R_RX_PAYLOAD,rxbuf,RX_PAYLO_WIDTH);//读取数据
		NRF24L01_Write_Reg(FLUSH_RX,0xff);//清除RX FIFO寄存器 
		return 0; 
	}	   
	return 1;//没收到任何数据
}	

//该函数初始化NRF24L01到RX模式
//设置RX地址,写RX数据宽度,选择RF频道,波特率和LNA HCURR
//当CE变高后,即进入RX模式,并可以接收数据了		   
void NRF24L01_RX_Mode(void)
{
		SI24R1_CE_LOW;	  
  	NRF24L01_Write_Buf(W_REGISTER+RX_ADDR_P0,(uint8_t*)RX_ADDRESS,RX_ADR_WIDTH);//写RX节点地址
	  
  	NRF24L01_Write_Reg(W_REGISTER+EN_AA,0x01);    	//使能通道0的自动应答    
  	NRF24L01_Write_Reg(W_REGISTER+EN_RXADDR,0x01);	//使能通道0的接收地址  	 
  	NRF24L01_Write_Reg(W_REGISTER+RF_CH,40);	    	//设置RF通信频率		  
  	NRF24L01_Write_Reg(W_REGISTER+RX_PW_P0,RX_PAYLO_WIDTH);//选择通道0的有效数据宽度 	    
  	NRF24L01_Write_Reg(W_REGISTER+RF_SETUP,0x0f);	//设置TX发射参数,0db增益,2Mbps,低噪声增益开启   
  	NRF24L01_Write_Reg(W_REGISTER+CONFIG, 0x0f);		//配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式 
  	SI24R1_CE_HIGH; //CE为高,进入接收模式 
}		




