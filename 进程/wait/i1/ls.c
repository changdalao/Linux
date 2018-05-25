#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
    printf("this is maomaochong\n");
    char* argv[]={"ls","-l",NULL};
    execvp("ls",argv);
    printf("after execvp\n");
    return 0;
}
