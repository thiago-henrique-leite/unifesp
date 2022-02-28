#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include <omp.h>

#define MATRIX_LENGTH 2048
#define GENERATIONS 2000
#define PRINT_LENGTH 50
#define NUM_THREADS 4

int cells_alive;

int** allocate_memory_to_matrix();
void initialize_matrix(int **grid);
int get_neighbors_amount(int **grid, int row, int column);
int get_new_cell_status(int **grid, int i, int j);
int get_num_cells_alive(int **grid);
void next_generation(int **grid, int **new_grid);
void generate_next_generations(int **grid, int **new_grid);
void print_matrix(int **grid);

#endif
