#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>

void regionCritica(int PID)
{
   int i;
   printf("\nProceso en la region critica proceso con pid=%d\n",PID);
   for(i=0;i<3;i++)
   {
      printf("\nRegión critica: %d\n",i);
      sleep(1);	
   }
}

void regionNoCriticaProcesoHijo(int PID)
{
   int i;
   printf("\nHijo en la region NO critica proceso con pid=%d\n",PID);
   for(i=0;i<5;i++)
   {
      printf("\nHijo: %d\n",i);
      sleep(1);
   }
}

void regionNoCriticaProcesoPadre(int PID)
{
   int i;
   printf("\nPadre en la region NO critica proceso con pid=%d\n",PID);
   for(i=0;i<5;i++)
   {
      printf("\nPadre: %d\n",i);
      sleep(1);
   }
}

int main()
{
   pid_t pid;
   int PID;
   int shmid;
   int i;
   int *turno;
   key_t llave;
   llave=ftok("Prueba",'k');
   shmid=shmget(llave,sizeof(int),IPC_CREAT|0600);
   turno=shmat(shmid,0,0);
   *turno=0;
   pid= fork();
   if(pid==-1)
   {
      perror("\nError al crear el proceso\n");
      exit(-1);
   }
   if(pid==0)
   {
      while (1)
      {
         while (*turno!=0);
         PID=getpid();
         regionCritica(PID);
         *turno=1;
         regionNoCriticaProcesoHijo(PID);
      }
   }
   else
   {
      while(1)
      {
         while (*turno!=1);
         PID=getpid();
         regionCritica(PID);
         *turno=0;
         regionNoCriticaProcesoPadre(PID);
      }
   }
   return 0;
}
