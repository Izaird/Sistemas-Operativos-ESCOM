#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<wait.h>
#include<sys/types.h>

int main()
{
   printf("\nHola soy un proceso muy chido\n");
   printf("\nMi identificador es: %d\n",getpid());
   printf("\nMi proceso padre es: %d\n",getppid());
   sleep(30);
}
