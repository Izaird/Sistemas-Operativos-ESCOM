#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
	pid_t Proceso;
	FILE *Archivo;
	char *palabras[]={"Hola","Esta","Es","Mi","Practica"};
	int n;

	n = 5;
	Archivo = fopen("./palabra.txt","a");
	if( Archivo == NULL)
	{
		printf("No se pudo abrir el archivo señalado\n");
		exit(0);
	}

	for (int i = 0; i < n; ++i)
	{
		Proceso = fork();
		if(Proceso == 0)
		{
			fprintf(Archivo,"%s - Proceso %d\n",palabras[i],i+1);
			break;
		}
	}
	if(Proceso != 0)
	{
		for (int j = 0; j < n; ++j)
			wait(NULL);
		
		fprintf(Archivo,"Uno - Padre\n\n");
		fclose(Archivo);
	}

	return 0;
}