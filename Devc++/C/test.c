#include ".\student.h"
 
void Menu(){
	printf("----------------------------------\n");
	printf("| *********ѧ������ϵͳ********* |\n");
	printf("| 1.ADD stu 2.SEE stu 3.MOD stu  |\n");
	printf("| 4.DEL stu 5.SORT score 6.EXIT  |\n");
	printf("----------------------------------\n");
}
#include ".\student.h"
 
void ADD(CLASS *p) {
	while(1){
		if(p->count == 6){
			printf("�༶�������޷�����\n");
			return;
		}
		STU temp;
LOOP1:
		printf("������ѧ������ ���� �Ա� ѧ�� �ɼ�\n");
		scanf("%s",temp.name);
		int i;
		if(*(temp.name) == '#') {
			printf("�������\n");
			return;
		}else{
			strcpy(p->num[p->count].name,temp.name);
LOOP0:
			scanf("%d %d %d %d",&p->num[p->count].age,&p->num[p->count].sex,
								&p->num[p->count].id,&p->num[p->count].score);
			for(i = 0;i < p->count;i++) {
				if(p->num[p->count].id == p->num[i].id) {
					printf("ѧ���ظ�������������\n");
					goto LOOP0;
				}
			}
			p->count++;
			printf("����ɹ�\n");
			goto LOOP1;
		}
	}
}
 
void SEE(CLASS *p) {
	int i = 0;
	printf("��ǰ�༶ѧ����Ϣ����:\n");
	printf("���� 	���� 	�Ա� 	ѧ�� 	�ɼ�\n");
	for(i = 0;i < p->count;i++) {
		printf("%s 	%d 	%d 	%d 	%d\n",p->num[i].name,p->num[i].age,
								p->num[i].sex,
								p->num[i].id,p->num[i].score);
	}
	return;
}
 
void MOD(CLASS *p) {
	printf("�����������޸ĵ�ѧ��ѧ��\n");
	int temp;
	scanf("%d",&temp);
	if(temp > N) {
		printf("ѧ����������,�����༶����\n");
		return;
	}
	int i,flag = 0;
	for(i = 0;i < p->count;i++) {
		if(temp == p->num[i].id) {
			flag = 1;
			printf("ѧ����ǰ��Ϣ���£�\n");
			printf("���� 	���� 	�Ա� 	ѧ�� 	�ɼ�\n");
			printf("%s 	%d 	%d 	%d 	%d\n",p->num[i].name,p->num[i].age,
									p->num[i].sex,
									p->num[i].id,p->num[i].score);
			printf("���޸�\n");
			scanf("%s %d %d %d %d",p->num[i].name,&p->num[i].age,
								&p->num[i].sex,
								&p->num[i].id,&p->num[i].score);
			return;
		}
	}
	if(flag == 0) {
		printf("ѧ���������󣬸�ѧ��������\n");
		return;
	}
}
 
void DEL(CLASS *p) {
	printf("����������ɾ����ѧ��ѧ��\n");
	int temp;
	scanf("%d",&temp);
	if(temp > N) {
		printf("ѧ����������,�����༶����\n");
		return;
	}
	int i,flag = 0,j;
	for(i = 0;i < p->count;i++) {
		if(temp == p->num[i].id) {
			flag = 1;
			printf("ѧ����ǰ��Ϣ���£�\n");
			printf("���� 	���� 	�Ա� 	ѧ�� 	�ɼ�\n");
			printf("%s 	%d 	%d 	%d 	%d\n",p->num[i].name,p->num[i].age,
									p->num[i].sex,
									p->num[i].id,p->num[i].score);
			break;
		}
	}
	if(flag == 0) {
		printf("ѧ���������󣬸�ѧ��������\n");
		return;
	}
	printf("ȷ��ɾ��? 1 : 0\n");
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
	printf("���ɼ��������\n");
	return;
}
//#include ".\student.h"//�ڵ�ǰ·��Ѱ��ͷ�ļ�
 
int main(int argc, const char *argv[])
{
	CLASS hq51;
	//�ýṹ����������ռ�,ϵͳ������Ӧ�ڴ�
	hq51.count = 0;//��ʼ��ѧ������
	int choose = 0;
	while(1) {
		Menu();
		scanf("%d",&choose);
		switch (choose) {
			case 1:
				ADD (&hq51);//��ַ����
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
				printf("�������󣬳����˳�\n");
				exit(-1);
		}
	}
	return 0;
}

