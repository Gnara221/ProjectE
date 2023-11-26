/*
 * @Author: your name
 * @Date: 2022-01-16 01:05:14
 * @LastEditTime: 2022-01-16 13:26:49
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \vscode\roll dice.c
 */
#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
int goal,sum, num1, num2, rou, win, lose = 0;
char command;
int judge()
{
    if(rou == 1)
    {
        switch (sum)
        {
            case 7:  case 11:
                win++;
                return true;
                break;
            case 2: case 3: case 12 :
                lose++;
                return false;
                break;
            default:
                goal = sum;
                return -1;
                break;
        }
    }
    if(rou > 1)
    {
        if(sum == goal)
        {  
            win++;
            return true;
        }
        if(sum == 7)
        {
            lose++;
            return false;            
        }
    }
}
int roll_dice(void)
{
    num1 = rand() % 6 + 1;
    num2 = rand() % 6 + 1;
    sum = num1 + num2;
    printf("You rolled:%d\n", sum);
    return sum;
}

int play_game(void)
{
    for (rou = 1;;rou++)
    {
        roll_dice();
        Sleep(1 * 1000);
        if (judge() == 1)
        {
            printf("You win!\n");
            break;
        }
        else if(judge()== 0)
        {
            printf("You lose!\n");
            lose--;
            break;
        }
        else
        {
            printf("Your point is %d\n", goal);
            continue;
        }
        Sleep(1 * 1000);
    }
}

int main(void)
{
    srand((unsigned)time(NULL));
    printf("Hello!\n");
    Sleep(2 * 1000);
    printf("Enter 'y' or 'Y' to play game\n");
    while (1)
    {    
        command = getchar();
        fflush(stdin);
        if(command == 'y'||command == 'Y')
        {
            play_game();
            printf("Play agian? Enter 'y'(Yes) to continue or'n'(NO) to exit\n");
        } 
        else if (command != 'y' || command != 'Y')
                if(win == 0 && lose == 0)
                break;
        else if (command != 'y' || command != 'Y')
        {
            if(win != 0 || lose != 0)
            {
                printf("Wins:%d     Losses:%d", win, lose);
                break;   
            }

        }
    }
        
        system("pause");
}
