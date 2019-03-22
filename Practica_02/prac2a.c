#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(){
    if(fork()==0){
        printf("Soy el hijo : PID %d\n", getpid());
    }else{
        printf("Soy el padre : PID %d\n", getpid());
    }
    return 0;
}