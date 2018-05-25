#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
    printf("pangdun is beautiful\n");
    char* argv[]={"date",NULL};
    execvp("date",argv);
    printf("after\n");
    return 0;
}
