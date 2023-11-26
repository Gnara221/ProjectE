#ifndef __NRF24L01_H__
#define __NRF24L01_H__

//NRF24L01�Ĵ�����������
#define SPI_READ_REG        0x00  //�����üĴ���,��5λΪ�Ĵ�����ַ
#define SPI_WRITE_REG       0x20  //д���üĴ���,��5λΪ�Ĵ�����ַ
#define RD_RX_PLOAD     0x61  //��RX��Ч����,1~32�ֽ�
#define WR_TX_PLOAD     0xA0  //дTX��Ч����,1~32�ֽ�
#define FLUSH_TX        0xE1  //���TX FIFO�Ĵ���.����ģʽ����
#define FLUSH_RX        0xE2  //���RX FIFO�Ĵ���.����ģʽ����
#define REUSE_TX_PL     0xE3  //����ʹ����һ������,CEΪ��,���ݰ������Ϸ���.
#define NOP             0xFF  //�ղ���,����������״̬�Ĵ���	 
//SPI(NRF24L01)�Ĵ�����ַ
#define CONFIG          0x00  //���üĴ�����ַ;bit0:1����ģʽ,0����ģʽ;bit1:��ѡ��;bit2:CRCģʽ;bit3:CRCʹ��;
                              //bit4:�ж�MAX_RT(�ﵽ����ط������ж�)ʹ��;bit5:�ж�TX_DSʹ��;bit6:�ж�RX_DRʹ��
#define EN_AA           0x01  //ʹ���Զ�Ӧ����  bit0~5,��Ӧͨ��0~5
#define EN_RXADDR       0x02  //���յ�ַ����,bit0~5,��Ӧͨ��0~5
#define SETUP_AW        0x03  //���õ�ַ���(��������ͨ��):bit1,0:00,3�ֽ�;01,4�ֽ�;02,5�ֽ�;
#define SETUP_RETR      0x04  //�����Զ��ط�;bit3:0,�Զ��ط�������;bit7:4,�Զ��ط���ʱ 250*x+86us
#define RF_CH           0x05  //RFͨ��,bit6:0,����ͨ��Ƶ��;
#define RF_SETUP        0x06  //RF�Ĵ���;bit3:��������(0:1Mbps,1:2Mbps);bit2:1,���书��;bit0:�������Ŵ�������
#define STATUS          0x07  //״̬�Ĵ���;bit0:TX FIFO����־;bit3:1,��������ͨ����(���:6);bit4,�ﵽ�����ط�
                              //bit5:���ݷ�������ж�;bit6:���������ж�;
#define MAX_TX  	0x10  //�ﵽ����ʹ����ж�
#define TX_OK   	0x20  //TX��������ж�
#define RX_OK   	0x40  //���յ������ж�
//24L01���ͽ������ݿ�ȶ���
#define TX_ADR_WIDTH    5   //5�ֽڵĵ�ַ���
#define RX_ADR_WIDTH    5   //5�ֽڵĵ�ַ���
#define TX_PLOAD_WIDTH  32  //20�ֽڵ��û����ݿ��
#define RX_PLOAD_WIDTH  32  //20�ֽڵ��û����ݿ��



#define CONFIG 0x00					// 'Config' register address
#define EN_AA 0x01					// 'Enable Auto Acknowledgment' register address
#define EN_RXADDR 0x02				// 'Enabled RX addresses' register address
#define SETUP_AW 0x03				// 'Setup address width' register address
#define SETUP_RETR 0x04 			// 'Setup Auto. Retrans' register address#define RF_CH Ox05// 'RF channel' register address
#define RF_SETUP 0x06				// 'RF setup' register address
#define STATUS 0x07 				// 'Status' register address
#define OBSERVE_TX 0x08				// 'Observe TX' register address
#define CD 0x09						// 'Carrier Detect' register address
#define RX_ADDR_P0 0x0A				// 'RX address pipe0' register address
#define RX_ADDR_P1 0x0B				// 'RX address pipe1' register address
#define RX_ADDR_P2 0x0C				// 'RX address pipe2' register address
#define RX_ADDR_P3 0x0D				//'RX address pipe3' register address
#define RX_ADDR_P4 0x0E				// 'RX address pipe4' register address
#define RX_ADDR_P5 0x0F				//'RX address pipe5' register address
#define TX_ADDR 0x10				// 'TX address' register address
#define RX_PW_P0 0x11				// 'RX payload width, pipe0' register address
#define RX_PW_P1 0x12				// 'RX payload width, pipel' register address
#define RX_PW_P2 0x13				// 'RX payload width, pipe2' register address
#define RX_PW_P3 0x14				// 'RX payload width, pipe3' register address
#define RX_PW_P4 0x15				// 'RX payload width, pipe4' register address
#define RX_PW_P5 0x16				// 'RX payload width, pipe5' register address
#define FIFO_STATUS 0x17			// 'FIFO Status Register' register address

void NRF24L01_Init(void);
u8 NRF24L01_Check(void);
u8 NRF24L01_Read_Buf(u8 reg,u8 *pBuf,u8 len);
u8 NRF24L01_Write_Buf(u8 reg, u8 *pBuf, u8 len);
u8 NRF24L01_Write_Reg(u8 reg,u8 value);
u8 NRF24L01_Read_Reg(u8 reg);
u8 NRF24L01_TxPacket(u8 *txbuf);
u8 NRF24L01_RxPacket(u8 *rxbuf);
void SPI_RX_Mode(void);
void SPI_TX_Mode(void);
#endif
