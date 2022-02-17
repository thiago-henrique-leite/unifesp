#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

typedef struct TCell *Cell;

typedef int TItem;

typedef struct TCell {
  Cell next;
  TItem key;
} TCell;

typedef struct {
  Cell top;
} Stack;

Stack *stack_init();
Cell   stack_create_cell(TItem key);
int    stack_push(Stack *stack, TItem key);
TItem  stack_pop(Stack *stack);
int    stack_has_key(Stack *stack, TItem key);
void   stack_print(Stack *stack);

#endif
