#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char board[10][10] = {'.'};
char r = 'A';
int end,i,t,m = 0;
void ini()
{
lable:	for(i = 0;i < 9;i++)
	{
		board[m][i] = '.';
	}
	if(m <= 9)
	{
		m++;
		goto lable;
	}	
	
}
void move()
{
	t = rand()%4;
	if (t = 0 && m > 1 && board[m-1][i] == 0)
		{
			m--;
			board[m][i] = r;
		}
		 
	else if (t = 1 && i > 1 && board[m][i-1] == 0)
		{
			i--;
			board[m][i] = r;
		}
	else if(t = 2 && m < 10 && board[m+1][i] == 0)
		{
			m++;
			board[m][i] = r;
		}
	else if(t = 3 && i < 10 && board[m][i+1] == 0)
		{
			i++;
			board[m][i] = r;
		}
		else end = 1;
}

void pr()
{
	if(end == 1)
	{
		m = 0;
lab:	for(i = 0;i < 9;i++)
		{
			putchar(board[m][i]);
		}
		if(m <= 9)
		{
			m++;
			goto lab;
		}		
	}	
}	
int main()
{
	srand((unsigned) time(NULL));
	ini();
	m = i = 0;
	board[m][i] = r;
	r++;
	while(end != 1)
	{
		move();
	}
	pr();
	return 0;

}
