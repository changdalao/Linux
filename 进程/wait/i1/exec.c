#include<stdio.h>
#include<unistd.h>

int main()
{
    printf("before execlp\n");
    execlp("ls","ls","-l",NULL);
    printf("after execlp\n");

}
