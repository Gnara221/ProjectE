#include<stdio.h> 
int main()
{
	int a[]={0,1,2,3,4,5,6,7,8,9};
	int low = 0,high = 9;
	a[low++] = a[high];
	return 0;
}
