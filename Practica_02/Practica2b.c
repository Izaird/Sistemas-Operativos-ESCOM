#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
  
int main() 
{ 
    for(int i=0;i<10;i++) // Se crean los 10 hijos
    { 
        if(fork() == 0) 
        { 
            printf("Hola soy el proceso con pid:%d y mi padre es:%d\n",getpid(),getppid()); 
            exit(0); 
        } 
    } 
        for(int i=0;i<10;i++) // Espera que termine los procesos
        wait(NULL); 
      
} 