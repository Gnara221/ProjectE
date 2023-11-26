#include<stdio.h>
#include<stdio.h>
#include<math.h> 
int main()
{
	int i,n,m;
	printf("Enter a number:");
	scanf("%d",&n);
	while((double)i + 2 < sqrt((double)n))
	{
		i += 2;
		m = pow((double)i,2);
		printf("%d\n",(int)m);
	}
	
	return 0;
}
