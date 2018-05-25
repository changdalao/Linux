/*
 *这是一个多线程阻塞和退出
*/
#include<unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include<string.h>
void *run1()
{
    printf("thread 1 running\n");
    return ((void*)1);//return退出线程
} 
void *run2()
{
    printf("thread 2 running\n");
    pthread_exit((void*)2);//pthread_exit退出线程
}
int main()
{
    pthread_t tid1,tid2;
    void* srg;
    //创建线程1
    if(pthread_create(&tid1,NULL,run1,NULL)!=0)
        perror("thread1"),exit(1);
    if(pthread_create(&tid2,NULL,run2,NULL)!=0)
        perror("thread2"),exit(1);
    if(pthread_join(tid1,&srg)!=0)
        perror("阻塞线程1失败"),exit(1);
    printf("线程1的退出码%d\n",(int)srg);
    if(pthread_join(tid2,&srg)!=0)
        perror("阻塞线程2失败"),exit(1);
    printf("线程2的退出码%d\n",(int)srg);

    return 0;
}
