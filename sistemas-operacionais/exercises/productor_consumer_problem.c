#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define TRUE 1
#define PRODUTORES 2 
#define CONSUMIDORES 9
#define BUFFER_LENGTH 9

int buffer[BUFFER_LENGTH];

int buffer_indice_producao=0;
int buffer_indice_consumo=0;

long int item_value = 0;

sem_t mutex, empty, full;

void insert_item(int item) 
{
    if(buffer_indice_producao==BUFFER_LENGTH)
        buffer_indice_producao = 0;

    buffer[buffer_indice_producao] = item;

    buffer_indice_producao += 1;
}

int consumir_item() 
{
    int item = buffer[buffer_indice_consumo];

    buffer_indice_consumo += 1;

    if(buffer_indice_consumo == BUFFER_LENGTH)
        buffer_indice_consumo = 0;

    return item;
}

int produzir_item() 
{
    return (item_value == 10) ? (item_value=0) : (item_value++);
}

void *produtor(void *args)
{
    int tid = *(int *)args;
    int item;

    while(TRUE) 
    {
        item = produzir_item();
        
        sem_wait(&empty);
        sem_wait(&mutex);

        printf("Produtor....%d: produzindo item %d\n", tid, item);
        
        insert_item(item);

        sem_post(&mutex);
        sem_post(&full);
    }
}

void *consumidor(void *args) 
{
    int item;
    int tid = *(int *)args;

    while(TRUE) 
    {
        sem_wait(&full);
        sem_wait(&mutex);

        item = consumir_item();

        printf("Consumidor..%d: consumindo item %d\n", tid, item);
        
        sem_post(&mutex);
        sem_post(&empty);
    }
}

void cria_consumidores_e_produtores(int n_consumidores, int n_produtores) 
{
    pthread_t consumers[n_consumidores], producers[n_produtores];

    for(int i=0; i < n_consumidores; i++)
        pthread_create(&consumers[i], NULL, consumidor, (void *)&i);

    for(int j=0; j < n_produtores; j++) 
        pthread_create(&producers[j], NULL, produtor, (void *)&j);

    pthread_exit((void *) NULL);
}

void inicia_semaforo() 
{
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, BUFFER_LENGTH);
    sem_init(&full,  0, 0);
}

void menu() {
    int op, n;

    printf("\n Problema do Produtor-Consumidor por Semáforos: \n\n");

    printf("\t (1) N Consumidores para 1 Produtor   \n");
    printf("\t (2) 1 Consumidor   para N Produtores \n");
    printf("\t (3) N Consumidores para N Produtores \n");

    printf("\n Digite a opção e o valor N: ");
    scanf("%d %d", &op, &n);

    switch(op) 
    {
        case 1:
                cria_consumidores_e_produtores(n, 1);
                break;
        case 2:
                cria_consumidores_e_produtores(1, n);
                break;
        case 3:
                cria_consumidores_e_produtores(n, n);
                break;
        default:
                printf("Opção inválida! \n");
                break;
    }
}

int main(void) 
{
    inicia_semaforo();
    menu();      
} 