// ѧ���ɼ�����ϵͳ.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

//ѧ��
typedef struct _Student
{
	unsigned int ID; ///ѧ��
	char name[20];		  /// ����
	char sex[4];		  ///�Ա�
	unsigned int age;	 ///����
	unsigned int score;  ///�ɼ�

} Student;

//����	
typedef struct _Node
{
	Student stu;		///ѧ����Ϣ
	struct _Node *next; ///��һ���ڵ�ָ��
} Node;

//ͷ���
Node *pHead = NULL;

//�ļ�
FILE *fp;
char filename[127];

//��ӭ����
int WelcomeInfo();

//����ͷ���
void CreatListOfHead();

//¼��ѧ����Ϣ
void InputStudentInfo();

//��ӡѧ����Ϣ
void PrintStudentInfo();

//ͳ��ѧ������
void CountStudent();

//����ѧ����Ϣ
void SearchStudent();

//����ѧ����Ϣ
void AlterStudentInfo();

//ɾ��ѧ����Ϣ
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
	printf("    |          ��ӭʹ�óɼ�����ϵͳ           |\n");
	printf("    |-----------------------------------------|\n");
	printf("    |             ��ѡ�����б�              |\n");
	printf("    |-----------------------------------------|\n");
	printf("    |             1��¼��ѧ����Ϣ             |\n");
	printf("    |             2����ӡѧ����Ϣ             |\n");
//	printf("    *             3������ѧ����Ϣ             *\n");
//	printf("    |             4����ȡѧ����Ϣ             *\n");
	printf("    |             3��ͳ��ѧ������             |\n");
	printf("    |             4������ѧ����Ϣ             |\n");
	printf("    |             5���޸�ѧ����Ϣ             |\n");
	printf("    |             6��ɾ��ѧ����Ϣ             |\n");
	printf("    |             0���˳�ϵͳ                 |\n");
	printf("    |-----------------------------------------|\n");
	return 0;
}

//����ͷ���
void CreatListOfHead()
{
	Node *pHead = (Node *)malloc(sizeof(Node));
	pHead->next = NULL;
}

// ¼��ѧ����Ϣ
void InputStudentInfo()
{
	//�����ڴ棬���ٽڵ�
	Node *p = (Node *)malloc(sizeof(Node));
	p->next = NULL;

	system("cls");
	printf("    |-----------------------------------------|\n");
	printf("    |             ѧ����Ϣ¼�����            |\n");
	printf("    |-----------------------------------------|\n");
	printf("\n");
	printf("������ѧ��������");
	scanf("%s", p->stu.name);
	printf("������ѧ��ѧ�ţ�");
	scanf("%d", &p->stu.ID);
	printf("������ѧ���Ա�");
	scanf("%s", p->stu.sex);
	printf("������ѧ�����䣺");
	scanf("%d", &p->stu.age);
	printf("������ѧ���ɼ���");
	scanf("%d", &p->stu.score);

	//���ڵ���ӵ�������
	if (pHead == NULL)
	{
		pHead = p;
	}
	else
	{
		//ͷ�巨
		p->next = pHead;
		pHead = p;
	}
	system("cls");
	printf("    |-----------------------------------------|\n");
	printf("    |            ѧ����Ϣ¼��ɹ���           |\n");
	printf("    |-----------------------------------------|\n");
	system("pause");
	system("cls");
}

//��ӡѧ����Ϣ
void PrintStudentInfo()
{
	system("cls");
	printf("\n\n");
	printf("---------------------------------------------------------------------------------\n");
	printf("|\t\t\t��ӭʹ��ѧ������ϵͳ\t\t\t\t\t|\n");
	printf("---------------------------------------------------------------------------------\n");
	printf("|\tѧ��\t|\t����\t|\t�Ա�\t|\t����\t|\t�ɼ�\t|\n");
	printf("---------------------------------------------------------------------------------\n");

	//��������
	Node *p = pHead;
	while (p != NULL)
	{
		printf("|\t%d\t|\t%s\t|\t%s\t|\t%d\t|\t%d\t|\n", p->stu.ID, p->stu.name, p->stu.sex, p->stu.age, p->stu.score);
		printf("---------------------------------------------------------------------------------\n");

		p = p->next;
	}
	if (pHead == NULL)
	{
		printf("|\t\t\t\tû��ѧ����Ϣ\t\t\t\t\t|\n");
		printf("---------------------------------------------------------------------------------\n");
	}

	printf("\n\n");
	system("pause");
}


//ͳ��ѧ������
void CountStudent()
{
	system("cls");
	printf("\n\n");
	printf("---------------------------------------------------------------------------------\n");
	printf("|\t\t\t��ӭʹ��ѧ������ϵͳ\t\t\t\t\t|\n");
	printf("---------------------------------------------------------------------------------\n");

	//��������
	Node *p = pHead;
	unsigned int count = 0;
	while (p != NULL)
	{
		count++;
		p = p->next;
	}
	printf("|\t\t\t\tѧ��������%d\t\t\t\t\t|\n", count);
	printf("---------------------------------------------------------------------------------\n");
	printf("\n\n");
	system("pause");
}

