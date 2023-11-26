#include<stdio.h>
int main(){
    int a,b;
    printf("Enter a 24-hour time:" );
    scanf("%d:%d",&a,&b);
    if (a>12){
        printf("Equivalent 12-hour time:%d:%.2dPM",a-12,b);
    }
    else if (a=12){
        printf("Equivalent 12-hour time:12:%.2dPM",b);
    }
    else if (a<12 && a>0){
        printf("Equivalent 12-hour time:%d:%.2dAM",a,b);
    }
    else if (a=0){
        printf("Equivalent 12-hour time:12:%.2dAM",b);
    }
            return 0;
}

