#include "queue.h"

Queue *queue_init() {
    Queue *queue = (Queue*)malloc(sizeof(Queue));

    queue->first = NULL;
    queue->length = 0;

    return queue;
}

Cell queue_create_cell(TItem key) {
   Cell cell = (Cell)malloc(sizeof(TCell));

   cell->key = key;

   return cell;
}

int queue_is_empty(Queue *queue) {
    return (queue->length == 0) ? 1 : 0;
}

int enqueue(Queue *queue, TItem key) {
    Cell cell = queue_create_cell(key);

    Cell current_cell = queue->first;

    if(queue_is_empty(queue)) {
        queue->first = cell;
    } else {
        while(current_cell->next != NULL)
            current_cell = current_cell->next;

        current_cell->next = cell;
    }

    queue->length++;

    return 1;
}

TItem dequeue(Queue *queue) {
    if(queue_is_empty(queue))
        return 0;

    Cell cell_to_remove = queue->first;

    queue->first = (queue->length > 1) ? cell_to_remove->next : NULL;

    cell_to_remove->next = NULL;
    
    TItem removed_item = cell_to_remove->key;

    queue->length--;

    free(cell_to_remove);

    return removed_item;
}

void queue_print(Queue *queue) {
    Cell current_cell = queue->first;

    while(current_cell != NULL) {
        printf("%d -> ", current_cell->key);
        current_cell = current_cell->next;
    }

    printf("null\n");
}