//����ѧ����Ϣ
void SearchStudent()
{
	while (1)
	{
		system("cls");
		printf("\n\n");
		printf("---------------------------------------------------------------------------------\n");
		printf("|\t\t\t����ѧ����Ϣ����\t\t\t\t\t|\n");
		printf("---------------------------------------------------------------------------------\n");
		printf("\n\n");
		printf("��ѡ���ѯ��ʽ����1����ѧ��   |  ��2�������� | ��-1���˳�\n��ѡ��");
		int k;
		Node *p = pHead;
		scanf("%d", &k);
		switch (k)
		{
		case 1:
			printf("������ѧ��ѧ�ţ�");
			int ID;
			scanf("%d", &ID);
			while (p->next != NULL)
			{
				if (p->stu.ID == ID)
				{
					printf("---------------------------------------------------------------------------------\n");
					printf("|\tѧ��\t|\t����\t|\t�Ա�\t|\t����\t|\t�ɼ�\t|\n");
					printf("---------------------------------------------------------------------------------\n");
					printf("|\t%d\t|\t%s\t|\t%s\t|\t%d\t|\t%d\t|\n", p->stu.ID, p->stu.name, p->stu.sex, p->stu.age, p->stu.score);
					printf("---------------------------------------------------------------------------------\n");
					p = p->next;
				}
				else
				{
					system("pause");
					printf("\t\t\t\tδ��ѯ��������Ϣ��\t\t\t\t\t");
					printf("---------------------------------------------------------------------------------\n");
					return;
				}
			}
			system("pause");
			return;
		case 2:
			printf("������ѧ��������");
			char name[20];
			scanf("%s", name);
			while (p && (strcmp(p->stu.name, name) != 0 )){p = p->next;}
			
			if (p)
			{
				printf("---------------------------------------------------------------------------------\n");
				printf("|\tѧ��\t|\t����\t|\t�Ա�\t|\t����\t|\t�ɼ�\t|\n");
				printf("---------------------------------------------------------------------------------\n");
				printf("|\t%d\t|\t%s\t|\t%s\t|\t%d\t|\t%d\t|\n", p->stu.ID, p->stu.name, p->stu.sex, p->stu.age, p->stu.score);
				printf("---------------------------------------------------------------------------------\n");
			}
			else
			{
				printf("---------------------------------------------------------------------------------\n");
				printf("\t\t\t\tδ��ѯ��������Ϣ��\t\t\t\t\t");
				printf("---------------------------------------------------------------------------------\n");
			}
			
			system("pause");
			return;
		case -1:
			return;
		default:
			printf("������ѡ��");
			system("pause");
			break;
		}
	}
}

//����ѧ����Ϣ
void AlterStudentInfo()
{
	system("cls");
	printf("    *******************************************\n");
	printf("    *             ѧ����Ϣ���Ľ���            *\n");
	printf("    *******************************************\n");
	printf("\n");
	printf("������ѧ��ѧ�ţ�");
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
		printf("|\tѧ��\t|\t����\t|\t�Ա�\t|\t����\t|\t�ɼ�\t|\n");
		printf("---------------------------------------------------------------------------------\n");
		printf("|\t%d\t|\t%s\t|\t%s\t|\t%d\t|\t%d\t|\n", p->stu.ID, p->stu.name, p->stu.sex, p->stu.age, p->stu.score);
		printf("---------------------------------------------------------------------------------\n");
		printf("��������ĺ��ѧ��ѧ�ţ�");
		scanf("%d", &p->stu.ID);
		printf("��������ĺ��ѧ��������");
		scanf("%s", p->stu.name);
		printf("��������ĺ��ѧ���Ա�");
		scanf("%s", p->stu.sex);
		printf("��������ĺ��ѧ�����䣺");
		scanf("%d", &p->stu.age);
		printf("��������ĺ��ѧ���ɼ���");
		scanf("%d", &p->stu.score);
		system("cls");
		printf("    *******************************************\n");
		printf("    *            ѧ����Ϣ���ĳɹ���           *\n");
		printf("    *******************************************\n");
		system("pause");
		system("cls");
		return;
	}
	else
	{
		system("cls");
		printf("    *******************************************\n");
		printf("    *               �Ҳ�����ѧ����             *\n");
		printf("    *******************************************\n");
		system("pause");
		system("cls");
		return;
	}
}

//ɾ��ѧ����Ϣ
void DeleteStudent()
{
	system("cls");
	printf("    *******************************************\n");
	printf("    *             ѧ����Ϣɾ������            *\n");
	printf("    *******************************************\n");
	printf("\n");
	printf("������Ҫɾ����ѧ��ѧ�ţ�");
	int ID;
	scanf("%d", &ID);
	Node *p = pHead;
	while (1)
	{
		if (p->next && (p->next->stu.ID == ID))
		{
			Node *useless = p->next;
			p->next = p->next->next;
			printf("������Ϣ�ѱ�ɾ����\n");
			printf("---------------------------------------------------------------------------------\n");
			printf("|\tѧ��\t|\t����\t|\t�Ա�\t|\t����\t|\t�ɼ�\t|\n");
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
				printf("    *            ѧ����Ϣɾ��ʧ�ܣ�            *\n");
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
		// ������
		system("cls");

		WelcomeInfo();
		printf("���������֣�");
		char ch = _getch();
		switch (ch)
		{
		case '1':
			//¼��ѧ����Ϣ
			InputStudentInfo();
			break;
		case '2':
			//��ӡѧ����Ϣ
			PrintStudentInfo();
			break;
/*		case '3':
			//����ѧ����Ϣ
			SaveData();
			break;
		case '4':
			//��ȡѧ����Ϣ
			LoadData();
			break;
*/
		case '3':
			//ͳ��ѧ������
			CountStudent();
			break;
		case '4':
			//����ѧ����Ϣ
			SearchStudent();
			break;
		case '5':
			//����ѧ����Ϣ
			AlterStudentInfo();
			break;
		case '6':
			//ɾ��ѧ����Ϣ
			DeleteStudent();
			break;
		case '0':
			//�˳�ϵͳ
			exit(0);
			break;
		default:
			break;
		}
	}
}
