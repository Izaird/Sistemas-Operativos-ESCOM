#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#define TAM_PAG 4096

typedef struct Table
{
    int pagina;
    int uso;
    
}MMU;



void MostrarTabla(MMU *Tabla)
{
    printf("\n\t\t\t      *** Tabla de dezplazamiento ***\n");
    printf("\n\t\t\t\t   Pagina   Marco    Uso\n");

    for (int i = 0; i < 8; ++i)
    {
        printf("\t\t\t\t\t%c | %s | %c \n",Tabla[i].pagina,Tabla[i].marco,Tabla[i].uso);

    }



}

void BitsDeDesplazamiento ( int num )
{
    int sup = 11;
    while(sup >= 0)
    {
        if(num & (((long int)1) << sup))
            printf("1");
        else
            printf("0");
        sup--;
    }
    
}

void BitsDePagina ( int num )
{
    int sup = 3;
    while(sup >= 0)
    {
        if(num & (((long int)1) << sup))
            printf("1");
        else
            printf("0");
        sup--;
    }
    
}

void BitsDeMarco ( int num )
{
    int sup = 2;
    while(sup >= 0)
    {
        if(num & (((long int)1) << sup))
            printf("1");
        else
            printf("0");
        sup--;
    }
    
}

int ImprimirTablaMMU(int *pagina, int *marco)
{
    int i;
    int x=0;
    int pag=*pagina;
    int marc=*marco;

    for(i=0;i<TAM_PAG;i++){
        BitsDePagina(pag);
        printf("\t");
        BitsDeDesplazamiento(i);
        printf("\t ====> \t");
        BitsDeMarco(marc);
        printf("\t");
        BitsDeDesplazamiento(i);
        printf("\n");
        *pagina=*pagina+1;
        *marco=*marco+1;
    }
    *pagina=*pagina+1;
    *marco=*marco+1;

    
    return 0;
}
int main(void){
    int NumeroDePagina=0;
    int NumeroDeMarco=0;
    int indice;
    int *pagina;
    int *marco;
    int indiceDePagina=0;
    int indiceDeMarco=0;
    MMU Tabla[8];

    pagina=&NumeroDePagina;
    marco=&NumeroDeMarco;



    for (int i = 0; i < 8; ++i)
    {
        Tabla[i].pagina = '-';
        strcpy( Tabla[i].marco, "---" );
        Tabla[i].uso = '-';
    }

    MostrarTabla(Tabla);

    for(indice=0;indice<16;indice++){
        ImprimirTablaMMU(pagina, marco);
        printf("\nSe movió correctamente la página %d al marco %d.\n",indice, indice%8) ;
        indiceDePagina = indiceDePagina + 1;
        indiceDeMarco = indiceDeMarco + 1;

        if (indiceDeMarco > 7)
        {
             indiceDeMarco = 0;
        } 

        Tabla[indiceDeMarco].pagina = indiceDePagina;
        strcpy(Tabla[indiceDeMarco].marco, marcos[indiceDeMarco]);
        Tabla[indiceDeMarco].uso = 1;

        MostrarTabla(Tabla);

        if(indice<7)
            printf("\nQuedan %d marcos disponibles.\n", 7-(indice%8));
        if(indice >= 7 && indice <15){
            printf("\nLa memoria fisica esta llena.\n");
            printf("Se sobreescribirá el marco %d.\n",indice-7);
        }
        if(indice!=15)
            system( "read -n 1 -s -p \"\nPresione ENTER para continuar...\n\n\"" );    
        if(indice==15)
        {
            printf("\n------------------------------------\nEl proceso terminó satisfactoriamente.\n------------------------------------\n");
            printf("\n\n\n");
        }
        
    }

}