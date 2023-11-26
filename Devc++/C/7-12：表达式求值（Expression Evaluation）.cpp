/*
 * 完成人　：马文焘(2021090922026)
 * 完成时间：2021-11-18, Thu, 21:59:22
 * 系统评分：100
 */


#include <stdio.h>
int main()
{
    double a, d;
    char ch;
    printf("Enter an expression: ");
    scanf("%lf", &a);
    while ((ch = getchar()) != '\n') {
        scanf("%lf", &d);
        switch (ch) {
        case '+':
            a = a + d;
            break;
        case '-':
            a = a - d;
            break;
        case '*':
            a = a * d;
            break;
        case '/':
            a = a / d;
            break;
        }
    }
    printf("Value of expression: %f", a);
}
