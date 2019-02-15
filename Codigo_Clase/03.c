//Ejemplo de trabajo por lotes 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    system("ls -la");
    sleep(5);
    system("top -ea");
    sleep(5);
    system("clear");
    return 0;
}
