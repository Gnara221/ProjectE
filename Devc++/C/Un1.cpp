#include <stdio.h>

int main(){
	float temp;
	int mantissa;
	int fraction;	   
	temp=(float)(84*1000000)/(9600*16);//�õ�USARTDIV
	mantissa=temp;				 //�õ���������
	fraction=(temp-mantissa)*16; //�õ�С������	 
    mantissa<<=4;
	mantissa+=fraction;
	printf("%x\n",mantissa);
}
