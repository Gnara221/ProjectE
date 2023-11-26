#include <stdio.h>
int a;
int main()
{
	printf("Enter numberical grade:");
	scanf("%d",&a);
	if (a >= 0 && a <= 100)
	{
		a = a/10;
		switch (a)
		{
			case 0: 
			case 1: 
			case 2: 
			case 3:
			case 4:
			case 5:
				printf("\nLetter grade:F\n");
				break;
			case 6:
				printf("Letter grade:D\n");
				break;
			case 7:
				printf("Letter grade:C\n");
				break;
			case 8:
				printf("Letter grade:B\n");
				break;
			case 9:
			case 10:
				printf("Letter grade:A\n");
				break;
		}
	}
	else printf("Error,grade must be between 0 and 100\n");
}
