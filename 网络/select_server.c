#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>

#define INIT -1

int startup(int port)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0){
		perror("socket");
		exit(2);
	}

	int opt = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	local.sin_port = htons(port);

	if(bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0){
		perror("bind");
		exit(3);
	}

	if(listen(sock, 5) < 0){
		perror("listen");
		exit(4);
	}

	return sock;
}

void handlerRequest(fd_set *rfds, int fd_array[], int num)
{
	int i = 0;
	for(; i < num; i++ ){
		if(fd_array[i] == INIT){
			continue;
		}

		if(i == 0 && FD_ISSET(fd_array[i], rfds)){
			//get a new connect
			struct sockaddr_in client;
			socklen_t len = sizeof(client);
			int sock = accept(fd_array[i], (struct sockaddr*)&client,\
					&len);
			if(sock < 0){
				perror("accept");
				continue;
			}
			printf("get a new client...!\n");
			int j = 1;
			for(; j < num; j++){
				if(fd_array[j] == INIT){
					break;
				}
			}
			if(j < num){
				fd_array[j] = sock;
			}
			else{
				close(sock);
				printf("select is full!\n");
			}
		}
		else if( i != 0 && FD_ISSET(fd_array[i], rfds) ){
			//normal read ready

			char buf[10240];
			ssize_t s = read(fd_array[i], buf, sizeof(buf)-1);
			if(s > 0){
				buf[s] = 0;
				printf("client# %s\n", buf);
			}else if( s == 0 ){
				close(fd_array[i]);
				printf("client quit!\n");
				fd_array[i] = INIT;
			}else{
				perror("read");
			}
		}
		else{
			//other
		}
	}
}

// ./select_server 80
int main(int argc, char *argv[])
{
	if(argc != 2){
		printf("Usage: %s [port]\n", argv[0]);
		return 1;
	}

	int listen_sock = startup(atoi(argv[1]));
	int fd_array[sizeof(fd_set)*8];
	int num = sizeof(fd_set)*8;
	fd_array[0] = listen_sock;

	int i = 1;
	for(; i < num; i++){
		fd_array[i] = INIT;
	}

	fd_set rfds;

	for( ; ; ){
		FD_ZERO(&rfds);
		int maxfd = INIT;
		for(i=0; i < num; i++){
			if(fd_array[i] == INIT){
				continue;
			}
			FD_SET(fd_array[i], &rfds);
			if(maxfd < fd_array[i]){
				maxfd = fd_array[i];
			}
		}

		struct timeval timeout = {0, 0};

		switch(select(maxfd+1, &rfds, NULL, NULL, NULL)){
			case -1:
				perror("select");
				break;
			case 0:
				printf("timeout...\n");
				break;
			default: //handlerRequest
				handlerRequest(&rfds, fd_array, num);
				break;
		}
	}

	return 0;
}
