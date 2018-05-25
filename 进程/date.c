#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
    execl("/bin/date","bin/date",(char*)0);
    return 0;
}
