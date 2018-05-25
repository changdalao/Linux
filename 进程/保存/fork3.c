#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
int main()
{
   /* pid_t pid;
    printf("ppid=%d\n",getpid());
    pid=fork();
    if(pid<0){
        printf("error\n");
        exit(0);
    }else if(pid>0){
        //printf("ppid=%d",getpid());
        pid=fork();
        //printf("ppid=%d",getppid());
        //printf("cpid=%d\n",pid);
        printf("ppid=%d,cpid=%d\n",getppid(),getpid());
        sleep(1);
    }else{
        //printf("cpid=%d\n",pid);

    }*/
    pid_t pid,pid1;
    pid=fork();
    if(pid<0){
        printf("error\n");
    }else if(pid==0){
        printf("这是子进程1，进程标识符是%d\n",getpid());
    }else{
        printf("这是子进程1的父进程,进程标识符是%d\n",getpid());
        pid1=fork();
        if(pid1>0){
            printf("这是子进程2的父进程，进程标识符是%d\n",getpid());
        }else if(pid1==0){
            printf("这是子进程2，进程标识符是%d\n",getpid());
        }
    }
    return 0;
}
