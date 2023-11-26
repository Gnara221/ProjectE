#include<stdio.h>

int main(){
	int Num1,Num2,OpNum = 0;
	while(1){
		printf("Enter 1 to calculate the addition or Enter others to exit: ");
		scanf("%d",&OpNum);
		if (OpNum != 1)
			break;
		printf("Please enter the First Number(Must be an integer): ");
		scanf("%d",&Num1);
		printf("Please enter the Second Number(Must be an integer): ");
		scanf("%d",&Num2);
		printf("The Sum is: ");
		Num1 += Num2;
		printf("%d\n",Num1);
	}	
	return 0;
}
