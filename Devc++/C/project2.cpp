#include <stdio.h>
#include "dev.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(void) {
	
	int DATA[4];
	int a[2],b[2] = {0,0};
	DATA = request(a,b);
	for(int i = 0 ; i < 2 ;i++)
		printf("%d",a[i]);
	printf("\d")
	for(int i = 0 ; i < 2 ;i++)
		printf("%d",b[i]);
	printf("\d")
	for(int i = 0 ; i < 4 ;i++)
		printf("%d",DATA[i]);
	printf("\d")
	return 0;
}
