/*
 * 完成人　：马文焘(2021090922026)
 * 完成时间：2021-11-20, Sat, 23:29:17
 * 系统评分：100
 */


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
   int j = 1, k = 1, num = 26, mid = 0,b;
    bool a[12][12] = { false };
    for (b = 0; b< 12; b++) {
        a[0][b] = true;
        a[11][b] = true;
        a[b][0] = true;
        a[b][11] = true;
    }
     
    char i[12][12];
    for (j = 0; j < 12; j++) {
        for (k = 0; k < 12; k++) {
            i[j][k] = '.';
        }
    }
    j = 1;
    k = 1;
    i[1][1] = 'A';
    a[1][1] = true;

    srand((unsigned)time(NULL));
    while (num > 1) {
        mid = rand() % 4;
		if (a[j - 1][k] == true && a[j + 1][k] == true && a[j][k - 1] == true && a[j][k + 1] == true)
            break;
        else {
            
            switch (mid) {
            case 0: {
                j--;
                if (a[j][k] == false) {
                    i[j][k] = i[j + 1][k] + 1;
                    a[j][k] = true;
                    num--;
                } else {
                    j++;
                    continue;
                }
                break;
            }
            case 1: {
                j++;
                if (a[j][k] == false) {
                    i[j][k] = i[j - 1][k] + 1;
                    a[j][k] = true;
                    num--;
                } else {
                    j--;
                    continue;
                }
                break;
            }
            case 2: {
                k--;
                if (a[j][k] == false) {
                    i[j][k] = i[j][k + 1] + 1;
                    a[j][k] = true;
                    num--;
                } else {
                    k++;
                    continue;
                }
                break;
            }
            case 3: {
                k++;
                if (a[j][k] == false) {
                    i[j][k] = i[j][k - 1] + 1;
                    a[j][k] = true;
                    num--;
                } else {
                    k--;
                    continue;
                }
                break;
            }
            }
        }
    }
    for (j = 1; j < 11; j++) {
        for (k = 1; k < 11; k++) {
            printf("%-2c", i[j][k]);
            if (k == 10)
                printf("\n");
        }
    }
}
