#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int i;
	char c = '\\';
	for(i= 1;i< 26;i++)
	{
		printf("[%c\"",c);
		printf("item_%d%c",i,c);
		printf("\"");
		printf("\,");
		printf("%c\"",c);
		printf("1000009");
		printf("%c",c);
		printf("\"");
		printf("\]\,");
	}
}
