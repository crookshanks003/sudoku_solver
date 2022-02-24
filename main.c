#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct args {
	int grid[36][36];
	int size;
};

int solved = 0;

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
	for (i = *row; i < size; i++) {
		for (j = *col; j < size; j++) {
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
	int valid_num[size];
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

void *solve_sudoku(void *args) {

	struct args *a;
	a = (struct args *)args;

	int row = 0;
	int col = 0;

	if (find_empty_cell(&row, &col, a->grid, a->size) == 0) {
		solved = 1;
		print_grid(a->size, a->grid);
		return 0;
	}

	int i, k;
	int valid[a->size];
	int index = 0;

	for (k = 1; k <= a->size; k++) {
		if (is_valid(k, row, col, a->grid, a->size)) {
			valid[index] = k;
			index++;
		}
	}

	while (index--) {
		a->grid[row][col] = valid[index];

		struct args new_a;
		memcpy(new_a.grid, a->grid, sizeof(a->grid));
		new_a.size = a->size;

		solve_sudoku(&new_a);
		/* pthread_create(&th, NULL, solve_sudoku, NULL); */
		if (solved) return 0;
		a->grid[row][col] = 0;
	}

	/* for (i = 1; i <= size; i++) { */ /* 	if (is_valid(i, row, col, grid,
										   size)) { */
	/* 		grid[row][col] = i; */
	/* 		if (solve_sudoku(grid, size)) return 1; */
	/* 		grid[row][col] = 0; */
	/* 	} */
	/* } */
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
	struct args a;
	memcpy(a.grid, grid, sizeof(grid));
	a.size = size;

	solve_sudoku(&a);

	if (solved != 1) printf("No solution");
	/* if (solved) */
	/* 	print_grid(size, grid); */
	/* else */
	/* 	printf("No solution"); */
}
