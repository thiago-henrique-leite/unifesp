#include "list.c"

int main(int argc, char** argv) {
    List *list = list_init();

    list_insert_last(list, 0);
    list_insert_last(list, 2);
    list_insert_last(list, 4);
    list_insert_last(list, 6);
    list_insert_last(list, 8);
    list_insert_last(list, 10);

    list_insert_index(list, 1, 1);
    list_insert_index(list, 3, 3);
    list_insert_index(list, 5, 5);
    list_insert_index(list, 7, 7);
    list_insert_index(list, 9, 9);

    list_remove(list, 7);
    list_remove(list, 8);
    list_remove(list, 9);
    list_remove(list, 10);
    list_remove(list, 11);

    list_print(list);

    return 0;
}
