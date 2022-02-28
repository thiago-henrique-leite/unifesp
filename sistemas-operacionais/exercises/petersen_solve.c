#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define FALSE 0
#define TRUE  1
#define N 2

int interested[N];
int turn;

void print(int process) 
{
    printf("P%d leave region\n", process);
    usleep(10);
}

void leave_region(int process) 
{
    interested[process] = FALSE;
}

void enter_region(int process) 
{
    int other = 1 - process;

    interested[process] = TRUE;
    
    turn = process;

    while(turn == process && interested[other] == TRUE);
    
    printf("\nP%d enter region - ", process);
}

void *proc(void *args) 
{
    int pid = *(int *)args;

    while(TRUE) 
    {
        enter_region(pid);
        print(pid);
        leave_region(pid);
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