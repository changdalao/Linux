/*
 *pthread_create
 *创建一个线程
*/
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>
#include<ctype.h>
#include<errno.h>
#include<sys/syscall.h>
void* show()
{
    //pid_t pid=syscall(SYS_gettid);
    //printf("%d\n",pid);
    printf("%u\n",syscall(SYS_gettid));
    printf("这是一个线程\n");
}
int main()
{
    pthread_t threadid;
    if((pthread_create(&threadid,NULL,show,NULL))!=0)
    {
        printf("pthread_create\n"),exit(0);
    }
    else
    {
        sleep(1);
        printf("main \n");
    }
    return 0;
}
