// Implementación del algoritmo de Peterson
// para el problema de consumidor-productor
// :)
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <time.h> 
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdbool.h> 
#define _BSD_SOURCE 
#include <sys/time.h> 
#include <stdio.h> 
  
#define BSIZE 4 // Tamano del Buffer 
#define PWT 2 // Tiempo limite de espera del productor
#define CWT 5 // Tiempo limite de espera del consumidos
#define RT 5 // Tiempo para correr el programa en segundos


int shmid1, shmid2, shmid3, shmid4; 
key_t k1 = 5491, k2 = 5812, k3 = 4327, k4 = 3213; 
bool* SHM1; 
int* SHM2; 
int* SHM3; 
  

// Recibe: Un numero entero
// Regresa: un numero entero aleatorio entre 1 y n  
int myrand(int n) 
{ 
    time_t t; 
    srand((unsigned)time(&t)); 
    return (rand() % n + 1); 
} 
  
int main() 
{ 
    shmid1 = shmget(k1, sizeof(bool) * 2, IPC_CREAT | 0660); // bandera 
    shmid2 = shmget(k2, sizeof(int) * 1, IPC_CREAT | 0660); // cambio 
    shmid3 = shmget(k3, sizeof(int) * BSIZE, IPC_CREAT | 0660); // buffer 
    shmid4 = shmget(k4, sizeof(int) * 1, IPC_CREAT | 0660); // marca de tiempo
  
    if (shmid1 < 0 || shmid2 < 0 || shmid3 < 0 || shmid4 < 0) { 
        perror("error en shmget : "); 
        exit(1); 
    } 
    SHM3 = (int*)shmat(shmid3, NULL, 0); 
    int ix = 0; 
    while (ix < BSIZE) // Inicializamos buffer 
        SHM3[ix++] = 0; 
  
    struct timeval t; 
    time_t t1, t2; 
    gettimeofday(&t, NULL); 
    t1 = t.tv_sec; 
  
    int* state = (int*)shmat(shmid4, NULL, 0); 
    *state = 1; 
    int wait_time; 
  
    int i = 0; // Consumidor 
    int j = 1; // Productor 
  
    if (fork() == 0) // Código de Productor
    { 
        SHM1 = (bool*)shmat(shmid1, NULL, 0); 
        SHM2 = (int*)shmat(shmid2, NULL, 0); 
        SHM3 = (int*)shmat(shmid3, NULL, 0); 
        if (SHM1 == (bool*)-1 || SHM2 == (int*)-1 || SHM3 == (int*)-1) { 
            perror(" error en shmat de Productor: "); 
            exit(1); 
        } 
  
        bool* flag = SHM1; 
        int* turn = SHM2; 
        int* buf = SHM3; 
        int index = 0; 
  
        while (*state == 1) { 
            flag[j] = true; 
            printf("---Productor esta listo---.\n\n"); 
            *turn = i; 
            while (flag[i] == true && *turn == i); 
  
            // Critical Section Begin 
            index = 0; 
            while (index < BSIZE) { 
                if (buf[index] == 0) { 
                    int tempo = myrand(BSIZE * 3); 
                    printf("El trabajo %d ha sido producido\n", tempo); 
                    buf[index] = tempo; 
                    break; 
                } 
                index++; 
            } 
            if (index == BSIZE) 
                printf("Buffer lleno, ya no se puede producir!!!\n"); 
            printf("Buffer: "); 
            index = 0; 
            while (index < BSIZE) 
                printf("%d ", buf[index++]); 
            printf("\n"); 
            // Critical Section End 
  
            flag[j] = false; 
            if (*state == 0) 
                break; 
            wait_time = myrand(PWT); 
            printf("Productor esperara %d segundos\n\n", wait_time); 
            sleep(wait_time); 
        } 
        exit(0); 
    } 
  
    if (fork() == 0) // Consumer code 
    { 
        SHM1 = (bool*)shmat(shmid1, NULL, 0); 
        SHM2 = (int*)shmat(shmid2, NULL, 0); 
        SHM3 = (int*)shmat(shmid3, NULL, 0); 
        if (SHM1 == (bool*)-1 || SHM2 == (int*)-1 || SHM3 == (int*)-1) { 
            perror("error en shmat dell consumidor:"); 
            exit(1); 
        } 
  
        bool* flag = SHM1; 
        int* turn = SHM2; 
        int* buf = SHM3; 
        int index = 0; 
        flag[i] = false; 
        sleep(5); 
        while (*state == 1) { 
            flag[i] = true; 
            printf("----Consumidor esta listo----.\n\n"); 
            *turn = j; 
            while (flag[j] == true && *turn == j) 
                ; 
  
            // Comienza la seccion crítica 
            if (buf[0] != 0) { 
                printf("El trabajo %d ha sido consumido\n", buf[0]); 
                buf[0] = 0; 
                index = 1; 
                while (index < BSIZE) // Recorremos los trabajos restantes
                { 
                    buf[index - 1] = buf[index]; 
                    index++; 
                } 
                buf[index - 1] = 0; 
            } else
                printf("Buffer is empty, nothing can be consumed!!!\n"); 
            printf("Buffer: "); 
            index = 0; 
            while (index < BSIZE) 
                printf("%d ", buf[index++]); 
            printf("\n"); 
            // Termina sección crítica
  
            flag[i] = false; 
            if (*state == 0) 
                break; 
            wait_time = myrand(CWT); 
            printf("Consumidor ira a dormir %d segundos\n\n", wait_time); 
            sleep(wait_time); 
        } 
        exit(0); 
    } 
    //proceso padre va a esperar por RT segundos antes de hacer que su hijo termine 
    while (1) { 
        gettimeofday(&t, NULL); 
        t2 = t.tv_sec; 
        if (t2 - t1 > RT) //El programa terminará despues de RT segundos
        { 
            *state = 0; 
            break; 
        } 
    } 
    //Esperamos a que ambos procesos terminen
    printf("Se terminó el tiempo.\n"); 
    return 0; 
} 