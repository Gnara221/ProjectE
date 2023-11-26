// 学生成绩管理系统.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

//学生
typedef struct _Student
{
	unsigned int ID; ///学号
	char name[20];		  /// 姓名
	char sex[4];		  ///性别
	unsigned int age;	 ///年龄
	unsigned int score;  ///成绩

} Student;

//链表	
typedef struct _Node
{
	Student stu;		///学生信息
	struct _Node *next; ///下一个节点指针
} Node;

//头结点
Node *pHead = NULL;

//文件
FILE *fp;
char filename[127];

//欢迎界面
int WelcomeInfo();

//创建头结点
void CreatListOfHead();

//录入学生信息
void InputStudentInfo();

//打印学生信息
void PrintStudentInfo();

//统计学生人数
void CountStudent();

//查找学生信息
void SearchStudent();

//更改学生信息
void AlterStudentInfo();

//删除学生信息
void DeleteStudent();

int Loop();

int main()
{
	Loop();

	return 0;
}

int WelcomeInfo()
{
	printf("\n\n");
	printf("    |-----------------------------------------|\n");
	printf("    |          欢迎使用成绩管理系统           |\n");
	printf("    |-----------------------------------------|\n");
	printf("    |             请选择功能列表              |\n");
	printf("    |-----------------------------------------|\n");
	printf("    |             1：录入学生信息             |\n");
	printf("    |             2：打印学生信息             |\n");
//	printf("    *             3：保存学生信息             *\n");
//	printf("    |             4：读取学生信息             *\n");
	printf("    |             3：统计学生人数             |\n");
	printf("    |             4：查找学生信息             |\n");
	printf("    |             5：修改学生信息             |\n");
	printf("    |             6：删除学生信息             |\n");
	printf("    |             0：退出系统                 |\n");
	printf("    |-----------------------------------------|\n");
	return 0;
}

//创建头结点
void CreatListOfHead()
{
	Node *pHead = (Node *)malloc(sizeof(Node));
	pHead->next = NULL;
}

// 录入学生信息
void InputStudentInfo()
{
	//申请内存，开辟节点
	Node *p = (Node *)malloc(sizeof(Node));
	p->next = NULL;

	system("cls");
	printf("    |-----------------------------------------|\n");
	printf("    |             学生信息录入界面            |\n");
	printf("    |-----------------------------------------|\n");
	printf("\n");
	printf("请输入学生姓名：");
	scanf("%s", p->stu.name);
	printf("请输入学生学号：");
	scanf("%d", &p->stu.ID);
	printf("请输入学生性别：");
	scanf("%s", p->stu.sex);
	printf("请输入学生年龄：");
	scanf("%d", &p->stu.age);
	printf("请输入学生成绩：");
	scanf("%d", &p->stu.score);

	//将节点添加到链表中
	if (pHead == NULL)
	{
		pHead = p;
	}
	else
	{
		//头插法
		p->next = pHead;
		pHead = p;
	}
	system("cls");
	printf("    |-----------------------------------------|\n");
	printf("    |            学生信息录入成功！           |\n");
	printf("    |-----------------------------------------|\n");
	system("pause");
	system("cls");
}

//打印学生信息
void PrintStudentInfo()
{
	system("cls");
	printf("\n\n");
	printf("---------------------------------------------------------------------------------\n");
	printf("|\t\t\t欢迎使用学生管理系统\t\t\t\t\t|\n");
	printf("---------------------------------------------------------------------------------\n");
	printf("|\t学号\t|\t姓名\t|\t性别\t|\t年龄\t|\t成绩\t|\n");
	printf("---------------------------------------------------------------------------------\n");

	//遍历链表
	Node *p = pHead;
	while (p != NULL)
	{
		printf("|\t%d\t|\t%s\t|\t%s\t|\t%d\t|\t%d\t|\n", p->stu.ID, p->stu.name, p->stu.sex, p->stu.age, p->stu.score);
		printf("---------------------------------------------------------------------------------\n");

		p = p->next;
	}
	if (pHead == NULL)
	{
		printf("|\t\t\t\t没有学生信息\t\t\t\t\t|\n");
		printf("---------------------------------------------------------------------------------\n");
	}

	printf("\n\n");
	system("pause");
}


//统计学生人数
void CountStudent()
{
	system("cls");
	printf("\n\n");
	printf("---------------------------------------------------------------------------------\n");
	printf("|\t\t\t欢迎使用学生管理系统\t\t\t\t\t|\n");
	printf("---------------------------------------------------------------------------------\n");

	//遍历链表
	Node *p = pHead;
	unsigned int count = 0;
	while (p != NULL)
	{
		count++;
		p = p->next;
	}
	printf("|\t\t\t\t学生人数：%d\t\t\t\t\t|\n", count);
	printf("---------------------------------------------------------------------------------\n");
	printf("\n\n");
	system("pause");
}

