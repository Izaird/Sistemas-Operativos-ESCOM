#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <time.h>

int main()
{
    int shmid, i;
    int h;
    float *array;       //aqui creamos un apuntador a un arreglo de flotantes, aquí se guardarán los flotantes :)
    key_t llave;
    pid_t pid;
    llave=ftok("Prueba",'k');
    shmid=shmget(llave,sizeof(int),IPC_CREAT|0600);
    array = shmat(shmid, 0, 0);     //con esta linea le indicamos al arreglo el segmento de memoria compartida que se va a utilizar.
  
    if((pid=fork())==0){             //aqui trabajamos con el proceso hijo
        srand48(time(NULL));       // esta linea nos provee de numeros flotantes aleatorios entre 0 y 1
        for(i=0; i<10; i++)
            array[i] = drand48();       //aqui le asignamos dichos numeros al arreglo previamente creado.

	exit(0);
    }
    else{
	    wait(0);
        for(h=0; h<10; h++)     //con este ciclo, simplemente vamos a mostrar en pantalla los números guardados por el proceso hijo.   
            printf("\n%f---\n", array[h] );
        
        shmdt((void *) array);
        return 0;
    }
    shmctl(shmid,IPC_RMID,0);
 }





