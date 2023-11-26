#ifndef STUDENT_H
#define STUDENT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//也作为学号输入是否正确的判断条件
#define N 6 //方便以后修改班级人数，
 
//定义单个学生的结构体
//此时内存没有给分空间
typedef struct Student{
	char name[16];
	int age;    //年龄
	char sex[16];    //1代表男，0女
	unsigned long long id;     //学号
	int score;    //成绩
}STU;
 
//定义这个班级所有学生的结构体
//此时内存没有给分空间
typedef struct Class{
	STU num[N];    //定义一个班级学生结构体数组
	int count;    //记录学生个数
}CLASS;
 

void Menu();    //打印菜单的函数
 
void ADD(CLASS *p);    //增加学生信息的函数
    
void SEE(CLASS *p);    //查看所有学生信息的函数
 
void MOD(CLASS *p);    //根据学号修改学生信息的函数
 
void DEL(CLASS *p);    //根据学号删除学生信息的函数
 
void SORT(CLASS *p);    //根据成绩将学生降序排序的函数
 
#endif

