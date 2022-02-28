#include "../game_of_life.h"

int** allocate_memory_to_matrix()
{
    int **matrix = (int**)malloc(sizeof(int*) * MATRIX_LENGTH);
    int i;

#pragma omp parallel for
    for(i = 0; i < MATRIX_LENGTH; i++)
       matrix[i] = (int*)calloc(MATRIX_LENGTH, sizeof(int));
    
    return matrix;
}

void initialize_matrix(int **grid)
{
    int l, c;

    l = 1; c = 1;
    grid[l][c+1] = grid[l+1][c+2] = grid[l+2][c] = grid[l+2][c+1] = grid[l+2][c+2] = 1;

    l = 10; c = 30;
    grid[l][c+1] = grid[l][c+2] = grid[l+1][c] = grid[l+1][c+1] = grid[l+2][c+1] = 1;
}

int get_neighbors_amount(int **grid, int row, int column)
{
    int border_limit = MATRIX_LENGTH - 1;

    int row_up = row - 1;
    int row_down = row + 1;
    int column_left = column - 1;
    int column_right = column + 1;

    if(row_up < 0) row_up = border_limit;
    if(row_down > border_limit) row_down = 0;
    if(column_left < 0) column_left = border_limit;
    if(column_right > border_limit) column_right = 0;

    return grid[row_up][column_left] + grid[row_up][column] + grid[row_up][column_right] +
           grid[row][column_right] + grid[row][column_left] + grid[row_down][column_left] +
           grid[row_down][column] + grid[row_down][column_right];
}

int get_new_cell_status(int **grid, int i, int j)
{
    int neighbors = get_neighbors_amount(grid, i, j);
    
    if(grid[i][j] == 1 && neighbors != 2 && neighbors != 3)
        return 0;
    
    if(grid[i][j] == 0 && neighbors == 3)
        return 1;

    return grid[i][j];
}

int get_num_cells_alive(int **grid)
{    
    int i, j;

    cells_alive = 0;

#pragma omp parallel for reduction(+: cells_alive) private(j) 
    for(i = 0; i < MATRIX_LENGTH; i++) 
    {
        for(j = 0; j < MATRIX_LENGTH; j++) 
        {
            if(grid[i][j])
            {
                cells_alive += grid[i][j];
            }
        }
    }

    return cells_alive;
}

void next_generation(int **grid, int **new_grid)
{
    int i, j;

#pragma omp parallel for private(j)
    for(i = 0; i < MATRIX_LENGTH; i++)
        for(j = 0; j < MATRIX_LENGTH; j++)
            new_grid[i][j] = get_new_cell_status(grid, i, j);

#pragma omp parallel for private(j)
    for(i = 0; i < MATRIX_LENGTH; i++)
        for(j = 0; j < MATRIX_LENGTH; j++)
            grid[i][j] = new_grid[i][j];
}

void generate_next_generations(int **grid, int **new_grid)
{
    printf("Condição inicial: %d\n", get_num_cells_alive(grid));

    for(int i = 0; i < GENERATIONS; i++)
    {
        next_generation(grid, new_grid);

        if(i < 4 || i == GENERATIONS - 1) {
            printf("Geração %d: %d\n", i+1, get_num_cells_alive(grid));
        }
    }
}

void print_matrix(int **grid)
{
    int i, j;

    for(i = 0; i < PRINT_LENGTH; i++)
    {
        for(j = 0; j < PRINT_LENGTH; j++)
            printf("%d  ", grid[i][j]);

        printf("\n");
    }

    printf("\n");
}

int main(int argc, char **argv) 
{
    omp_set_num_threads(NUM_THREADS);

    int **grid = allocate_memory_to_matrix();
    int **new_grid = allocate_memory_to_matrix();

    initialize_matrix(grid);
    initialize_matrix(new_grid);
    
    time_t start, end;

    time(&start);
    generate_next_generations(grid, new_grid);
    time(&end);
    
    printf("Tempo de execução: %.2lf segundos.\n", difftime(end, start));
   
    return 0;
}
