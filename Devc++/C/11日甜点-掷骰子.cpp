#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int num_1,point,w,f,a;
bool outcome;
int roll_dice(void)
{
	num_1 = (rand()% 6 + 1) + (rand()% 6 + 1);
	return num_1;
}
void play_game()
{	
		roll_dice();
		printf("You rolled: %d\n",num_1);
		switch(num_1)
		{
			case 7: case 11:
			outcome = true;		break;
			case 2: case 3: case 12:
			outcome = false;	break;
			default:
			point = num_1;
		printf("Your point is %d\n",point);
		do
		{
			roll_dice();
			printf("You rolled:%d\n",num_1);	
		}while(num_1 != point && num_1 != 7);
		if (num_1 == point && num_1 != 7)
		{
			outcome = true;
			break;	
		}
		else if(num_1 == 7)
		{
			outcome = false;
			break;
		}
		}
	
}
int main()
{
	srand((unsigned)time(NULL));
	play_game();
lable: while (outcome == true)
	{
		w++;
		outcome = 0;
		printf("You win!\n\n");
		printf("Play again? ");
		char ch;
		ch = getchar();
		fflush(stdin);
		if(ch == 'y' || ch == 'Y') 
		{ 
			printf("\n\n");
			play_game();
			continue;
		}
		else printf("Wins:%d Losses:%d",w,f);
		return 0;
	}
	while (outcome == false)
	{
		outcome = 1;
		f++;
		printf("You lose!\n\n");
		printf("Play again? ");
		char ch;
		ch = getchar();
		fflush(stdin);
		if(ch == 'y'|| ch == 'Y')
		{ 
			printf("\n\n");
			play_game();
			continue;
		}
		else printf("Wins:%d Losses:%d",w,f);
		return 0;
	
	}
	do
	{
		goto lable;
	}while(outcome == true);
	return 0;
}

