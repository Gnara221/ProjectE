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
#define DEBUG 1

int my_int_float()
{
    char InputNum[N], ch;
    int  Num1[N], Num2[N], BiNum1[N], BiNum2[N], Plus[N], Rest[N], Result[50];
    int len = 0, Byte[6], PointPos = 0;
    memset(Byte, 0, sizeof(Byte));
    memset(Num1, 0, sizeof(Num1));
    memset(Num2, 0, sizeof(Num2));
    memset(BiNum1, 0, sizeof(BiNum1));
    memset(BiNum2, 0, sizeof(BiNum2));
    printf("1\n");
    scanf("%s",InputNum);
    printf("2\n");
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

    #ifdef DEBUG
    printf("\n");
    for (int i = 1; i <=100; i++)
    {
            printf("%d",BiNum1[i]);
    }
    printf("\nBiNum1Len:%d\n",BiNum1Len);
    #endif

    int Lowest = Num2Len, BiNum2Len = 0;
    for(BiNum2Len=1; BiNum2Len<=264; BiNum2Len++){
        if(Num2[Lowest] == 0){
            if(Lowest == 1) break;
            Lowest--;
        }
        memset(Plus, 0, sizeof(Plus));
        for(int j=Lowest; j>=1; j--){
            Plus[j] = (Num2[j] >= 5)?1:0;
            Num2[j] = Num2[j]*2%10 + Plus[j+1];
        }
        BiNum2[BiNum2Len] = Plus[1];
    }
    BiNum2Len--;

    #ifdef DEBUG
    printf("\n");
    for (int i = 1; i <=100; i++)
    {
            printf("%d",BiNum2[i]);
    }
    #endif
 
    /*get PointNum and TailNum*/
    int PointNum = 0;
    memset(Result, 0, sizeof(Result));
    if(BiNum1Len >= 23){    // x...x(>23).xxx
  PointNum = BiNum1Len-1+127;
  for(int i=BiNum1Len; BiNum1Len-i+1<=23; i--){
            Result[9+BiNum1Len-i+1] = BiNum1[i];
        }
    }else if(BiNum1Len == 0){   // 0.xxx
  while(BiNum2[PointNum] == 0){
            PointNum++;
        }
        PointNum = -1*PointNum + 127;
        for(int i=PointNum+1; i<=23; i++){
            Result[9+i-PointNum] = BiNum2[i];
        }
    }else{        // xxx.xxx
     PointNum = BiNum1Len-1+127;
  for(int i=BiNum1Len; i>=1; i--){
            Result[9+BiNum1Len-i+1] = BiNum1[i];
        }
        for(int i=1; i<=(23-BiNum1Len); i++){
            Result[9+BiNum1Len+i] = BiNum2[i];
        }
    }

    printf("\nPointNum:%d\n",PointNum);
 
    /* 10 to 2*/
 for(int i=9; i>=2; i--){
        Result[i] = (PointNum%2 == 1) ? 1 : 0;
        PointNum /= 2;
    }

    for(int i=1; i<=32; i++){
        printf("%d",Result[i]);
    }

    int value = 0, pow = 1;
    for(int i=32; i>=1; i--){
        value += pow*Result[i];
        pow *= 2;
    }


    /*for(int j=1; j<=4; j++){
        for(int i=0; i<len; i++){
            Byte[j] += ((int)(str[i]-'0'));
            Byte[j] *= 10;
        }
    }
   int time = 2;
    for(int j=4; j>=1; j--){
        while(Result != 0){
            Result += time * (Byte[j]%10);
            Byte[j] /= 10;
            time *= 2;
    }
    }*/
    return value;
}

int main()
{
    printf("\n%d", my_int_float());
    return 0;
}
