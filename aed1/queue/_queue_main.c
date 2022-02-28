#include "queue.c"

int main(int argc, char** argv) {
    Queue *queue = queue_init();

    enqueue(queue, 0);
    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);
    enqueue(queue, 4);
    enqueue(queue, 5);

    dequeue(queue);
    dequeue(queue);
    dequeue(queue);

    queue_print(queue);

    return 0;
}
