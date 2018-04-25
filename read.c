#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/ipc.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/msg.h>
struct msgbuf{
  long channel;
  char* mtext[100];
};
int main()
{
   int id=msgget(1234,0);
   if(id==-1)
      perror("mssget"),exit(1);
   struct msgbuf mb;
   printf("channel:");
   int channel;                                                                                                             
   scanf("%d",&channel);
   ssize_t r=msgrcv(id,&mb,100,channel,0);
   if(r==-1)
       perror("msgrcv"),exit(1);
   printf("%s\n",mb.mtext);
   return 0;
}
