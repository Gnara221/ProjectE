/******************* ********************
 * 文件名  ：motor.c
 * 描  述  ：motor 应用函数库
 *          
 * 实验平台：基于STM32F103C8T6  四轴飞行器V1.0
 * 库版本  ：ST3.0.0 

* 程序版本：V1.0
* 程序日期：2020-04-27
* 程序作者：Lizh023@163.com
* 版权所有：CSUer																										  
*********************************************************/
#include "led.h"
#include "stm32f10x.h" 

 /***************  配置LED用到的I/O口 *******************/
void LED_GPIO_Config(void)	
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE); // 使能PB端口时钟  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_9|GPIO_Pin_8;	//选择对应的引脚 分别对应LED3、LED1、LED2
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);  //初始化PC端口
  GPIO_SetBits(GPIOB, GPIO_Pin_10 );	 // 关闭所有LED
	GPIO_SetBits(GPIOB, GPIO_Pin_9 );	 // 关闭所有LED
	GPIO_SetBits(GPIOB, GPIO_Pin_8 );	 // 关闭所有LED
}



