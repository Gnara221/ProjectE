#ifndef STUDENT_H
#define STUDENT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Ҳ��Ϊѧ�������Ƿ���ȷ���ж�����
#define N 6 //�����Ժ��޸İ༶������
 
//���嵥��ѧ���Ľṹ��
//��ʱ�ڴ�û�и��ֿռ�
typedef struct Student{
	char name[16];
	int age;    //����
	char sex[16];    //1�����У�0Ů
	unsigned long long id;     //ѧ��
	int score;    //�ɼ�
}STU;
 
//��������༶����ѧ���Ľṹ��
//��ʱ�ڴ�û�и��ֿռ�
typedef struct Class{
	STU num[N];    //����һ���༶ѧ���ṹ������
	int count;    //��¼ѧ������
}CLASS;
 

void Menu();    //��ӡ�˵��ĺ���
 
void ADD(CLASS *p);    //����ѧ����Ϣ�ĺ���
    
void SEE(CLASS *p);    //�鿴����ѧ����Ϣ�ĺ���
 
void MOD(CLASS *p);    //����ѧ���޸�ѧ����Ϣ�ĺ���
 
void DEL(CLASS *p);    //����ѧ��ɾ��ѧ����Ϣ�ĺ���
 
void SORT(CLASS *p);    //���ݳɼ���ѧ����������ĺ���
 
#endif

