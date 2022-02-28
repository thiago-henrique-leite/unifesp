#ifndef LIST_H
#define LIST_H

#include "page.h"

#define TItem Page

typedef struct {
  TItem first;
  int length;
} List;

List *list_init();
int  list_insert(List *list, TItem item);
int  list_remove(List *list, TItem item);
int  list_search_item(List *list, int id);
void list_print(List *list);

#endif