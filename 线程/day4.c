#include<unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include<string.h>
void* show()
{
    printf("这是一个线程处理函数\n");
    pthread_exit("pthread exit");
}
int main()
{
    pthread_t tid;
    void* str;
    if(pthread_create(&tid,NULL,show,NULL)!=0){
        printf("error"),exit(1);
    }
    else
    {
        pthread_join(tid,&str);
        printf("%s\n",(char*)str);
    }
    return 0;
}
