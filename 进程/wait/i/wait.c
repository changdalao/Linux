#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
int main()
{
    pid_t pid;
    pid=fork();
    switch(pid){
        case 0:
            {
            int i=0;
            for( i=0;i<10;i++){
                printf("$");
                fflush(stdout);
                sleep(1);
            }
            exit(0);
            }
        case -1:
            perror("fork");
            exit(1);
        default:
            {
                int stat;
                pid_t p;
                if((p=wait(&stat))==-1)
                    perror("wait");
                printf("wait %d,child pid=%d\n",p,pid);
            }
            break;
    }
}
