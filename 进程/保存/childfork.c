#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    pid_t pid1,pid2;
    pid1=fork();
    if(pid1<0){
        printf("eror\n");
        exit(0);
    }else if(pid1==0){
        printf("这是子进程1，进程标识符是%d\n",getpid());
        pid2=fork();
        if(pid2<0){
            printf("error\n");
            exit(0);
        }else if(pid2>0){
            printf("这是子进程2的父进程，进程标识符是%d\n",getpid());
        }else{
            printf("这是子进程2，进程标识符是%d\n",getpid());
        }
    }else{
        printf("这是子进程1的父进程，进程标识符是%d\n",getpid());
    }
    return 0;
}
