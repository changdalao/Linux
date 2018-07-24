// 读取共享内存，写入文件
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( void )
{
	// 1. 读取共享内存内容
	int shmid = shmget(1234, 0, 0);
	if ( shmid == -1 ) perror("shmget"),exit(1);
	int semid = semget(1234, 1, 0);
	if ( semid == -1 ) perror("semget"),exit(1);
	char *p = shmat(shmid, NULL, 0);
	if ( p == NULL ) perror("shmat"),exit(1);
	
	struct sembuf sb[1] = { {0, -1, 0} };
	semop(semid, sb, 1);
	
	char buf[1024] = {};
	strcpy(buf, p);
	
	struct sembuf sb1[1] = { {0, 1, 0} };
	semop(semid, sb1, 1);
	shmdt(p); // 卸载共享内存
	
	
	// 2. 写入文件
	int fd = open("./tmp", O_RDWR|O_TRUNC);
	if ( fd == -1) perror("open"),exit(1);
	
	write(fd, buf, strlen(buf));
	
	close(fd);
	
}
