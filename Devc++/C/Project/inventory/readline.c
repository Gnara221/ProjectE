/*
 * @Author: your name
 * @Date: 2022-01-26 14:42:21
 * @LastEditTime: 2022-01-26 14:49:39
 * @LastEditors: your name
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \vscode\C\project\inventory\readline.c
 */
#include <ctype.h>
#include <stdio.h>
#include "readline.h"

int read_line(char str[],int n)
{
    int ch, i = 0;

    while (isspace(ch = getchar()))
        ;
    while (ch != '\n' && ch != EOF)
    {
        if (i<n)
            str[i++] = ch;
        ch = getchar();

    }
    str[i] = '\0';
    return i;
}