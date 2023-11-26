#ifndef __USART_H__
#define __USART_H__

void MyUSART_Init(void);
void SendByte(char ch);
u8 GetReceiveFlag(void);
 void ReceiveChar(void);
void SysteminitClock(void);
 
#endif
