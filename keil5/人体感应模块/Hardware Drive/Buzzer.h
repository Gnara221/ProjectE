#ifndef __BUZZER_H
#define __BUZZER_H

void BUZZER_Init(void);
void Buzzer_ON(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void Buzzer_OFF(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);




#endif
