#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_FILOSOFOS 5
#define NUM_TENEDORES 5

sem_t tenedores[NUM_TENEDORES];

void *filosofo(void *id)
{
    int i = *((int *)id);
    int izquierdo = i;
    int derecho = (i + 1) % NUM_FILOSOFOS;

    while (1)
    {
        printf("Filósofo [%d] está pensando...\n", i + 1);
        sleep(1);
        printf("Filósofo [%d] está hambriento...\n", i + 1);
        sem_wait(&tenedores[izquierdo]);
        sem_wait(&tenedores[derecho]);
        printf("Filósofo [%d] usa cubiertos (%d, %d)\n", i + 1, izquierdo + 1, derecho + 1);
        printf("Filósofo [%d] come\n", i + 1);
        sleep(2);
        sem_post(&tenedores[izquierdo]);
        sem_post(&tenedores[derecho]);
        printf("Filósofo [%d] regresa los cubiertos (%d, %d)\n", i + 1, izquierdo + 1, derecho + 1);
        printf("Filósofo [%d] piensa\n", i + 1);
    }
}

int main()
{
    pthread_t filosofos[NUM_FILOSOFOS];
    int i;

    for (i = 0; i < NUM_TENEDORES; i++)
    {
        sem_init(&tenedores[i], 0, 1);
    }

    for (i = 0; i < NUM_FILOSOFOS; i++)
    {
        int *id = malloc(sizeof(int));
        *id = i;
        pthread_create(&filosofos[i], NULL, filosofo, (void *)id);
    }

    for (i = 0; i < NUM_FILOSOFOS; i++)
    {
        pthread_join(filosofos[i], NULL);
    }

    return 0;
}
