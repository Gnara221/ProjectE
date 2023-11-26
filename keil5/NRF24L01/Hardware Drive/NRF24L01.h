#ifndef __NRF24L01_H__
#define __NRF24L01_H__

#define READ_REG Ox00 				// Define read command to register
#define WRITE_REG Ox20				// Define write command to register
#define RD_RX_PLOAD 0x61			// Define RX payload register address
#define WR_TX_PLOAD OxAO			// Define TX payload register address
#define FLUSH_TX OxE1				// Define flush TX register command
#define FLUSH_RX OxE2				// Define flush RX register command
#define REUSE_TX_PL OxE3			// Define reuse TX payload registercommand
#define NOP OxFF					// Define No Operation, might be used to readstatusregister


#define CONFIG Ox00					// 'Config' register address
#define EN_AA 0x01					// 'Enable Auto Acknowledgment' register address
#define EN_RXADDR Ox02				// 'Enabled RX addresses' register address
#define SETUP_AW 0x03				// 'Setup address width' register address
#define SETUP_RETR Ox04 			// 'Setup Auto. Retrans' register address#define RF_CH Ox05// 'RF channel' register address
#define RF_SETUP 0x06				// 'RF setup' register address
#define STATUS 0x07 				// 'Status' register address
#define OBSERVE_TX 0x08				// 'Observe TX' register address
#define CD 0x09						// 'Carrier Detect' register address
#define RX_ADDR_PO Ox0A				// 'RX address pipe0' register address
#define RX_ADDR_P1 OxOB				// 'RX address pipe1' register address
#define RX_ADDR_P2 0xOC				// 'RX address pipe2' register address
#define RX_ADDR_P3 OxOD				//'RX address pipe3' register address
#define RX_ADDR_P4 Ox0E				// 'RX address pipe4' register address
#define RX_ADDR_P5 OxOF				//'RX address pipe5' register address
#define TX_ADDR Ox10				// 'TX address' register address
#define RX_PW_PO Ox11				// 'RX payload width, pipe0' register address
#define RX_PW_P1 Ox12				// 'RX payload width, pipel' register address
#define RX_PW_P2 0x13				// 'RX payload width, pipe2' register address
#define RX_PW_P3 0x14				// 'RX payload width, pipe3' register address
#define RX_PW_P4 0x15				// 'RX payload width, pipe4' register address
#define RX_PW_P5 0x16				// 'RX payload width, pipe5' register address
#define FIFO_STATUS 0x17			// 'FIFO Status Register' register address




#endif
