/*
 * @description: 
 * @param: 
 * @return: 
 */
/*
 * @description: 
 * @param: 
 * @return: 
 */



#include <stdlib.h>
#include <stdio.h> 
#include <string.h> 
#include <errno.h> 
#include <malloc.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <pthread.h>
#include <semaphore.h>
 
#define N 5
 
sem_t chopsticks[N];//设置5种信号量，有5种不同类型的资源，每一种有1个,这样便于理解，因为每个哲学家需要的资源不同
 
pthread_mutex_t mutex;//定义互斥锁
 
int philosophers[N] = {0, 1, 2, 3, 4};//代表5个哲学家的编号
 
//定义随机延时函数
void delay (int time) {
	int i = rand() % time;
	while (i--);
}
 
void *philosopher (void* arg) {
	int i = *(int *)arg;
	int left = i;//左筷子的编号和哲学家的编号相同
	int right = (i + 1) % N;//右筷子的编号为哲学家编号+1
	while (1) {
		printf("%dis thinking\n", i);
		delay(60000);
		
		printf("%dis hungry\n", i);
 
		pthread_mutex_lock(&mutex);//加锁
 
		sem_wait(&chopsticks[left]);//此时这个哲学家左筷子的信号量-1之后>=0时，表示能继续执行。
		printf("%dtake chopstick%d,only 1 chopstick,can not eating\n", i, left);
		sem_wait(&chopsticks[right]);
		printf("%dtake chopstick%d\n", i, right);
 
		pthread_mutex_unlock(&mutex);//解锁
 
		printf("%dhave 2 chopsticks,is eating\n", i);
		delay(60000);
		sem_post(&chopsticks[left]);
		printf("%ddrop chopstick%d\n", i, left);
		sem_post(&chopsticks[right]);
		printf("%ddrop chopstick%d\n", i, right);
	}
}
 
int main (int argc, char **argv) {
	srand(time(NULL));
	pthread_t philo[N];
	
	//信号量初始化
	for (int i=0; i<N; i++) {
		sem_init(&chopsticks[i], 0, 1);
	}
 
	pthread_mutex_init(&mutex,NULL);//初始化互斥锁
	
	//创建线程
	for (int i=0; i<N; i++) {
		pthread_create(&philo[i], NULL, philosopher, &philosophers[i]);
	}
	
	//挂起线程
	for (int i=0; i<N; i++) {
		pthread_join(philo[i], NULL);
	}
	
	//销毁信号量
	for (int i=0; i<N; i++) {
		sem_destroy(&chopsticks[i]);
	}
 
	pthread_mutex_destroy(&mutex);//销毁互斥锁
 
	return 0;
}

