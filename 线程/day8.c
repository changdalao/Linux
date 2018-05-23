/*
 *互斥：
 *
*/
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<errno.h>
#include<stdlib.h>

int a=0;
int b=0;
pthread_mutex_t mutex;
void *r1(){
    while(1){
        pthread_mutex_lock(&mutex);
        a++;
        b++;
        pthread_mutex_unlock(&mutex);
        if(a!=b){
            printf("%d!=%d\n",a,b);
            a=0;
            b=0;
        }
    }
}
void *r2(){
    while(1){
        pthread_mutex_lock(&mutex);
        a++;
        b++;
        pthread_mutex_unlock(&mutex);
        if(a!=b){
            printf("%d!=%d\n",a,b);
            a=0;
            b=0;
        }
    }
}
int main()
{
    pthread_mutex_init(&mutex,NULL);//初始化互斥量
    pthread_t t1,t2;
    pthread_create(&t1,NULL,r1,NULL);
    pthread_create(&t2,NULL,r2,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_mutex_destroy(&mutex);
    return 0;
}
