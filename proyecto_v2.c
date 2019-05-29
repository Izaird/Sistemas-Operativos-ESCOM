#include<stdio.h>
#include<stdlib.h>

#define TAM_PAG 4096

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

    pagina=&NumeroDePagina;
    marco=&NumeroDeMarco;


    for(indice=0;indice<16;indice++){
        ImprimirTablaMMU(pagina, marco);
        printf("\nSe movió correctamente la página %d al marco %d.\n",indice, indice%8) ;
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