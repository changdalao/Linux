#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int a=0;
int main()
{
    pid_t pid;
    int b=0;
    int *heap;
    heap=(int *)malloc(sizeof(int));
    *heap=1;
    printf("创建进程之前,a=%d,b=%d,*heap=%d\n",a,b,*heap);
    pid=vfork();
    if(pid<0){
        printf("error\n");
        exit(0);
    }else if(pid==0){
        ++a;
        ++b;
        ++(*heap);
        printf("child-->全局a=%d,栈b=%d,堆*heap=%d\n",a,b,*heap);
        exit(0);
    }else{
        printf("parent-->全局a=%d,栈b=%d,堆*heap=%d\n",a,b,*heap);
        printf("hehe\n");
        exit(0);
    }
    return 0;
}
