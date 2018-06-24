#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>

// ./udp_client 192.**.**.* 8080
//客户端

int main(int argc,char* argv[])
{
    if(argc!=3){
        printf("Usage:%s ip port\n",argv[0]);
        return 1;
    }

    int sock=socket(AF_INET,SOCK_DGRAM,0);//创建套接字
    if(sock<0){
        perror("socket");
        return 2;
    }
    
    struct sockaddr_in server;
    server.sin_family=AF_INET;//地址类型
    server.sin_port=htons(atoi(argv[2]));//端口号
    server.sin_addr.s_addr=inet_addr(argv[1]);//IP地址转为整数+变为网络序列
    //客户端不需要绑定，服务器端必须绑定
    char buf[128];
    while(1){//先发送，后接收
        printf("please enter:");
        fflush(stdout);
        ssize_t s=read(0,buf,sizeof(buf)-1);
        if(s>0){
            buf[s-1]=0;
            sendto(sock,buf,strlen(buf),0,(struct sockaddr*)&server,sizeof(server));

        }
        ssize_t r=recvfrom(sock,buf,sizeof(buf)-1,0,NULL,NULL);
        if(r>0){
            buf[r]=0;
            printf("server echo# %s\n",buf);
        }
    }
    return 0;
}
