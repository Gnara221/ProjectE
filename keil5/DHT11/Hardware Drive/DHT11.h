#ifndef __DHT11_H_
#define __DHT11_H_

void DHT11_Init(void);
void DHT_Mode(u8 mode);
void DHT_SendStaSign(void);
void DHT_SendResponse(void);
u8 DHT_Read_Byte(void);
void DHT_ReadDATA(u8 *humi,u8* temp);

#endif
