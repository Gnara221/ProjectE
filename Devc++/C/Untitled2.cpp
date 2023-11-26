#include <stdio.h>
#include <stdlib.h>

#define uint32 unsigned int
#define uint8 unsigned char

void FuncOutputBin(int value)
{
	char string[33];   //形参类型uint32最大为32位，因此我这里定义了大小为33的字符串数组存放
	itoa(value, string, 2);  
	printf("库函数得到的二进制为：%s\r\n",string);
}

//用短除法的思想得到二进制，之后将数据从后往前读取 
void ShortDivOutputBin(uint32 input)
{
	uint8 temp[33] = {0};  
	int i = 0;
	printf("短除法得到的二进制为：");
	while(input)
	{
		temp[i] = input % 2;	//取余数存放到数组中，此为得到的二进制数
		input = (uint32)input / 2;  //短除，while中判断是否除尽
		i++;  //存储了一个二进制数，自加存储下一个
	}
	for(i--; i>=0; i--)  //由于最后一次input为0无效，i还是自加了，因此最后一次自加的值是无用的，所以先自减，然后将余数从后往前读取
    {
		printf("%d",temp[i]);
	}
	printf("\r\n");
}

int main(void)
{
	int input = 0;
	printf("请输入一个需要转化为2进制的整形数据：");
	scanf("%d", &input); 
	FuncOutputBin(input);
	ShortDivOutputBin(input);	
} 

