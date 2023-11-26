#include <stdio.h>
int m,n,g,i,h,p=0;
int main()
{
	scanf("%d",&n);
	scanf("%d",&m);
	int goods[n][m] = {0};
lable:	for(i = 0;i < n;i++){
		scanf("%d",&g);
		goods[h][i] = g; 
	}
	if(h < m){
		h += 1;
		goto lable;
	}
	h = i = 0;
lab:	int min = goods[h][i];
	for(h = 0;h < m;h++){
		if(min > goods[h][i] && goods[h][i] != -1){
			min = goods[h][i];
		}
	}
	p += min;
	if(i < n){
	i += 1;
	goto lab;
	}
	printf("%d",p);
	return 0;
	

}
