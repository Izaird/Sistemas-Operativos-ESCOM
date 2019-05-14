#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int foo(const char *ID);    

int main()
{
        int n= 10;
        int status=0;


        printf("Creando %d hijos\n", n);
        foo("padre");
        for(int i=0;i<n;i++){
                pid_t pid=fork();

                if (pid==0){//Solo se ejecuta el hijo
                    foo("hijo");
                    
                        for (int i = 0; i < 10; i++){//Se hace el conteo y se imprime el pid y ppid para verficar que es el mismo padre e hijo
                            printf("%d pid:%d ppid:%d\n",i+1,getpid(),getppid());
                            sleep(1);
                        }

                    exit(0);

                }
                wait(&status);  /* Solo el padre espera */
        }



        return 0;
}


int foo(const char *ID)//Funcion para imprimir si es un padre o hijo y su pid y ppid
{
        printf("Soy un %s.  Mi pid es:%d  y mi ppid es:%d\n",
                        ID, getpid(), getppid() );
        return 1;
}
