#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<string.h>
#include<stdlib.h>
void fun1()
{
    printf("fun1\n");
}
int main()
{
    atexit(fun1);
    printf("hello word\n");
    return 0;
}
