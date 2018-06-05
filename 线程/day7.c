/*
 *设置分离属性
*/
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<errno.h>
#include<stdlib.h>
void *show()
{
    printf("run\n");
}
pthread_attr_t attr;
int main()
{
    pthread_t tid;
    pthread_attr_init(&attr);//初始化属性
    int r=pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);//设置分离属性
    if(pthread_create(&tid,&attr,show,NULL)!=0)
        perror("pthread_create"),exit(1);
    if(r==PTHREAD_CREATE_JOINABLE)
        printf("PTHREAD_CREATE_JOINABLE\n");
    else if(r==PTHREAD_CREATE_DETACHED)
        printf("PTHREAD_CREATE_DETACHED\n");
    pthread_attr_destroy(&attr);//销毁属性
    return 0;
}
