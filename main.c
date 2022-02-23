#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void read_grid_from_file(int size, char *ip_file, int grid[36][36]) {
	FILE *fp;
	int i, j;
	fp = fopen(ip_file, "r");
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++) {
			fscanf(fp, "%d", &grid[i][j]);
		}
}

void print_grid(int size, int grid[36][36]) {
	int i, j;
	/* The segment below prints the grid in a standard format. Do not change */
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++)
			printf("%d\t", grid[i][j]);
		printf("\n");
	}
}

int find_empty_cell(int *row, int *col, int grid[36][36], int size) {
	int i, j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if (grid[i][j] == 0) {
				*row = i;
				*col = j;
				return 1;
			}
		}
	}
	return 0;
}

int is_valid(int n, int r, int c, int grid[36][36], int size) {
	int i, j;
	int box_size = sqrt(size);
	for (i = 0; i < size; i++) {
		if (grid[r][i] == n) return 0;
	}
	for (i = 0; i < size; i++) {
		if (grid[i][c] == n) return 0;
	}
	int row_start = (r / box_size) * box_size;
	int col_start = (c / box_size) * box_size;
	for (i = row_start; i < row_start + box_size; i++) {
		for (j = col_start; j < col_start + box_size; j++) {
			if (grid[i][j] == n) return 0;
		}
	}
	return 1;
}

int solve_sudoku(int grid[36][36], int size) {
	int row;
	int col;
	if (find_empty_cell(&row, &col, grid, size) == 0) return 1;
	int n, i;
	for (i = 1; i <= size; i++) {
		if (is_valid(i, row, col, grid, size)) {
			grid[row][col] = i;
			if (solve_sudoku(grid, size)) return 1;
			grid[row][col] = 0;
		}
	}
	return 0;
}
int main(int argc, char *argv[]) {
	int grid[36][36], size, i, j;

	if (argc != 3) {
		printf("Usage: ./sudoku.out grid_size inputfile");
		exit(-1);
	}

	size = atoi(argv[1]);
	read_grid_from_file(size, argv[2], grid);

	/* Do your thing here */
	solve_sudoku(grid, size);

	print_grid(size, grid);
}
