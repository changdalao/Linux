#include<stdio.h>
#include<unistd.h>
#include<string.h>

int main()
{
    /*
    if(fork()>0){
        printf("ppid=%d\n",getpid());
        pid_t pid=fork();
        printf("ppid=%d,cpid=%d\n",getppid(),pid);
        if(pid==0){
            fork();
            printf("ppid=%d,cpid=%d\n",getppid(),getpid());
        }
    }*/
    pid_t pid;
    printf("这是父进程，进程标识符是%d\n",getpid());
    pid=fork();
    if(pid==0){
        printf("这是子进程1，进程标识符是%d\n",getpid());
        pid_t pid1=fork();
        if(pid1==0){
            printf("这是子进程2，进程标识符是%d\n",getpid());
        }
    }
}
