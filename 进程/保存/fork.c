#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
int main()
{
    pid_t pid;
    printf("parent->pid=%d\n",getpid());
    //printf("parent\n");
    pid=fork();
    if(pid<0){
        printf("error\n");
        printf("fork:%s\n",strerror(errno));
        exit(0);
    }else if(pid==0){
        int i=0;
        while(i<10){
        printf("childpid->%d,parent->pid=%d\n",getpid(),getppid());
        i++;
        sleep(1);
        }
        //printf("child\n");
    }else{
        while(1){
        printf("parent->pid=%d,childpid->%d\n",getpid(),pid);
        sleep(1);
        }
        //printf("parent\n");
    }

    return 0;
}
