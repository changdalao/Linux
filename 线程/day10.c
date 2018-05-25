#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>

pthread_mutex_t mutex;
pthread_cond_t cond;

int num=0;
#define CON 2//消费者
#define RPN 1//生产者
void* pro(void* arg)//生产者
{
    int id=*(int*)arg;
    free(arg);
    while(1)
    {
        pthread_mutex_lock(&mutex);//上锁
        printf("%d生产者线程开始生产第%d个产品\n",id,num+1);
        num++;
        sleep(1);
        printf("%d生产者生产第%d个产品结束\n",id,num);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);//解锁
        sleep(1);
    }
}
void* con(void* arg)//消费者
{
    int id=*(int*)arg;
    free(arg);
    while(1)
    {
        pthread_mutex_lock(&mutex);
        while(num<=0)
        {
            printf("%d消费者线程等待消费\n",id);
            pthread_cond_wait(&cond,&mutex);
            printf("%d消费者线程等待结束\n",id);
        }
        printf("%d消费者线程开始消费第%d个产品\n",id,num);
        num--;
        sleep(1);
        printf("%d消费者线程消费第%d个产品结束\n",id,num+1);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}
int main()
{
    pthread_t tid[CON+RPN];
    pthread_mutex_init(&mutex,NULL);//初始化互斥量
    pthread_cond_init(&cond,NULL);//初始化条件变量
    int i=0;
    for(i=0;i<RPN;i++)//创建生产者线程
    {
        int* p=malloc(sizeof(int));
        *p=i;
        pthread_create(&tid[i],NULL,pro,p);
    }
    for(i=0;i<CON;i++)//创建消费者线程
    {
        int* p=malloc(sizeof(int));
        *p=i;
        pthread_create(&tid[RPN+i],NULL,con,p);
    }
   for(i=0;i<RPN+CON;i++)
       pthread_join(tid[i],NULL);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return 0;
}
