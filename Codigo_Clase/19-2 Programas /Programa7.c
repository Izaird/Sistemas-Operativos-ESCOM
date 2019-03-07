#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<wait.h>
#include<sys/types.h>

int main()
{
   pid_t pid;
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
         printf("\nHola soy el proceso hijo\n");
         printf("\nMi identificador es: %d\n",getpid());
         printf("\nMi proceso padre es: %d\n",getppid());
         sleep(1);
      }
   }
   else
   {
      while(1)
      {
         printf("\n\t\t\tHola soy el proceso padre\n");
         printf("\n\t\t\tMi identificador es: %d\n",getpid());
         printf("\n\t\t\tMi proceso padre es: %d\n",getppid());
         sleep(1);
      }
   }
   return 0;
}
