#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
    pid_t pid;
    pid=fork();
    if(pid<0){
        printf("error\n");
        exit(1);
    }else if(pid==0){
        if(execvp("hello",NULL)<0){
            printf("fail to exec\n");
            exit(0);
        }
        printf("the child is no hello\n");
        exit(0);
    }
    printf("the parent\n");
    return 0;
}
