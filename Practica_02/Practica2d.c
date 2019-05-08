#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
	//Variables que se van a ocupar en el programa
	pid_t Proceso; 	//variable que guardará el resultado de la función fork()
	FILE *Archivo;	//variable que guardará el apuntador al archivo palabra.txt
	char *palabras[]={"Hola","Esta","Es","Mi","Practica"};	//Elemntos de la frace "Hola esta e smi practica "
	int n; //variable que aguarda el numero de hijos

	n = 5;
	Archivo = fopen("./palabra.txt","a");	//Asiganación del apuntador del archivo
	if( Archivo == NULL)
	{
		printf("No se pudo abrir el archivo señalado\n"); //Si el apuntador no se puede asignar por algun motivo, el programa mostrará este mensaje y lo terminará
		exit(0);
	}

	for (int i = 0; i < n; ++i) //bucle finito que se ocpua para crear los hijos y que estos escriban la palabra que les corresponde
	{
		Proceso = fork();
		if(Proceso == 0) // Acciones que se harán si la función fork() regresa el valor 0
		{
			fprintf(Archivo,"%s - Proceso %d. mi PID es: %d. El PID de mi padre es: %d\n",palabras[i],i+1,getpid(),getppid()); //Sentencia para imprimir en el archivo por medio del apuntador que asigno el padre
			break;
		}
	}
	if(Proceso != 0) //Acciones que se harán si la función fork() regresa diferente de 1
	{
		for (int j = 0; j < n; ++j) //Se espera a todos los hijos que se crearon
			wait(NULL);
		
		fprintf(Archivo,"Uno - Proceso Padre, PID: %d\n\n",getpid());	//El padre imprime la ultima palabra en el archivo
		fclose(Archivo);	//El padre cierra el apuntador al archivo
	}

	return 0;
}
	//termina el programa