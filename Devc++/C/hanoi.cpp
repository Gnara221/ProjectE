#include <stdio.h>


void hanoi(int n, char x,char y,char z)
{
	if (n == 1)
		printf("%c --> %c\n",x,z);
	else
	{
		hanoi(n - 1, x, z, y);
		printf("%c --> %c\n",x,z);
		hanoi(n - 1, y, x, z);
	}
}
int main(void)
{
	int m;
	printf("Please enter the floor of hanoi:");
	scanf("%d",&m);
	hanoi(m,'X','Y','Z');
}
