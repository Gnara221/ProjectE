/*
 * @Author: your name
 * @Date: 2022-01-26 14:39:15
 * @LastEditTime: 2022-01-27 14:41:53
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \vscode\C\project\inventory\inventory.c
 */
#include<stdio.h>
#include"readline.h"
#include<windows.h>

#define NAME_LEN 25
#define MAX_PARTS 100

struct part
{
    int number;
    char name[NAME_LEN + 1];
    int on_hand;
};



int find_part(int number, const struct part inv[], int np);
void insert(struct part inv[], int *np);
void search(const struct part inv[], int np);
void update(struct part inv[], int np);
void print(const struct part inv[], int np);


int main(void)
{
    struct part inventory[MAX_PARTS];
    int num_parts = 0;
    int* np = &num_parts;

    char code;

    for (;;)
    {
        printf("Enter opertion code: ");
        scanf(" %c", &code);
        while (getchar() != '\n')
            ;
        switch(code)
        {
            case 'i':
                insert(inventory,np);
                break;
            case 's':
                search(inventory,*np);
                break;
            case 'u':
                update(inventory,*np);
                break;
            case 'p':
                print(inventory,*np);
                break;
            case 'q':
                return 0;
            default :
                printf("Illegal code\n");
        }
        printf("\n");
        system("pause");
    }
}

int find_part(int number, const struct part inv[], int np)
{
    int i;

    for (i = 0; i < np;i++)
        if(inv[i].number == number)
            return i;
    return -1;

}

void insert(struct part inv[], int *np)
{
    int part_number;

    if(*np == MAX_PARTS)
    {
        printf("Database is full; can't add more parts.\n");
        return;
    }
    printf("Enter part number: ");
    scanf("%d", part_number);

    if (find_part(part_number,inv,*np) >= 0)
    {
        printf("Part already exists.\n");
        return;
    }

    inv[*np].number = part_number;
    printf("Enter part name ");
    read_line(inv[*np].name, NAME_LEN);
    printf("Enter quantity on hand ");
    scanf("%d", &inv[*np].on_hand);
    (*np)++;
}

void search(const struct part inv[], int np)
{
    int i, number;
    printf("Enter part number: ");
    scanf("%d", number);
    i = find_part(number,inv,np);
    if (i >= 0)
    {
        printf("Part name: %s\n", inv[i].name);
        printf("Quantity on hands: %d\n", inv[i].on_hand);
    }
    else
        printf("Part not found.\n");
}

void update(struct part inv[], int np)
{
    int i, number, change;

    printf("Enter part number: ");
    scanf("%d", &number);
    i = find_part(number,inv,np);
    if (i >= 0)
    {
        printf("Enter change in quantity on hand: ");
        scanf("%d", &change);
        inv[i].on_hand += change;
    }
    else
        printf("Part not found.\n");
}
void print(const struct part inv[], int np)
{
    int i;
    printf("Part Number     Part Name           "
            "Quantity on Hand\n");
    for (i = 0; i < np;i++)
        printf("%7d     %-25s%lld\n", inv[i].number, inv[i].name, inv[i].on_hand);
}