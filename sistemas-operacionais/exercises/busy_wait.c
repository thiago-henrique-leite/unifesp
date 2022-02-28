#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int turn = 1;

#define ALTERNA(turn) (1-turn)

void critical_region(int pid) 
{
    printf("RC\t pid=%d turn=%d \n", pid, turn);
    fflush(stdout);
}   

void noncritical_region(int pid) 
{
    printf("OUT\t pid=%d turn=%d \n", pid, turn);
    fflush(stdout);
}

void *proc(void *args) 
{
    int pid = *(int *)args;

    while(1) {
        while(turn != pid);
        
        critical_region(pid);
        turn = ALTERNA(turn);
        noncritical_region(pid);
    }
}

int main(int argc, char** argv) 
{
    pthread_t pt0, pt1;

    int pid0 = 0;
    int pid1 = 1;

    pthread_create(&pt0, NULL, proc, &pid0);
    pthread_create(&pt1, NULL, proc, &pid1);

    pthread_join(pt0, NULL);
    pthread_join(pt1, NULL);

    return 0;
}