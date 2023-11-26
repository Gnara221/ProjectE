#include <stdio.h>
int main()
{
	int mm,dd,yyyy;
	printf("Enter a date(mm/dd/yyyy):\n");
	scanf("%d/%d/%d",&mm,&dd,&yyyy);
	printf("You entered the date %4.4d%2.2d%2.2d",yyyy,mm,dd);
	return 0;
 } 
