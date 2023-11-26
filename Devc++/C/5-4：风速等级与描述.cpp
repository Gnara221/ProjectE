#include <stdio.h>

int a;

int main()
{
	printf("Enter a wind speed:");
	scanf("%d",&a);
	if (a < 1)
	printf("Calm");
	
	if(a > 0 && a <4)
	printf("Light air");
	
	if(a > 3 && a <28)
	printf("Breeze");
	
	if(a > 27 && a < 48)
	printf("Gale");
	
	if(a > 47 && a < 64)
	printf("Storm");
	
	else printf("Hurricane");
	return 0;
	
	}
