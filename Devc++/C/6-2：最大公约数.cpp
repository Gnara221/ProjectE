#include <stdio.h>

int m,n,i;
int main()
{
	printf("Enter two integers:");
	scanf("%d %d",&m,&n);
	while(m >= n && n != 0)
	{
			i = m%n;
			m = n;
			n = i;

	}
	if(n == 0)
	printf("\nGreatest common divisor:%d",m);

while(n >= m && m != 0)
	{
			i = n%m;
			n = m;
			m = i;

	}
	if(m == 0)
	printf("\nGreatest common divisor:%d",n);
	
	return 0;
}
