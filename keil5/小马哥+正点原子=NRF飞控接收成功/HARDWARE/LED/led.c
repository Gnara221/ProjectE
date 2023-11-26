/******************* ********************
 * �ļ���  ��motor.c
 * ��  ��  ��motor Ӧ�ú�����
 *          
 * ʵ��ƽ̨������STM32F103C8T6  ���������V1.0
 * ��汾  ��ST3.0.0 

* ����汾��V1.0
* �������ڣ�2020-04-27
* �������ߣ�Lizh023@163.com
* ��Ȩ���У�CSUer																										  
*********************************************************/
#include "led.h"
#include "stm32f10x.h" 

 /***************  ����LED�õ���I/O�� *******************/
void LED_GPIO_Config(void)	
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE); // ʹ��PB�˿�ʱ��  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_9|GPIO_Pin_8;	//ѡ���Ӧ������ �ֱ��ӦLED3��LED1��LED2
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);  //��ʼ��PC�˿�
  GPIO_SetBits(GPIOB, GPIO_Pin_10 );	 // �ر�����LED
	GPIO_SetBits(GPIOB, GPIO_Pin_9 );	 // �ر�����LED
	GPIO_SetBits(GPIOB, GPIO_Pin_8 );	 // �ر�����LED
}



