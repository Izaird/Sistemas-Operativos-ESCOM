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
      printf("\nHola soy el proceso hijo\n");
      printf("\nMi identificador es: %d\n",getpid());
      printf("\nMi proceso padre es: %d\n",getppid());
      sleep(10);
      //exit(0);
   }
   else
   {
      wait(NULL);      
      printf("\n\t\t\tHola soy el proceso padre\n");
      printf("\n\t\t\tMi identificador es: %d\n",getpid());
      printf("\n\t\t\tMi proceso padre es: %d\n",getppid());
      
   }
   printf("\n\t\t\tHola soy el proceso padre fuera del if\n");
   printf("\n\t\t\tMi identificador es: %d\n",getpid());
   printf("\n\t\t\tMi proceso padre es: %d\n",getppid());
   return 0;
}
