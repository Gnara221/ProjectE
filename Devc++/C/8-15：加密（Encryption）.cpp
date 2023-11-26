/*
 * 完成人　：马文焘(2021090922026)
 * 完成时间：2021-11-20, Sat, 23:30:26
 * 系统评分：100
 */


#include <stdio.h>
#include <stdlib.h>
 
int main()
{
    int x, y, z;
    char ch[100];
    z = 0;
    for (y = 0; y < 100; y++)
        ch[y] = 0;
    printf("Enter message to be encrypted:\n");
    for (;; z++) {
        ch[z] = getchar();
        if (ch[z] == '\n')
            break;
    }
    printf("Enter shift amount (1-25):\n");
    scanf("%d", &x);
    y = 0;
    printf("Encrypted message: ");
    while (y < z) {
        if (ch[y] >= 'a' && ch[y] <= 'z') {
            ch[y] = ((ch[y] - 'a') + x) % 26 + 'a';
 
            if (ch[y] > 'z')
 
                ch[y] = ((ch[y] - 'A') + x) % 26 + 'A';
 
        }
 
        else if (ch[y] >= 'A' && ch[y] <= 'Z') {
            ch[y] += x;
            if (ch[y] > 'Z')
                ch[y] -= 26;
        }
 
        printf("%c", ch[y]);
        y++;
    }
    return 0;
}
