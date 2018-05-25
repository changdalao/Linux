#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc,char* argv[],char* envp[])
{
    printf("这是参数argc\n%d\n",argc);
    printf("这是参数argv\n");
    while(*argv){
        printf("%s\n",*(argv++));
    }
    printf("这是环境变量envp\n");
    while(*envp){
        printf("%s\n",*(envp++));
    }
    return 0;
}
