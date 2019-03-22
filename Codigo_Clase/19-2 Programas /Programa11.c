#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/types.h>

void regionCritica()
{
   int i;
   printf("\nProceso en la region critica proceso con pid=%d\n",getpid());
   for(i=0;i<3;i++)
   {
      printf("\nRegión critica: %d\n",i);
      sleep(1);	
   }
}

void regionNoCritica()
{
   int i;
   printf("\nEn la region NO critica proceso con pid=%d\n",getpid());
   for(i=0;i<10;i++)
   {
      printf("\nContando(%d): %d\n",getpid(),i);
      sleep(1);
   }
}

int main()
{
   int shmid;
   int i;
   int *turno;
   key_t llave;
   llave=ftok("Prueba",'k');
   shmid=shmget(llave,sizeof(int),IPC_CREAT|0600);
   turno=shmat(shmid,0,0);
   while(1)
   {
      while(*turno!=1);
      regionCritica();
      *turno=0;
      regionNoCritica();
   }
}
