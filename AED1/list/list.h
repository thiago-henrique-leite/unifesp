#ifndef LIST_H
#define LIST_H

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
} List;

List *list_init();
Cell  list_create_cell(TItem key);
Cell  list_get_cell_by_key(List *list, TItem key);
int   list_insert_last(List *list, TItem key);
int   list_insert_index(List *list, TItem key, int index);
TItem list_remove(List *list, TItem key);
int   list_has_key(List *list, TItem key);
void  list_print(List *list);

#endif
