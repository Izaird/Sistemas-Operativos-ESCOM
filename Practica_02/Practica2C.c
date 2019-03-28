#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>

int main(){

    pid_t pid;
    pid_t PidHijos;
    pid_t PidHijos2;
    
    printf("Hola soy el padre\n");
    printf("Mi proceso padre es: %d\n",getppid());
    printf("Mi identificador es: %d\n\n",getpid());
    

    pid = fork();
    if (pid == 0) {
        printf("\tHola soy el proceso hijo\n");
        printf("\tMi proceso padre es: %d\n",getppid());
        printf("\tMi identificador es: %d\n\n",getpid());
      
            for (int i = 0; i < 3; ++i)
            {   
               PidHijos = fork();
                if (PidHijos ==0)
                {
                    printf("\t\tHola soy el proceso hijo del hijo, %d\n",i);
                    printf("\t\tMi proceso padre es: %d\n",getppid());
                    printf("\t\tMi identificador es: %d\n\n",getpid());

                    for (int i = 0; i < 2; ++i)
                    {   
                        PidHijos = fork();
                        if (PidHijos ==0)
                        {
                            printf("\t\t\tHola soy el proceso hijo del hijo, %d\n",i);
                            printf("\t\t\tMi proceso padre es: %d\n",getppid());
                            printf("\t\t\tMi identificador es: %d\n\n",getpid()); 
                            break; 
                        }
                        else
                            wait(NULL); 
                    } 
                    break; 
                }
                else
                    wait(NULL);
            }
        }
    
    else
        wait(NULL);
        
    return 0;
}