#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
//#include "PWM.h"
//#include "IC.h"
#include "TimerSR06.h"
#include "HCSR04.h"

uint64_t numlen(uint64_t num)//�������ֵĳ���
{
    uint64_t len = 1;        // ��ʼ����Ϊ1
    for(; num > 9; ++len)    // �ж�num�Ƿ����9�����򳤶�+1
        num /= 10;	         // ʹ�ó����������㣬ֱ��numС��1
    return len;              // ���س��ȵ�ֵ
}

int main(void)
{
	OLED_Init();
//	PWM_Init();
//	IC_Init();
	Timer_Init();		//��ʼ����ʱ��
	HC_SR04_Init();		//��ʼ�����������ģ��
	
	OLED_ShowString(1, 1, "Distance:");		//OLED������ַ���
	
//	OLED_ShowString(1, 1, "Freq:00000Hz");
//	OLED_ShowString(2, 1, "Duty:00%");
	
//	PWM_SetPrescaler(720 - 1);			//Freq = 72M / (PSC + 1) / 100
//	PWM_SetCompare1(50);				//Duty = CCR / 100
	OLED_ShowChar(4, 3, '.');
	while (1)
	{
		int Distance_mm=sonar_mm();			//��ȡ��������������λ���ף�mm��
		
		int Distance_m=Distance_mm/1000;	//ת��Ϊ�ף�m��Ϊ��λ�����������ַ���Distance_m
		int Distance_m_p=Distance_mm%1000;	//ת��Ϊ�ף�m��Ϊ��λ����С�����ַ���Distance_m_p
		
		OLED_ShowNum(2, 1,Distance_m,numlen(Distance_m));	//��ʾ�����������������
		OLED_ShowChar(2, 1+numlen(Distance_m), '.');		//��ʾС����
		if(Distance_m_p<100){								//�ж��Ƿ�С��100����
			OLED_ShowChar(2, 1+numlen(Distance_m)+1,'0');								//��Ϊ��λ���ף�����С��10cmʱҪ��0
			OLED_ShowNum(2, 1+numlen(Distance_m)+2,Distance_m_p,numlen(Distance_m_p));	//��ʾ���������С������
			OLED_ShowChar(2, 1+numlen(Distance_m)+2+numlen(Distance_m_p), 'm');			//��ʾ��λ
		}else																			// https://blog.zeruns.tech
		{
			OLED_ShowNum(2, 1+numlen(Distance_m)+1,Distance_m_p,numlen(Distance_m_p));	//��ʾ���������С������
			OLED_ShowChar(2, 1+numlen(Distance_m)+1+numlen(Distance_m_p), 'm');			//��ʾ��λ
		}
		OLED_ShowNum(3, 1,Distance_mm,numlen(Distance_mm));		//��ʾ��λΪ���׵ľ�����
		OLED_ShowString(3, 1 + numlen(Distance_mm), "mm");
		Delay_ms(300);						//��ʱ300����
		
	}

}
