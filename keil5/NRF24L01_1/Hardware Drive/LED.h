#ifndef __LED_H
#define __LED_H


void LED_Init(void);
void LED_SET_ON(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);		//第一个参数选引脚，第二个参数选针脚
void LED_SET_OFF(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);		



#endif
