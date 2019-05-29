#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Table
{
	int page;
	int frame;
	int use;
	
}MMU;

void MostrarTabla(MMU *);


int main(int argc, char const *argv[])
{
	MMU Tabla [8];

	for (int i = 0; i < 8; ++i)
	{
		Tabla[i].pagina = -1;
		strcpy( Tabla[i].marco, "---" );
		Tabla[i].uso = -1;
	}
	
	MostrarTabla(Tabla);

	return 0;
}

void MostrarTabla(MMU *Tabla, int pagina, int marco)
{
	printf("\n\t\t\t      *** Tabla de dezplazamiento ***\n");
	printf("\n\t\t\t\t   Pagina   Marco    Uso\n");
	for (int i = 0; i < 8; ++i)
	{
		printf("\t\t\t\t\t%d | %s | %d \n",Tabla[i].pagina,Tabla[i].marco,Tabla[i].uso);

	}



}