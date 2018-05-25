#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
void beforemain()__attribute__((constructor));
void beforemain()
{
    printf("before main\n");
}

int main()
{
    printf("in main\n");

    printf("out main\n");
}
