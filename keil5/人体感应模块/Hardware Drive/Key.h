#ifndef __KEY_H
#define __KEY_H 


void Key_Init(void);
uint8_t	Key_GetNum(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void LED_Turn(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);


#endif
