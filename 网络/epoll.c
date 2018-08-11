/*************************************************************************
	> File Name: epoll.c
	> Author: 
	> Mail: 
	> Created Time: Sat 11 Aug 2018 06:04:05 AM PDT
 ************************************************************************/

#include <stdio.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>


#define SIZE 1024

int startup(const char* ip,int port)
{
    int sock=socket(AF_INET,SOCK_STREAM,0);
    if(sock < 0){
        perror("socket");
        return 5;
    }
    struct sockaddr_in local;
    local.sin_family=AF_INET;
    local.sin_port=htons(port);
    local.sin_addr.s_addr=inet_addr(ip);

    if(bind(sock,(struct sockaddr*)&local,sizeof(local)) < 0){
        perror("bind");
        return 6;
    }

    if(listen(sock,10) < 0){
        perror("listen");
        return 7;
    }
    return sock;
}

int main(int argc,char* argv[])
{
    if(argc!=3)
    {
        printf("\rUsage:\n\r%s[ip][port]\n",argv[0]);
        return 1;
    }
    
    int listen_sock=startup(argv[1],atoi(argv[2]));

    int epfd=epoll_create(256);//创建epoll模型

    struct epoll_event event;
    event.data.fd=listen_sock;
    event.events=EPOLLIN;
    int ret=epoll_ctl(epfd,EPOLL_CTL_ADD,listen_sock,&event);
    if(ret < 0){
        perror("epoll_ctl");
        return 2;
    }

    struct epoll_event revs[SIZE];
    int timeout=2000;
    int num=-1;

    while(1){
        switch(num=epoll_wait(epfd,revs,SIZE,timeout)){
            case 0:
                //printf("timeout...\n");
                break;
            case -1:
                perror("epoll_wait");
                break;
            default://就绪事件    
                {
                    int i=0;
                    for(;i<num;i++){
                        int fd=revs[i].data.fd;
                        if(listen_sock == fd && (revs[i].events & EPOLLIN)){
                            //listen_sock
                            struct sockaddr_in client;
                            socklen_t len=sizeof(client);
                            int sock=accept(listen_sock,(struct sockaddr*)&client,&len);
                            if(sock < 0){
                                perror("accept");
                                continue;
                            }
                            printf("get a new client [%s:%d]\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
                            event.data.fd=sock;
                            event.events=EPOLLIN;
                            epoll_ctl(epfd,EPOLL_CTL_ADD,sock,&event);
                        }
                        else if(fd != listen_sock){
                            //normal_sock
                            if(revs[i].events & EPOLLIN){
                                //read
                                char buf[1024];
                                ssize_t s=read(revs[i].data.fd,buf,sizeof(buf)-1);
                                if(s < 0){
                                    perror("read");
                                    return 3;
                                }
                                else if(s == 0){
                                    close(revs[i].data.fd);
                                    printf("client quit...\n");
                                    epoll_ctl(epfd,EPOLL_CTL_DEL,revs[i].data.fd,NULL);
                                }
                                else
                                {
                                    buf[s]=0;
                                    printf("client$:%s\n",buf);
                                }
                            }
                            else if(revs[i].events & EPOLLOUT){
                                //write
                                char buf[1024];
                                ssize_t s=write(revs[i].data.fd,buf,strlen(buf));
                                if(s < 0){
                                    perror("write");
                                    return 4;
                                }
                            }
                            else{}
                        }//normal_sock
                        else{}
                    }//for
                }//default
                break;
        }//switch
    }//while
    
}//main
