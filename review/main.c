#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>

#include "add.h"

union semun {
	int val;
};

int main( void )
{
	// 读取文件
	int fd;
again:
	fd = open("./tmp", O_RDONLY);
	if ( fd == -1 ){
		if (errno == EINTR) {
			goto again;
		}
		perror("open");
		exit(1);
	}
	char buf[100];
	memset(buf, 0x00, sizeof(buf));
	int r = read(fd, buf, 100);
	if (r == -1 )perror("read"),exit(1);
	
	close(fd);
	int left, right;
	// 2. 调用动态库计算加法
	sscanf(buf, "%d+%d", &left, &right); // 从buf中提取加数和被加数
	r = add(left, right);
	
	// 3. 将结果转化成字符串，写到共享内存
	memset(buf, 0x00, sizeof(buf));
	sprintf(buf, "%d+%d=%d\n", left, right, r);
	// 3.1 创建共享内存和信号量
	int shmid = shmget(1234, strlen(buf), IPC_CREAT|0644);
	if ( shmid == -1 ) perror("shmget"),exit(1);
	char *p = shmat(shmid, NULL, 0); // 挂载
	int semid = semget(1234, 1, IPC_CREAT|0644);
	if ( semid == -1 ) perror("semget"),exit(1);
	union semun su;
	su.val = 1;
	semctl(semid, 0, SETVAL, su);
	
	struct sembuf sb[1] = { {0, -1, 0} };
	semop(semid, sb, 1);
	
	strcpy(p, buf);
	
	struct sembuf sb1[1] = { {0, 1, 0} };
	semop(semid, sb1, 1);
	
	shmdt(p);// 卸载共享内存
	
	pid_t pid;
	if ( (pid=fork()) == 0 ) {
		char *argv[] = { "write", NULL};
		execvp("./write", argv);
		perror("execvp");
		exit(0);
	}
	waitpid(pid, NULL, 0);
}










