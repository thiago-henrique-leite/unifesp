#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct TCell *Cell;

typedef int TItem;

typedef struct TCell {
  Cell next;
  TItem key;
} TCell;

typedef struct {
  Cell first;
  int length;
} Queue;

Queue *queue_init();
Cell   queue_create_cell(TItem key);
int    enqueue(Queue *queue, TItem key);
TItem  dequeue(Queue *queue);
int    queue_has_key(Queue *queue, TItem key);
void   queue_print(Queue *queue);

#endif
