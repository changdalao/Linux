#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
// ./udp_server 192.**.**.* 8080

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
    
    struct sockaddr_in local;
    local.sin_family=AF_INET;//地址类型
    local.sin_port=htons(atoi(argv[2]));//端口号
    local.sin_addr.s_addr=inet_addr(argv[1]);//IP地址转为整数+变为网络序列

    if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0){//绑定
        perror("bind");
        return 3;
    }

    char buf[128];
    while(1){//收数据，发数据
        struct sockaddr_in client;//客户端
        socklen_t len=sizeof(client);
        ssize_t s=recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&client,&len);//收数据
        if(s>0){
            buf[s]=0;
            printf("[%s:%d]:>%s\n",inet_ntoa(client.sin_addr), //ip地址
                                ntohs(client.sin_port),
                                buf);
            sendto(sock,buf,strlen(buf),0,(struct sockaddr*)&client,len);//发数据
        }
    }
    return 0;
}
