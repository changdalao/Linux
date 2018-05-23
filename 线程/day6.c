#include<unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include<string.h>

void *thread1( void *arg  )
{
    printf("thread 1 returning ... \n");
    int *p = (int*)malloc(sizeof(int));
    *p = 1;
    return (void*)p;//return 退出线程

}
void *thread2( void *arg  )
{
    printf("thread 2 exiting ...\n");
    int *p = (int*)malloc(sizeof(int));
    *p = 2;
    pthread_exit((void*)p);//pthread_exit退出线程

}
void *thread3( void *arg  )
{
    while ( 1  ){ //
        printf("thread 3 is running ...\n");
        
        sleep(1);
    }
    return NULL;
}
int main( void  )
{
    pthread_t tid;
    void *ret;
    // thread 1 return
     pthread_create(&tid, NULL, thread1, NULL);
     pthread_join(tid, &ret);
     printf("thread return, thread id %X, return code:%d\n", tid, *(int*)ret);
     free(ret);
     // thread 2 exit
     pthread_create(&tid, NULL, thread2, NULL);
     pthread_join(tid, &ret);
     printf("thread return, thread id %X, return code:%d\n", tid, *(int*)ret);
     free(ret);
     // thread 3 cancel by other
     pthread_create(&tid, NULL, thread3,NULL);
     sleep(3);
     pthread_cancel(tid);
     pthread_join(tid, &ret);
     if ( ret == PTHREAD_CANCELED  )
         printf("thread return, thread id %X, return code:PTHREAD_CANCELED\n", tid);
     else
         printf("thread return, thread id %X, return code:NULL\n", tid);

}
