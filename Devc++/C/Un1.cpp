#include <stdio.h>

int main(){
	float temp;
	int mantissa;
	int fraction;	   
	temp=(float)(84*1000000)/(9600*16);//得到USARTDIV
	mantissa=temp;				 //得到整数部分
	fraction=(temp-mantissa)*16; //得到小数部分	 
    mantissa<<=4;
	mantissa+=fraction;
	printf("%x\n",mantissa);
}
