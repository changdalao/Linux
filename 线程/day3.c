#include<unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include<string.h>
void *route(void *arg)
{
    while ( 1  ) {
        //pthread_testcancel();
        // printf(" I'm active\n");
        // sleep(1);
        
    }

}

int main( void  )
{
    pthread_t tid;
    pthread_create(&tid, NULL, route, NULL);

    sleep(2);
    pthread_cancel(tid);
    printf("111\n");
    printf("%x thread dead\n", tid);

}
 
