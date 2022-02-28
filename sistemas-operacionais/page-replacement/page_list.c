#include "page_list.h"

void create_initial_pages(List *memory, int memory_size, int *page_counter) {
    for(int i = 0; i < memory_size; i++) {
        list_insert(memory, create_page(*page_counter));

        *page_counter += 1;
    }
}

void update_page_bits(List *memory, int page_id, int real_memory_size) {
    Page current_page = memory->first;

    for(int i = 0; i < real_memory_size; i++) {
        for(int i = PAGE_BITS_SIZE - 1; i > 0; i--)
            current_page->bits[i] = current_page->bits[i-1];

        current_page->bits[0] = (current_page->id == page_id) ? 1 : 0;

        current_page = current_page->next;
    } 
}

Page get_page_to_replace(List *memory) {
    int smaller = INT_MAX;
    int decimal = 0;

    Page current_page = memory->first;
    Page page_to_replace;

    while(current_page != NULL) {
        decimal = convert_binary_to_decimal(current_page);

        if(decimal < smaller) {
            smaller = decimal;
            page_to_replace = current_page;
        }

        current_page = current_page->next;
    }

    return page_to_replace;
}

Page get_page_by_id(List *list, int id) {
    Page current_page = list->first;

    while(current_page->id != id && current_page != NULL)
        current_page = current_page->next;

    return current_page;
}
