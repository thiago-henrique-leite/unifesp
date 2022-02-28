#include "page.c"
#include "list.c"
#include "page_list.c"

void validate_params(int virtual_memory, int real_memory, int n_iterations, int limiter) {

    if(real_memory >= virtual_memory || n_iterations < 0 || limiter > virtual_memory) {

        if(real_memory >= virtual_memory)
            printf("Memória virtual deve ser maior que a memória real! \n");
        if(n_iterations < 0)
            printf("Número de iterações deve ser maior que zero! \n");
        if(limiter > virtual_memory)
            printf("Limitador deve ser menor ou igual ao tamanho da memória virtual! \n");

        exit(0);
    }
}

int main(int argc, char** argv) {

    if(argc == 1) {
        printf("Parâmetros não informados.\n");
        exit(0);
    }

    const int virtual_memory_size = atoi(argv[1]);
    const int real_memory_size = atoi(argv[2]);
    const int iterations = atoi(argv[3]);
    const int random_number_limiter = atoi(argv[4]);

    const int swap_memory_size = virtual_memory_size - real_memory_size;

    validate_params(virtual_memory_size, real_memory_size, iterations, random_number_limiter);

    List *real_memory = list_init();
    List *swap_memory = list_init();

    int page_counter = 1;

    create_initial_pages(real_memory, real_memory_size, &page_counter);
    create_initial_pages(swap_memory, swap_memory_size, &page_counter);

    srand(time(NULL));
    
    Page accessed_page, required_page_of_swap_memory, page_to_be_replaced;

    int hits = 0, page_misses = 0, page_id = 0;

    for(int i = 0; i < iterations; i++) {

        page_id = select_aleatory_page(random_number_limiter);

        if(list_search_item(real_memory, page_id)) 
        {
            update_page_bits(real_memory, page_id, real_memory_size);
            hits++;
        } 
        else 
        {
            required_page_of_swap_memory = get_page_by_id(swap_memory, page_id);
            page_to_be_replaced = get_page_to_replace(real_memory);
            
            list_remove(real_memory, page_to_be_replaced);
            list_remove(swap_memory, required_page_of_swap_memory);

            list_insert(real_memory, required_page_of_swap_memory);
            list_insert(swap_memory, page_to_be_replaced);

            reset_page_bits(required_page_of_swap_memory);
            update_page_bits(real_memory, required_page_of_swap_memory->id, real_memory_size);

            page_misses++;
        }
    }

    float hits_percentage = (float) hits / iterations * 100;

    printf("Tamanho da Memória Virtual: %d\n", virtual_memory_size);
    printf("Tamanho da Memória Real:    %d\n", real_memory_size);
    printf("Tamanho da Memória Swap:    %d\n", swap_memory_size);
    printf("Iterações:  %d\n", iterations);
    printf("Limitador:  %d\n", random_number_limiter);
    printf("Misses:     %d\n", page_misses);
    printf("Hits:       %d\n", hits);
    printf("%% de Hits:  %.2f%%\n", hits_percentage);

    return 0;
}