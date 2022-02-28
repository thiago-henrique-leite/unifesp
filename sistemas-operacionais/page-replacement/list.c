#include "list.h"

List *list_init() {
    List *list = (List*)malloc(sizeof(List));

    list->first = NULL;
    list->length = 0;

    return list;
}

int list_insert(List *list, TItem item) {
    TItem current_item = list->first;

    if(current_item == NULL) {
        list->first = item;
    } else {
        while(current_item->next != NULL)
            current_item = current_item->next;

        current_item->next = item;
    }

    list->length++;

    return 1;
}

int list_remove(List *list, TItem item) {
    TItem current_item = list->first;

    if(current_item == NULL)
        return 0;

    if(item == list->first) {
        list->first = (list->length > 1) ? list->first->next : NULL;
    } else {
        while(current_item->next != item)
            current_item = current_item->next;

        current_item->next = item->next;
    }

    item->next = NULL;
    list->length--;

    return 1;
}

void list_print(List *list) {
    TItem current_item = list->first;

    while(current_item != NULL) {
        printf("%d -> ", current_item->id);
        current_item = current_item->next;
    }

    printf("null\n");
}

int list_search_item(List *list, int id) {
    TItem current_item = list->first;

    while(current_item->next != NULL) {
        if(current_item->id == id)
            return 1;

        current_item = current_item->next;
    }

    return (current_item->id == id) ? 1 : 0;
}