#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>

int main(){
    pid_t pid;
    pid = fork();
    if (pid == -1) {
        perror("\nErro al crar el proceso");
        exit(-1);
    }

    if (pid == 0) {
        printf("Hola soy el proceso hijo\n");
        printf("Mi identificador es: %d\n",getpid());
        printf("Mi proceso padre es: %d\n\n",getppid());
        sleep(10);
        exit(0);
        }
    
    else{
        wait(NULL);
        printf("\t\t\tHola soy el proceso hijo\n");
        printf("\t\t\tMi identificador es: %d\n",getpid());
        printf("\t\t\tMi proceso padre es: %d\n\n",getppid());
    }
    
    printf("\t\t\tHola soy el proceso padre fuera del if\n");
    printf("\t\t\tMi identificador es: %d\n",getpid());
    printf("\t\t\tMi proceso padre es: %d\n",getppid());
    
    return 0;
}