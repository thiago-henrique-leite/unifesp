#ifndef PAGE_H
#define PAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define PAGE_BITS_SIZE 8

typedef struct TPage *Page;

typedef struct TPage {
  Page next;
  int id;
  int bits[PAGE_BITS_SIZE];
} TPage;

Page create_page(int id);
void print_page(Page page);
void reset_page_bits(Page page);
int  convert_binary_to_decimal(Page page);
int  select_aleatory_page(int page_access);

#endif