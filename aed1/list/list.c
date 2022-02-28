#include "list.h"

List *list_init() {
    List *list = (List*)malloc(sizeof(List));

    list->first = NULL;
    list->length = 0;

    return list;
}

Cell list_create_cell(TItem key) {
   Cell cell = (Cell)malloc(sizeof(TCell));

   cell->key = key;

   return cell;
}

Cell list_get_cell_by_key(List *list, TItem key) {
    Cell current_cell = list->first;

    if(list_has_key(list, key) == 0)
        return 0;

    while(current_cell->key != key && current_cell != NULL)
        current_cell = current_cell->next;

    return current_cell;
}

int list_insert_last(List *list, TItem key) {
    Cell cell = list_create_cell(key);

    Cell current_cell = list->first;

    if(current_cell == NULL) {
        list->first = cell;
    } else {
        while(current_cell->next != NULL)
            current_cell = current_cell->next;

        current_cell->next = cell;
    }

    list->length++;

    return 1;
}

int list_insert_index(List *list, TItem key, int index) {
    int counter = 0;
    
    Cell cell = list_create_cell(key);

    Cell current_cell = list->first;

    if(index < 0 || index > list->length)
        return 0;
    
    if(index == 0) {
        list->first = cell;
        list->first->next = current_cell;
    } else {
        while(counter < index - 1) {
            current_cell = current_cell->next;

            counter++;
        }

        cell->next = current_cell->next;;
        current_cell->next = cell;
    }

    list->length++;

    return 1;
}

int list_remove(List *list, TItem key) {
    Cell cell = list_get_cell_by_key(list, key);

    if(cell == NULL)
        return 0;

    Cell current_cell = list->first;

    if(current_cell == NULL)
        return 0;

    if(cell == list->first) {
        list->first = (list->length > 1) ? list->first->next : NULL;
    } else {
        while(current_cell->next != cell)
            current_cell = current_cell->next;

        current_cell->next = cell->next;
    }

    cell->next = NULL;
    list->length--;

    free(cell);

    return 1;
}

int list_has_key(List *list, TItem key) {
    Cell current_cell = list->first;

    if(list->length == 0)
        return 0;

    while(current_cell->next != NULL) {
        if(current_cell->key == key)
            return 1;

        current_cell = current_cell->next;
    }

    return (current_cell->key == key) ? 1 : 0;
}

void list_print(List *list) {
    Cell current_cell = list->first;

    while(current_cell != NULL) {
        printf("%d -> ", current_cell->key);
        current_cell = current_cell->next;
    }

    printf("null\n");
}
