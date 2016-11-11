#include <stdio.h>
#include <stdlib.h>
#include <random>
#include <time.h>
#include "algorithms.h"

#define N 2
#define FIRST 524288
#define STEP 10


void fill(int* arr, int size) {
	int i = 0;
	for (i = 0; i < size; ++i)
		arr[i] = rand();
}

int main() {
	srand(time(NULL));

	size_t i = 1, n = FIRST, order = ASC;
	unsigned int start_time, end_time, sort_time;
	int *arr;
	for (i = 1; i <= STEP; ++i) {
		n = n * N;
		arr = (int*)malloc(sizeof(int) * n);
		if (arr == NULL)
			continue;
		fill(arr, n);
		printf("Size array %d, order ", n);
		start_time = clock();
		merge(arr, n, order);
		end_time = clock();
		sort_time = end_time - start_time;
		if (check(arr, n, order) != 0)
			printf(" ERROR ");
		else
			printf(" Time %.3f ", sort_time / 1000.0);
		printf("\n");
		free(arr);
	}
	return 0;
}