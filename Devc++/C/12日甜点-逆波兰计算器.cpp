# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# define N 10

int stack[N];		//���������С 
int  a,b,i,t,w;
int top = -1;				//����ջ�� 
char ch;
void push_out(); 
void push_in();



void make_empty()		
{
	top = 9;
	do{	
	stack[top] = 0;
	top--;
	}
	 while(top != -1 && top < N );
}							//ջ�ĳ�ʼ��// 



bool is_empty()
{
	if (top == -1)
	{
		return 1;	
	}
	else return 0;
}							//�п�// 



bool is_full()
{
	if (top == N)
	{
		return 1;
	}

	else return 0;
}							//����//

bool is_opnum()
{
	if (ch <= '9' && ch >= '0')
	return 1;
	else return 0;
}							//�в�����//

bool is_opsign()
{
	if(ch == '*' || ch == '+' || ch == '-' || ch == '/' || ch == '=')
	return 1;
	else return 0;
 } 							//�в�����// 
 
 bool result()
 {
 	if (top == 0)
 		return 1;
 	else return 0;
 }

void calculate()
{
	if (is_opsign() == 1)
	{
		switch(ch){
		
		case '*': {
			top--;
		push_out(); 
		if (w != 1){
			i = a * b;
			top++;
			stack[top] = i;	break;
		}
		else	break;
	
		}
		case '+': {
			top--;
		push_out();
		if (w != 1){
			i = a + b;
			top++;
			stack[top] = i;	break;
		}
		else	break;
		}
		case '-': {
			top--;
		push_out(); 
		if (w != 1){
			i = a - b;
			top++;
			stack[top] = i;	break;
		}
		else	break;
		}
		case '/':{
			top--;
		push_out();
		if (w != 1){
			i = a / b;
			top++;
			stack[top] = i;	break;
		}
		else	break;
		} 
		case '=': {
			top--;
		if (result() == 1){	
			printf("Value of expression: ");
			printf("%d\n",stack[top]);
			t = 1;
		}
		else w = 1;
			break;
		}
		default: w = 1;break;
		}
	}
	else w = 1;
}							//����// 

void push_in()
{
	for (top = 0;  top <= N; ++top)
	{
		
		scanf(" %c",&ch);
		if (is_opnum() == 1)
		{
		stack[top] = ch - 48;
		if (is_full() == 1)
		{	
			printf("Expression is too complex\n");
			w = 1;
			break;	
		}
		}
		else calculate();
			if(t != 1 && w != 1)
			continue;
			else break;
	}	
 } 							//��ջ//
 
 void push_out() 
{

 	if (top > 0 && top < N){
	 	b = stack[top];
		stack[top] = 0;
		top--;
		a = stack[top];
 		stack[top] = 0;
 		top--;
		}
	else {
	printf("Not enough operands in expression\n");
		w = 1;
	}
			
		
 }							//��ջ���ж����� //
 int main()
 {
 		printf("Enter an RPN expression: ");
lable: 	if(stack[top] != 0)
		make_empty();
 		while (is_empty() == 1){ 	
		push_in();
		if (t == 1 && w != 1)
		{
			printf("Enter an expression: ");
			t = 0;
			goto lable;
		}

 	}
 		return 0;
 }
