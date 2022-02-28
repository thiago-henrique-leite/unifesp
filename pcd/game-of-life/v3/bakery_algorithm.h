#ifndef BAKERY_ALGORITHM_H
#define BAKERY_ALGORITHM_H

#include "../game_of_life.h"

int want_to_enter[NUM_THREADS];
int choosing_ticket[NUM_THREADS];

int max();
void choose_ticket(int t_id);
void lock(int t_id);
void unlock(int t_id);

#endif
