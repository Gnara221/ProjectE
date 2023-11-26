#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
    int x, y,d;
	int i= 1;
bool Line_breaks()
{
	if (d%7 != 0)
		return 0;
	else 
		return 1;
}

int main()
{
    printf("Enter number of days in month: ");
    scanf("%d", &x);
    printf("Enter starting day of the  week(1=Sun, 7=Sat): ");
    scanf("%d", &y);
    printf("日  一  二  三  四  五  六\n");
    if(y != 7)
	{  
		for (d = 0; d < y-1; d++)
   		printf("    ");
	}
	else 
	{
		for (d = 1; d < y; d++)
   		printf("    ");
   		d = 6;
	}

 	for (i = 1; i <= x; i++) {
		if (Line_breaks() == 1)
		printf("\n");
		if (i < 10)
        {
		    printf(" %d  ", i);
		    d++;
		}
        
        else
		{           
			printf("%d  ", i);
			d++;
		}

    }
 
    return 0;
}
