// 父进程首先使用系统调用pipe()建立一个管道，然后使用系统调用fork() 创建子进程1
// 子进程1关闭管道读文件
// 子进程1通过文件I/O操作向管道写文件写一句话（向文件中写入字符串）：
//    Child process 1 is sending a message! 
// 然后子进程1调用exit（）结束运行
// 父进程再次使用系统调用fork() 创建子进程2
// 子进程2关闭管道读文件
// 子进程2通过文件I/O操作向管道写文件写一句话（向文件中写入字符串）：
//    Child process 2 is sending a message! 
// 然后子进程2调用exit（）结束运行
// 父进程关闭管道写文件
// 父进程通过文件I/O操作从管道读文件中读出来自于两个子进程的信息，通过printf语句打印输出在屏幕上




#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>


FILE *fp;
char ch;
int glob;
pid_t pid;


void Readfile(char *filename)
{
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("File open error!\n");
        exit(0);
    }
}

int main(void)
{
    int fd[2];
    pipe(fd);
    pid = fork();
    if(pid == 0)
    {
        close(fd[0]);
        char *str = "Child process 1 is sending a message!";
        write(fd[1], str, strlen(str));
        close(fd[1]);
        exit(1);
    }
    if(pid == 1)
    {
        close(fd[0]);
        char *str = "Child process 2 is sending a message!";
        write(fd[1], str, strlen(str));
        exit(0);
    }
    close(fd[1]);
    char buf[100];
    while(read(fd[0], buf, 100))
        printf("%s\n", buf);

}