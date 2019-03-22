#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
   while(1)
   {
      printf("\nHola alumnos, yo soy: %d\n",getpid());
      sleep(1);
   }
   return 0;
}
