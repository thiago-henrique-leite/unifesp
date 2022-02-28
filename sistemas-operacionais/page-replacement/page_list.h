#ifndef PAGE_LIST_H
#define PAGE_LIST_H

#include <limits.h>
#include "list.h"

void create_initial_pages(List *memory, int memory_size, int *page_counter);
void update_page_bits(List *memory, int page_id, int real_memory_size);
Page get_page_to_replace(List *memory);
Page get_page_by_id(List *list, int id);

#endif