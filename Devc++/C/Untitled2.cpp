#include <stdio.h>
#include <stdlib.h>

#define uint32 unsigned int
#define uint8 unsigned char

void FuncOutputBin(int value)
{
	char string[33];   //�β�����uint32���Ϊ32λ����������ﶨ���˴�СΪ33���ַ���������
	itoa(value, string, 2);  
	printf("�⺯���õ��Ķ�����Ϊ��%s\r\n",string);
}

//�ö̳�����˼��õ������ƣ�֮�����ݴӺ���ǰ��ȡ 
void ShortDivOutputBin(uint32 input)
{
	uint8 temp[33] = {0};  
	int i = 0;
	printf("�̳����õ��Ķ�����Ϊ��");
	while(input)
	{
		temp[i] = input % 2;	//ȡ������ŵ������У���Ϊ�õ��Ķ�������
		input = (uint32)input / 2;  //�̳���while���ж��Ƿ����
		i++;  //�洢��һ�������������ԼӴ洢��һ��
	}
	for(i--; i>=0; i--)  //�������һ��inputΪ0��Ч��i�����Լ��ˣ�������һ���Լӵ�ֵ�����õģ��������Լ���Ȼ�������Ӻ���ǰ��ȡ
    {
		printf("%d",temp[i]);
	}
	printf("\r\n");
}

int main(void)
{
	int input = 0;
	printf("������һ����Ҫת��Ϊ2���Ƶ��������ݣ�");
	scanf("%d", &input); 
	FuncOutputBin(input);
	ShortDivOutputBin(input);	
} 

