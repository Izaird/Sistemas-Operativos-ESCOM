#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
   int shmid, i;
   int *variable;
   key_t llave;
   pid_t pid;
   llave=ftok("Prueba",'k');
   shmid=shmget(llave,sizeof(int),IPC_CREAT|0600);
   variable=shmat(shmid,0,0);
   *variable=10;
   printf("\nLa variable vale %d\n",*variable);
   if((pid=fork())==0)
   {
      (*variable)--;
      exit(0);
   }
   else
   {
      wait(0);
      printf("La variable ahora vale:%d\n",*variable);
   }
   shmdt(&variable);
   shmctl(shmid,IPC_RMID,0);
   return 0;
}
