#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define Procesos 5

//int Global_i=0;
//int extern Global_i;
int *Global_i=0;

void codigo_del_proceso(int id, int herencia)
{
   int i;
   //int Global_i=0; //Solo cuando es extern
   for(i=0;i<5;i++)
   {
      printf("\nProceso %d: i=%d, Global_i=%d, Herencia=%d PID=%d\n",id,i,(*Global_i)++,herencia,getpid());
      sleep(2);
   }
   exit(id);
}

int main()
{
   int p;
   int id[Procesos]={1,2,3,4,5};
   int variable_heredada=0;
   int pid;
   int salida;
   for(p=0;p<Procesos;p++)
   {
      pid=fork();
      if(pid==-1)
      {
         perror("Error al crear el proceso");
         exit(-1);
      }
      else if(pid==0)
      {
         codigo_del_proceso(id[p], variable_heredada);
      }
      variable_heredada++;
   }
   for(p=0;p<Procesos;p++)
   {
      pid=wait(&salida);
      printf("\nProceso %d con id=%d terminado\n",pid,salida>>8);
      sleep(2);
   }
}

