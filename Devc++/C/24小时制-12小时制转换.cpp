#include <stdio.h>

int main()
{
	int a,b;
	printf("Enter a 24-hour time: ");
	scanf("%d:%d",&a,&b);
	if (a > 12)
		printf("\nEquivalent 12-hour time:%d:%.2d PM",a-12,b);
	else if (a < 12) {		
			if (a > 0 && a < 12)
			printf("Equivalent 12-hour time:%d:%.2d AM",a,b);
			else printf("Equivalent 12-hour time:%d:%.2d AM",a+12,b);
	}
		else
		printf("Equivalent 12-hour time:%d:%.2d PM",a,b);
	return 0;
}
