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
	token1 = strtok(str1,point);					//取整数字符串 
	token2 = strtok(NULL,point);					//取小数字符串 
	printf("%s\n",token1);    	
	printf("%s\n",token2);    
	                          
	intNum = atoi(token1);							//取十进制整数有效部分 
	floatNum = atoi(token2);						//取十进制小数有效部分
	if(sign == 1)           
		intNum %= (int)pow(10,strlen(token1) - 1);	//负数去掉符号位
	strcpy(FloatChar,token2);						//截取十进制小数部分 
	
	
	itoa(intNum,IntChar,2);		 					//取二进制带符号整数字符串
	intNum = atoi(IntChar);							//取二进制带符号整数
	                  	
								
	intNum /= 10;									//去掉整数首部分的1 
	printf("%s\n",IntChar);    	
	
	itoa(intNum,IntChar,10);		 				//取二进制无符号无头整数字符串 
	                        
	
	if(intNum > 0)								
		shift = strlen(IntChar)  + 127;		 	//整数偏移量
	else{
			int j = 0;
			for(int i = 0; floatNum < (int)pow(10,strlen(FloatChar)); i++){
				floatNum *= 2;
				j++;
			}
			floatNum /= 2;										
			shift = 127 - j; 						//小数偏移量
	} 
	
	itoa(shift,ShiftChar,2);						//取偏移量二进制字符串 
	 
	
	int flt_len = strlen(FloatChar);				//取小数部分长度 
	
	 
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
		FloatChar[32] = '\0';												//小数转换二进制字符串
	
	printf("%s\n",ShiftChar);
	printf("%s\n",IntChar);  
	printf("%s\n",FloatChar); 
	

	
	
	if(sign == 0)						//输入符号位	
		str[0] = '0'; 							 
		else 
			str[0] = '1';
						
					
	for(int i = 1, j = 0; i < 9; i++){				//偏移量输入 
		if((i + strlen(ShiftChar)) < 8){
			str[i] = '0';							//高位补零 
		}
		else{
				str[i] = ShiftChar[j];
		}
		j++;	
	}
		
		
	
	for(int i= 0; (IntChar[i] != '\0') && ((i + 9 ) < 32); i++){
		str[9 + i] = IntChar[i];									//整数串输入 
	}
	int len = strlen(str);
	for(int i = 0; i < 32 - len; i++){
		if(FloatChar != '\0')
			str[len + i] = FloatChar[i];									//小数串输入 
		else break;
	}
	str[32] = '\0';
	
	if(strlen(str) < 32){
		for(int i = strlen(str); i < 32; i++){
			str[i] = '0';											//尾部补0 
		}
		str[32] = '\0';
	}		
	
	num = atoi(str);												//取二进制小数 
	printf("%s\n",str);
	printf("%d\n",strlen(str));

	return num;
}
int main(){
	int itg,flt,a = 0;
	a = my_int_float();
	printf("%d\n",a);
}

