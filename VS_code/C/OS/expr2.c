/* 生产者消费者问题实现 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define n 100

pthread_mutex_t mutex;
char buffer[n];
sem_t full, empty;
int ful,emp;
FILE *fp;

void ReadFile(char *Filename)
{
    fp = fopen(Filename, "r");
    if (fp == NULL)
    {
        printf("File open error!\n");
        exit(0);
    }
}

void GetData(char *ch)
{
    *ch = fgetc(fp);
}

void PutData(char ch)
{
    fputc(ch, fp);
}

void Producer(void)
{
    char ch;
    GetData(&ch);
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);
    buffer[ful] = ch;
    pthread_mutex_unlock(&mutex);
    sem_post(&full);
    ful = full;
}

void Consumer(void)
{

    char ch;
    sem_wait(&full);
    ful = full;
    pthread_mutex_lock(&mutex);
    ch = buffer[ful];
    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
    PutData(ch);
}

int main(int argc, char const *argv[])
{
    ReadFile("data.txt");
    sem_init(&full, 1, 0);
    sem_init(&empty, 1, n);
    pthread_mutex_init(&mutex, NULL);
    pthread_t p1, p2;
    int ret = 0;
    ret = pthread_create(&p1, NULL, (void*)Producer, NULL);
    if (ret != 0)
    {
        printf("Producer create error!\n");
    }

    ret = pthread_create(&p2, NULL, (void*)Consumer, NULL);
    if (ret != 0)
    {
        printf("Consumer create error!\n");
    }
    
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    printf ("Producer and Consumer have finished!\n");
    return 0;
}
