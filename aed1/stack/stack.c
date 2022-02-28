#include "stack.h"

Stack *stack_init() {
    Stack *stack = (Stack*)malloc(sizeof(Stack));

    stack->top = NULL;
    
    return stack;
}

Cell stack_create_cell(TItem key) {
   Cell cell = (Cell)malloc(sizeof(TCell));

   cell->key = key;

   return cell;
}

int stack_is_empty(Stack *stack) {
    return (stack->top == NULL) ? 1 : 0;
}

int stack_push(Stack *stack, TItem key) {
    Cell cell = stack_create_cell(key);

    cell->next = stack->top;

    stack->top = cell;

    return 1;
}

TItem stack_pop(Stack *stack) {
    if(stack_is_empty(stack))
        return 0;

    Cell cell_to_remove = stack->top;

    stack->top = stack->top->next;

    TItem removed_item = cell_to_remove->key;

    free(cell_to_remove);

    return removed_item;
}

void stack_print(Stack *stack) {
    Cell current_cell = stack->top;

    while(current_cell != NULL) {
        printf("%d -> ", current_cell->key);
        current_cell = current_cell->next;
    }

    printf("null\n");
}
