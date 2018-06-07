#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>

sem_t blackSem;//生产者
sem_t dataSem;//消费者

#define NUM 128

int running[NUM];//环形队列

void* consume()//消费者
{
    srand((unsigned int)time);
    int data;
    int step=0;
    while(1){
        sem_wait(&dataSem);//p
        data=running[step];
        printf("consume is done,data is %d\n",data);
        step++;
        step%=128;
        sleep(1);
        sem_post(&blackSem);
    }
}
void* produce()//生产者
{
    srand((unsigned int)time);
    int data;
    int step=0;
    while(1){
        sem_wait(&blackSem);
        data=rand()%1024;
        running[step]=data;
        printf("produce is done,data is %d\n",data);
        step++;
        step%=128;
        sem_post(&dataSem);
        sleep(1);
    }    
}
int main()
{
    //初始化信号量
    sem_init(&blackSem,0,NUM);
    sem_init(&dataSem,0,0);
    
    //创建线程
    pthread_t t1,t2;
    pthread_create(&t1,NULL,consume,NULL);
    pthread_create(&t2,NULL,produce,NULL);


    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    //销毁信号量
    sem_destroy(&blackSem);
    sem_destroy(&dataSem);
    return 0;
}
