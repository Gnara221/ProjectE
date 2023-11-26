#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 105

int total;

struct inventory{
	int code, stock;
	char name[25]; 
	struct inventory *next; 
};

struct inventory *components = NULL;

int read_name(char str[]){
	int ch, i=0;
	while(isspace(ch = getchar()));
	while(ch!='\n' && ch!=EOF){
		str[i] = ch;
		i++;
		ch = getchar();
	}
	str[i] = '\0';
	return i;
}
struct inventory *find(int code){
	/*for(int i=1; i<=total; i++)
		if(components[i].code == code) return i;
	return 0;*/
	struct inventory *p;
	for(p = components; p!=NULL && p->code!=code; p=p->next);
	if(p == NULL) return NULL;
	return p;
	
}
void Insert(){
	int insert_code;
	char insert_name[25];
	printf("Enter component code: ");
	scanf("%d",&insert_code);
	if(find(insert_code) != NULL){
		printf("The component is already added.\n");
		return;
	}
	struct inventory *p,*last;
	int first = 0;
	p = malloc(sizeof(struct inventory));
	if(components == NULL){
		first = 1;
	}else{
		for(last= components; last->next!=NULL; last = last->next); // find the last component
		last->next = p;
		}
	p->next = NULL;
	printf("Enter component name: ");
	read_name(p->name);
	printf("Enter component stock: ");
	scanf("%d",&p->stock);
	p->code = insert_code;
	if(first) components = p;
	printf("Operation is done.\n");
	return;
}

void Search(){
	int search_code;
	printf("Enter component code:");
	scanf("%d",&search_code);
	struct inventory *pos = find(search_code);
	if(pos == NULL){
		printf("The component is not in the database.\n");
		return;
	}
	printf("Component name:");
	puts(pos->name);
	printf("Component stock:%d",pos->stock);
	printf("\nOperation is done.\n");
	return;
}

void Update(){
	int update_code,change;
	printf("Enter component number:");
	scanf("%d",&update_code);
	struct inventory *pos = find(update_code);
	if(pos == NULL){
		printf("The component is not in the database.\n");
		return;
	}
	printf("\nEnter quantity change in stock:");
	scanf("%d",&change);
	pos->stock += change;
	printf("Operation is done.\n");
	return;
}

void Print(){
	printf("Component code       Component name       Quantity in stock\n");
	/*for(int i=1; i<=total; i++){
		printf("%-20d %-20s %-20d\n",components[i].code,components[i].name,components[i].stock);
		//printf("%s",components[i].name);
	}*/
	struct inventory *p;
	for(p = components; p!=NULL; p = p->next)
		printf("%-20d %-20s %-20d\n",p->code,p->name,p->stock);
	printf("Operation is done.\n");
	return;
}


int main(void)
{
	char ch;
	while(1){
		printf("Enter operation code: ");
		scanf(" %c",&ch);
		switch (ch){
			case 'i': Insert(); break;
			case 's': Search(); break; 
			case 'u': Update(); break;
			case 'p': Print();  break;
			case 'q': printf("Operation completed."); return 0;
			default: printf("Please input accurate operation command.\n");
		}
		puts("");
	}
	return 0;
 }
