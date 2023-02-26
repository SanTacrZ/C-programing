#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_HILOS 4
#define n 14
#define n1 10
#define n2 10
int acumulada = 0;
pthread_mutex_t mutex_acumulado;

void *thread_acumulada(void *arg) {
    
    int acumulado = 0;
    for (int i = 1; i <= n2; i++) {
        acumulado += i;
        // Imprimir el acumulado actual en formato de lista separada por comas
        printf("Hilo 1: Acumulado hasta %d es ", n2);
        for (int j = 1; j <= i; j++) {
            if (j == i) {
                printf("%d+%d", j - 1,j);
            } else {
                printf("%d+", j - 1);
            }
        }
        printf("=%d\n", acumulado);
    }
    
    acumulada += acumulado;
   usleep(2000000); // agregar 1 segundo de proceso
    pthread_exit(NULL);
}

void *thread_productoria(void *arg) {
    
    int productoria = 1;
    for (int i = 1; i <= n1; i++) {
        productoria *= i;
        printf("Hilo 2: Productoria de %d es %d, %d\n",n1, i,productoria);
    }
  usleep(2000000); // agregar 1 segundo de proceso
    pthread_exit(NULL);
}


void *thread_potencias(void *arg) {
    
    for (int i = 0; i <= 10; i++)
    {
        int potencia = 1;
        for (int j = 0; j < i; j++) {
            potencia *= 2;
        }
        printf("Hilo 3: 2 elevado a la %d es %d\n", i, potencia);
    }
    usleep(2000000); // agregar 1 segundo de proceso
    pthread_exit(NULL);
}


void *thread_fibonacci(void *arg) {
    
    int a = 0, b = 1;
    for (int i = 2; i <= n; i++) {
        int c = a + b;
        a = b;
        b = c;
        printf("Hilo 4: Secuencia de Fibonacci hasta %d es: %d, %d\n",n, a, b);
    }
    printf("\n");
    usleep(2000000); // agregar 1 segundo de proceso
    pthread_exit(NULL);
}
  

int main() {
    pid_t  parent_pid = getpid();
    pthread_t hilos[NUM_HILOS];
    int args[NUM_HILOS];

        // Hilo 1: Acumulada
    args[0] = 3;
    pthread_create(&hilos[0], NULL, thread_acumulada, &args[0]);
    pthread_join(hilos[0], NULL);
    // Hilo 2: Productoria
    args[1] = 4;
    pthread_create(&hilos[1], NULL, thread_productoria, &args[1]);
    pthread_join(hilos[1], NULL);
    // Hilo 3: Potencias de 2
    args[2] = 5;
    pthread_create(&hilos[2], NULL, thread_potencias, &args[2]);
    pthread_join(hilos[2], NULL);
    // Hilo 4: Fibonacci
    args[3] = 10;
    pthread_create(&hilos[3], NULL, thread_fibonacci, &args[3]);
    pthread_join(hilos[3], NULL);

    for (int i = 0; i <= NUM_HILOS; i++) {
        pthread_join(hilos[i], NULL);
        pthread_t thread_id = pthread_self();
        printf("Funcion principal PID:%d del hilo: %d\n", parent_pid,i);
    }
 while(1)
        ;
 return 0;
}