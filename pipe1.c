#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>

int main()
{
    int fd[2];
    char writebuf[]="pangdun is a girl\n";                                                                                            
    char readbuf[100];
    int id=pipe(fd);
    if(id<0)
    {   
        printf("创建管道失败\n");
        exit(1);
    }   
    write(fd[1],writebuf,sizeof(writebuf));
    read(fd[0],readbuf,sizeof(writebuf));
    printf("%s",readbuf);
    printf("管道的读id是%d,写id是%d\n",fd[0],fd[1]);
    close(fd[0]);
    close(fd[1]);
    return 0;
}
