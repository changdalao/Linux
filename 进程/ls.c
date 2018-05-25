#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
    execlp("ls","ls","-al","/etc/passwd",(char*)0);
    return 0;
}
