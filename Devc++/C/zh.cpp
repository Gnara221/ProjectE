/*
ieee754，要求如下，
定义函数 int my_int_float()
从键盘输入一个单精度浮点数的字符串，
然后自己解析该字符串，
并用位操作把对应的值按754格式保存到4字节里，
最后返回该四字节对应的整数值，
期间不能使用 float 和 double类型。

IEEE752
range: 10E38
precision: 8
1+8+23 = 32

*/
/*
 11111111111111111111111111111111
 3.14159
 1000.125
 0.32
 10000000000000000000000000000000000000000.125
 20.59375
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 205
#define DEBUG 0

long long my_int_float()
{
    char InputNum[N], ch;
    int  Num1[N], Num2[N], BiNum1[N], BiNum2[N], Plus[N], Rest[N], Result[50];
    int len = 0, Byte[6], PointPos = 0;
    memset(Byte, 0, sizeof(Byte));
    memset(Num1, 0, sizeof(Num1));
    memset(Num2, 0, sizeof(Num2));
    memset(Result, 0, sizeof(Result));
    memset(BiNum1, 0, sizeof(BiNum1));
    memset(BiNum2, 0, sizeof(BiNum2));

    scanf("%s",InputNum);

    /*Transfer char to int*/
    len = strlen(InputNum);
    int Num1Len = 0, Num2Len = 0;
    for(int i=0; i<len; i++){
        ch = InputNum[i];
        if(ch == '.'){
            PointPos = i;
            continue;
        }else if(ch == '-'){
            Result[1] = 1;
            continue;
        }
        if(PointPos == 0){
            Num1[++Num1Len] = ch-'0';
        }else{
            Num2[++Num2Len] = ch-'0';
        }
    }

    /*Transfer decimal(10) to binary(2) of the integer part*/
    int Highest = 1, BiNum1Len = 0;
    for(BiNum1Len=1; Highest<=Num1Len; BiNum1Len++){
        if(Num1[Highest] == 0){
            if(Highest == Num1Len) break;
            Highest++;
        }
        memset(Rest, 0, sizeof(Rest));
        for(int j=Highest; j<=Num1Len; j++){
            Rest[j] = (Num1[j] & 1)?1:0;
            Num1[j] = (Rest[j-1]*10 + Num1[j])/2;
        }
        BiNum1[BiNum1Len] = Rest[Num1Len];
    }
    BiNum1Len--;

    /*Output binary result of integer part*/
    #if DEBUG
    printf("\n");
    for (int i = 1; i <=100; i++)
    {
            printf("%d",BiNum1[i]);
    }
    printf("\nBiNum1Len:%d\n",BiNum1Len);
    #endif
}
