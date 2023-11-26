#include ".\student.h"
 
void Menu(){
	printf("----------------------------------\n");
	printf("| *********学生管理系统********* |\n");
	printf("| 1.ADD stu 2.SEE stu 3.MOD stu  |\n");
	printf("| 4.DEL stu 5.SORT score 6.EXIT  |\n");
	printf("----------------------------------\n");
}
#include ".\student.h"
 
void ADD(CLASS *p) {
	while(1){
		if(p->count == 6){
			printf("班级已满，无法插入\n");
			return;
		}
		STU temp;
LOOP1:
		printf("请输入学生姓名 年龄 性别 学号 成绩\n");
		scanf("%s",temp.name);
		int i;
		if(*(temp.name) == '#') {
			printf("插入结束\n");
			return;
		}else{
			strcpy(p->num[p->count].name,temp.name);
LOOP0:
			scanf("%d %d %d %d",&p->num[p->count].age,&p->num[p->count].sex,
								&p->num[p->count].id,&p->num[p->count].score);
			for(i = 0;i < p->count;i++) {
				if(p->num[p->count].id == p->num[i].id) {
					printf("学号重复，请重新输入\n");
					goto LOOP0;
				}
			}
			p->count++;
			printf("插入成功\n");
			goto LOOP1;
		}
	}
}
 
void SEE(CLASS *p) {
	int i = 0;
	printf("当前班级学生信息如下:\n");
	printf("姓名 	年龄 	性别 	学号 	成绩\n");
	for(i = 0;i < p->count;i++) {
		printf("%s 	%d 	%d 	%d 	%d\n",p->num[i].name,p->num[i].age,
								p->num[i].sex,
								p->num[i].id,p->num[i].score);
	}
	return;
}
 
void MOD(CLASS *p) {
	printf("请输入你想修改的学生学号\n");
	int temp;
	scanf("%d",&temp);
	if(temp > N) {
		printf("学号输入有误,超过班级人数\n");
		return;
	}
	int i,flag = 0;
	for(i = 0;i < p->count;i++) {
		if(temp == p->num[i].id) {
			flag = 1;
			printf("学生当前信息如下：\n");
			printf("姓名 	年龄 	性别 	学号 	成绩\n");
			printf("%s 	%d 	%d 	%d 	%d\n",p->num[i].name,p->num[i].age,
									p->num[i].sex,
									p->num[i].id,p->num[i].score);
			printf("请修改\n");
			scanf("%s %d %d %d %d",p->num[i].name,&p->num[i].age,
								&p->num[i].sex,
								&p->num[i].id,&p->num[i].score);
			return;
		}
	}
	if(flag == 0) {
		printf("学号输入有误，该学生不存在\n");
		return;
	}
}
 
void DEL(CLASS *p) {
	printf("请输入你想删除的学生学号\n");
	int temp;
	scanf("%d",&temp);
	if(temp > N) {
		printf("学号输入有误,超过班级人数\n");
		return;
	}
	int i,flag = 0,j;
	for(i = 0;i < p->count;i++) {
		if(temp == p->num[i].id) {
			flag = 1;
			printf("学生当前信息如下：\n");
			printf("姓名 	年龄 	性别 	学号 	成绩\n");
			printf("%s 	%d 	%d 	%d 	%d\n",p->num[i].name,p->num[i].age,
									p->num[i].sex,
									p->num[i].id,p->num[i].score);
			break;
		}
	}
	if(flag == 0) {
		printf("学号输入有误，该学生不存在\n");
		return;
	}
	printf("确认删除? 1 : 0\n");
	int or;
	scanf("%d",&or);
	if(or == 1) {
		for(j = i;j < p->count;j++) {
			p->num[i] = p->num[i+1];
		}
		p->count--;
		return;
	}else{
		return;
	}
}
 
void SORT(CLASS *p) {
	int i, j;
	STU temp;
	for(i = 0;i < p->count-1;i++) {
		for(j = 0;j < p->count-1-i;j++) {
			if(p->num[j].score > p->num[j+1].score) {
				temp = p->num[j];
				p->num[j] = p->num[j+1];
				p->num[j+1] = temp;
			}
		}
	}
	printf("按成绩排序完成\n");
	return;
}
//#include ".\student.h"//在当前路径寻找头文件
 
int main(int argc, const char *argv[])
{
	CLASS hq51;
	//用结构体申请变量空间,系统分配相应内存
	hq51.count = 0;//初始化学生个数
	int choose = 0;
	while(1) {
		Menu();
		scanf("%d",&choose);
		switch (choose) {
			case 1:
				ADD (&hq51);//传址操作
				break;
			case 2:
				SEE (&hq51);
				break;
			case 3:
				MOD (&hq51);
				break;
			case 4:
				DEL (&hq51);
				break;
			case 5:
				SORT (&hq51);
				break;
			case 6:
				exit(0);
				break;
			default:
				printf("输入有误，程序退出\n");
				exit(-1);
		}
	}
	return 0;
}

