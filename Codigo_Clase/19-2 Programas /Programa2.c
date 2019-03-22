#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
int contador=1;
   while(1)
   {
      printf("\nHola mundo cruel, contador: %d\n",contador);
      sleep(1);
      contador++;
   }
   return 0;
}
