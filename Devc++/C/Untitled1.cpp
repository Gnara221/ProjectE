#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


int my_int_float(){
	char str1[33],IntChar[33],FloatChar[33],str[33],ShiftChar[8];
	int num,intNum,floatNum,sign,shift = 0;
	printf("Input a float number:");
	gets(str1);
	const char point[1] = {'.'};
	if(str1[0] == '-'){
		str1[0] = '1';
		sign = 1;
		
	}
	char *token1,*token2;
	token1 = strtok(str1,point);					//ȡ�����ַ��� 
	token2 = strtok(NULL,point);					//ȡС���ַ��� 
	printf("%s\n",token1);    	
	printf("%s\n",token2);    
	                          
	intNum = atoi(token1);							//ȡʮ����������Ч���� 
	floatNum = atoi(token2);						//ȡʮ����С����Ч����
	if(sign == 1)           
		intNum %= (int)pow(10,strlen(token1) - 1);	//����ȥ������λ
	strcpy(FloatChar,token2);						//��ȡʮ����С������ 
	
	
	itoa(intNum,IntChar,2);		 					//ȡ�����ƴ����������ַ���
	intNum = atoi(IntChar);							//ȡ�����ƴ���������
	                  	
								
	intNum /= 10;									//ȥ�������ײ��ֵ�1 
	printf("%s\n",IntChar);    	
	
	itoa(intNum,IntChar,10);		 				//ȡ�������޷�����ͷ�����ַ��� 
	                        
	
	if(intNum > 0)								
		shift = strlen(IntChar)  + 127;		 	//����ƫ����
	else{
			int j = 0;
			for(int i = 0; floatNum < (int)pow(10,strlen(FloatChar)); i++){
				floatNum *= 2;
				j++;
			}
			floatNum /= 2;										
			shift = 127 - j; 						//С��ƫ����
	} 
	
	itoa(shift,ShiftChar,2);						//ȡƫ�����������ַ��� 
	 
	
	int flt_len = strlen(FloatChar);				//ȡС�����ֳ��� 
	
	 
	for(int i = 0; i < 32; i++)
	{
		floatNum *= 2;
		if(floatNum / (int)(pow(10,flt_len)) == 1){
			FloatChar[i] = '1';							
			if((floatNum % (int)pow(10,flt_len)) == 0)
				break;
		} else	FloatChar[i] = '0';
		floatNum %= (int)pow(10,flt_len);
	}
		FloatChar[32] = '\0';												//С��ת���������ַ���
	
	printf("%s\n",ShiftChar);
	printf("%s\n",IntChar);  
	printf("%s\n",FloatChar); 
	

	
	
	if(sign == 0)						//�������λ	
		str[0] = '0'; 							 
		else 
			str[0] = '1';
						
					
	for(int i = 1, j = 0; i < 9; i++){				//ƫ�������� 
		if((i + strlen(ShiftChar)) < 8){
			str[i] = '0';							//��λ���� 
		}
		else{
				str[i] = ShiftChar[j];
		}
		j++;	
	}
		
		
	
	for(int i= 0; (IntChar[i] != '\0') && ((i + 9 ) < 32); i++){
		str[9 + i] = IntChar[i];									//���������� 
	}
	int len = strlen(str);
	for(int i = 0; i < 32 - len; i++){
		if(FloatChar != '\0')
			str[len + i] = FloatChar[i];									//С�������� 
		else break;
	}
	str[32] = '\0';
	
	if(strlen(str) < 32){
		for(int i = strlen(str); i < 32; i++){
			str[i] = '0';											//β����0 
		}
		str[32] = '\0';
	}		
	
	num = atoi(str);												//ȡ������С�� 
	printf("%s\n",str);
	printf("%d\n",strlen(str));

	return num;
}
int main(){
	int itg,flt,a = 0;
	a = my_int_float();
	printf("%d\n",a);
}

