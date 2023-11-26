#include "stm32f10x.h"                  // Device header

void AD_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);							//开启时钟
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);												//6分频，即ADCCLK = 72MHz/6 = 12MHZ
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;									//AIN模式会断开GPIO，
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	
	/*	  配置ADC  	*/
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);		//在规则组序列1的位置写入通道0最后一项为采样时间，此时为55.5个ADCCLK周期
	
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;							//数据右对齐
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;								//独立模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;				//不使用外部触发
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;								//单次转换
	ADC_InitStructure.ADC_NbrOfChannel = 1;											//通道数为1（此参数仅在扫描模式下有效）
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;									//非扫描模式			
	
	ADC_Init(ADC1,&ADC_InitStructure);
	ADC_Cmd(ADC1,ENABLE);
	
	/*	校准ADC	 */
	ADC_ResetCalibration(ADC1);														//复位校准,完成后会置0
	while (ADC_GetResetCalibrationStatus(ADC1) == SET);								//等待复位校准完成
	ADC_StartCalibration(ADC1);														//开始复位校准,完成后会置0
	while (ADC_GetCalibrationStatus(ADC1) == SET);									//等待校准完成
	
	
}

uint16_t AD_GetValue(void)	
{
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);											//软件触发转换
	while (ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);							//判断规则组是否转换完成，等待时间约为：1/12MHZ * （55.5采样时间 +12.5固定周期） = 5.6us
	return ADC_GetConversionValue(ADC1);											//获取ADC转换值,读取DR寄存器会自动清除EOC标志位，故不用手动清除
}
