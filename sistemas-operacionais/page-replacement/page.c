#include "page.h"

Page create_page(int id) {
   Page new_page = (Page)malloc(sizeof(TPage));

   for(int i = 0; i < PAGE_BITS_SIZE; i++)
        new_page->bits[i] = 0;

   new_page->id = id;

   return new_page;
}

int convert_binary_to_decimal(Page page) {
  int j = 0, decimal = 0;

  for(int i = PAGE_BITS_SIZE - 1; i >= 0; i--, j++)
    if(page->bits[i]) 
      decimal += pow(2, j);
  
  return decimal;
}

void print_page(Page page) {
    printf("Pagina%d ", page->id);

    for(int i = 0; i < PAGE_BITS_SIZE; i++)
        printf("%d", page->bits[i]);

    printf("\n");
}

int select_aleatory_page(int page_access) {
    return (rand() % page_access) + 1;
}

void reset_page_bits(Page page) {
    for(int i = 0; i < PAGE_BITS_SIZE; i++)
        page->bits[i] = 0;
}