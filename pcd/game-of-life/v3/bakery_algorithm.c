#include "bakery_algorithm.h"

int max() 
{
    int max = want_to_enter[0];

    for(int i=1; i<NUM_THREADS; i++)
        if(want_to_enter[i] > max) 
            max = want_to_enter[i];

    return max;
}

void choose_ticket(int t_id) 
{
    choosing_ticket[t_id] = 1;
    want_to_enter[t_id] = 1 + max();
    choosing_ticket[t_id] = 0;
}

void lock(int t_id) 
{
    choose_ticket(t_id);

    for(int j=0; j<NUM_THREADS; j++) 
    {
        if(j != t_id) 
        {
            while(choosing_ticket[j] == 1);
            while(!(want_to_enter[j] == 0 || (want_to_enter[t_id] < want_to_enter[j] || (want_to_enter[t_id] == want_to_enter[j] && t_id < j))));
        }
    }
}

void unlock(int t_id) 
{
    want_to_enter[t_id] = 0;
}
