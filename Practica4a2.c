#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char const *argv[])
{
  key_t llave; //Variable que aguardará lo que regresa la función FTOK
  int shmid; //variable que aguardará lo que regresa la funcion SHMGET
  int *turno; //Apuntador que recibirá la dirección de la variable que se compratirá entre los dos programas

  printf("\nHola, yo soy el programa 1"); 
  llave = ftok("Zona",'k'); //Se obtiene la llave para poder utilizar el archivo ZONA 
  printf("\n Llave: %d",llave); //Imprime la llave que obtuvo 
  shmid = shmget(llave,sizeof(int),IPC_CREAT|0600); //Se obtiene un permiso para poder ocupar la memoria del tamaño que se indico 
  printf("\n identificador: %d",shmid); // Se imprime el identificador que se obtuvo
  turno = shmat(shmid,0,0); // Se obtiene la direccion del espacio de memoria al que ambos programas podrán acceder
  // se puede observar que no se le asigna ningun valor ya que el programa 1 ya lo hizo

  while (1) //El programa realiza las acciones hasta que el programa se detiene desde la terminal
  {
      while(*turno != 1); //El programa crea un bucle que no termina hasta que la variable se igual a 1
      printf("\n"); //se imprime un espacio para que se aprecie mejor dicho bucle

        for(int j = 0; j < 3; j++) 
        {
          printf("\n Practica 2, Estoy en Región critica: %d\n",j+1); //se imprime 3 veces con el fin de hacer esperar el programa 1
          sleep(1); 
        }
        
        *turno = 0; // Al terminar el for se cambia el valor de la variable para que el programa 1 pudiese interactuar con la variable compartida
  }

  return 0;   
}