//查找学生信息
void SearchStudent()
{
	while (1)
	{
		system("cls");
		printf("\n\n");
		printf("---------------------------------------------------------------------------------\n");
		printf("|\t\t\t搜索学生信息界面\t\t\t\t\t|\n");
		printf("---------------------------------------------------------------------------------\n");
		printf("\n\n");
		printf("请选择查询方式：【1】按学号   |  【2】按姓名 | 【-1】退出\n请选择：");
		int k;
		Node *p = pHead;
		scanf("%d", &k);
		switch (k)
		{
		case 1:
			printf("请输入学生学号：");
			int ID;
			scanf("%d", &ID);
			while (p->next != NULL)
			{
				if (p->stu.ID == ID)
				{
					printf("---------------------------------------------------------------------------------\n");
					printf("|\t学号\t|\t姓名\t|\t性别\t|\t年龄\t|\t成绩\t|\n");
					printf("---------------------------------------------------------------------------------\n");
					printf("|\t%d\t|\t%s\t|\t%s\t|\t%d\t|\t%d\t|\n", p->stu.ID, p->stu.name, p->stu.sex, p->stu.age, p->stu.score);
					printf("---------------------------------------------------------------------------------\n");
					p = p->next;
				}
				else
				{
					system("pause");
					printf("\t\t\t\t未查询到该生信息！\t\t\t\t\t");
					printf("---------------------------------------------------------------------------------\n");
					return;
				}
			}
			system("pause");
			return;
		case 2:
			printf("请输入学生姓名：");
			char name[20];
			scanf("%s", name);
			while (p && (strcmp(p->stu.name, name) != 0 )){p = p->next;}
			
			if (p)
			{
				printf("---------------------------------------------------------------------------------\n");
				printf("|\t学号\t|\t姓名\t|\t性别\t|\t年龄\t|\t成绩\t|\n");
				printf("---------------------------------------------------------------------------------\n");
				printf("|\t%d\t|\t%s\t|\t%s\t|\t%d\t|\t%d\t|\n", p->stu.ID, p->stu.name, p->stu.sex, p->stu.age, p->stu.score);
				printf("---------------------------------------------------------------------------------\n");
			}
			else
			{
				printf("---------------------------------------------------------------------------------\n");
				printf("\t\t\t\t未查询到该生信息！\t\t\t\t\t");
				printf("---------------------------------------------------------------------------------\n");
			}
			
			system("pause");
			return;
		case -1:
			return;
		default:
			printf("请重新选择！");
			system("pause");
			break;
		}
	}
}

//更改学生信息
void AlterStudentInfo()
{
	system("cls");
	printf("    *******************************************\n");
	printf("    *             学生信息更改界面            *\n");
	printf("    *******************************************\n");
	printf("\n");
	printf("请输入学生学号：");
	int ID;
	scanf("%d", &ID);
	Node *p = pHead;
	while (p && (p->stu.ID != ID))
	{
		p = p->next;
	}
	if (p)
	{
		printf("---------------------------------------------------------------------------------\n");
		printf("|\t学号\t|\t姓名\t|\t性别\t|\t年龄\t|\t成绩\t|\n");
		printf("---------------------------------------------------------------------------------\n");
		printf("|\t%d\t|\t%s\t|\t%s\t|\t%d\t|\t%d\t|\n", p->stu.ID, p->stu.name, p->stu.sex, p->stu.age, p->stu.score);
		printf("---------------------------------------------------------------------------------\n");
		printf("请输入更改后的学生学号：");
		scanf("%d", &p->stu.ID);
		printf("请输入更改后的学生姓名：");
		scanf("%s", p->stu.name);
		printf("请输入更改后的学生性别：");
		scanf("%s", p->stu.sex);
		printf("请输入更改后的学生年龄：");
		scanf("%d", &p->stu.age);
		printf("请输入更改后的学生成绩：");
		scanf("%d", &p->stu.score);
		system("cls");
		printf("    *******************************************\n");
		printf("    *            学生信息更改成功！           *\n");
		printf("    *******************************************\n");
		system("pause");
		system("cls");
		return;
	}
	else
	{
		system("cls");
		printf("    *******************************************\n");
		printf("    *               找不到该学生！             *\n");
		printf("    *******************************************\n");
		system("pause");
		system("cls");
		return;
	}
}

//删除学生信息
void DeleteStudent()
{
	system("cls");
	printf("    *******************************************\n");
	printf("    *             学生信息删除界面            *\n");
	printf("    *******************************************\n");
	printf("\n");
	printf("请输入要删除的学生学号：");
	int ID;
	scanf("%d", &ID);
	Node *p = pHead;
	while (1)
	{
		if (p->next && (p->next->stu.ID == ID))
		{
			Node *useless = p->next;
			p->next = p->next->next;
			printf("以下信息已被删除：\n");
			printf("---------------------------------------------------------------------------------\n");
			printf("|\t学号\t|\t姓名\t|\t性别\t|\t年龄\t|\t成绩\t|\n");
			printf("---------------------------------------------------------------------------------\n");
			printf("|\t%d\t|\t%s\t|\t%s\t|\t%d\t|\t%d\t|\n", useless->stu.ID, useless->stu.name, useless->stu.sex, useless->stu.age, useless->stu.score);
			printf("---------------------------------------------------------------------------------\n");
			printf("\n\n");
			system("pause");
			free(useless);
			return;
		}
		else
		{
			if (p->next != NULL)
			{
				p = p->next;
			}
			else
			{
				system("cls");
				printf("    *******************************************\n");
				printf("    *            学生信息删除失败！            *\n");
				printf("    *******************************************\n");
				printf("\n");
				system("pause");
				return;
			}
		}
	}
}


int Loop()
{
	while (1)
	{
		// 清除输出
		system("cls");

		WelcomeInfo();
		printf("请输入数字：");
		char ch = _getch();
		switch (ch)
		{
		case '1':
			//录入学生信息
			InputStudentInfo();
			break;
		case '2':
			//打印学生信息
			PrintStudentInfo();
			break;
/*		case '3':
			//保存学生信息
			SaveData();
			break;
		case '4':
			//读取学生信息
			LoadData();
			break;
*/
		case '3':
			//统计学生人数
			CountStudent();
			break;
		case '4':
			//查找学生信息
			SearchStudent();
			break;
		case '5':
			//更改学生信息
			AlterStudentInfo();
			break;
		case '6':
			//删除学生信息
			DeleteStudent();
			break;
		case '0':
			//退出系统
			exit(0);
			break;
		default:
			break;
		}
	}
}
