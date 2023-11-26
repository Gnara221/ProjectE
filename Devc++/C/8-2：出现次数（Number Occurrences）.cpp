#include <stdio.h>

int Digit[10] = {0};
int main()
{
	int digit,i;
	long n;
	
	printf("Enter a number: ");
	scanf("%ld",&n);
	if(n == 0);
	goto lable;
	
	
	while (n > 0)
	{	
lable:		digit = n%10;	
		Digit[digit] += 1;
		n /= 10;
	}
	
	if (n <= 0)
	printf("Digit:      0 1 2 3 4 5 6 7 8 9\n");
	printf("Occureences:");
	for(i = 0;i < 10;i++)
	printf("%d ",Digit[i]);
		
	return 0;
}
