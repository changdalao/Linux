/*
 *同步：
 *利用互斥量、条件变量实现同步
*/
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
pthread_mutex_t mutex;
pthread_cond_t cond;

void* r1()
{
    while(1){
        pthread_cond_wait(&cond,&mutex);
        printf("wait返回\n");
    }
}
void* r2()
{
    while(1){
        pthread_cond_signal(&cond);
        sleep(1);
    }
}
int main()
{
    pthread_mutex_init(&mutex,NULL);//初始化互斥量
    pthread_cond_init(&cond,NULL);//初始化条件变量
    pthread_t t1,t2;
    //创建线程
    pthread_create(&t1,NULL,r1,NULL);//创建线程1
    pthread_create(&t2,NULL,r2,NULL);//创建线程2
    pthread_join(t1,NULL);//等待线程1结束
    pthread_join(t2,NULL);//等待线程2结束
    pthread_cond_destroy(&cond);//销毁条件变量
    pthread_mutex_destroy(&mutex);//销毁互斥量
    return 0;
}
