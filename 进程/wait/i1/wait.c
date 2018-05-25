#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

int main()
{
    pid_t pid=fork();
    if(pid==0){
        if(fork()>0){
            exit(0);
        }
        for(; ; ){
            printf("孙子\n");
            sleep(1);
        }
    }else{
        wait(NULL);
        for(; ;){
            printf("老子\n");
            sleep(1);
        }
    }
    return 0;
}
