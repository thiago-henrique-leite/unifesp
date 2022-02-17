#include "stack.c"

int main(int argc, char** argv) {
    Stack *stack = stack_init();

    stack_push(stack, 5);
    stack_push(stack, 4);
    stack_push(stack, 3);
    stack_push(stack, 2);
    stack_push(stack, 1);
    stack_push(stack, 0);

    stack_pop(stack);
    stack_pop(stack);
    stack_pop(stack);

    stack_print(stack);

    return 0;
}
